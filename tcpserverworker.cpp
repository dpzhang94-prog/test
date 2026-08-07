#include "tcpserverworker.h"

#include <QAbstractSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QTcpServer>
#include <QTcpSocket>

namespace {
constexpr quint16 kServerPort = 7788;
constexpr quint32 kMaximumFrameSize = 1024U * 1024U;

// 根据协议生成带四字节大端长度前缀的JSON数据帧。
QByteArray buildJsonFrame(const QJsonObject &object)
{
    const QByteArray body =
        QJsonDocument(object).toJson(QJsonDocument::Compact);
    const quint32 length = static_cast<quint32>(body.size());

    QByteArray frame(4, Qt::Uninitialized);
    frame[0] = static_cast<char>((length >> 24) & 0xff);
    frame[1] = static_cast<char>((length >> 16) & 0xff);
    frame[2] = static_cast<char>((length >> 8) & 0xff);
    frame[3] = static_cast<char>(length & 0xff);
    frame.append(body);
    return frame;
}

// 优先选择可用的非回环IPv4地址，没有时回退到本地回环地址。
QHostAddress selectListenAddress()
{
    const QList<QNetworkInterface> interfaces =
        QNetworkInterface::allInterfaces();
    for (const QNetworkInterface &networkInterface : interfaces) {
        const QNetworkInterface::InterfaceFlags flags =
            networkInterface.flags();
        if (!flags.testFlag(QNetworkInterface::IsUp) ||
            !flags.testFlag(QNetworkInterface::IsRunning) ||
            flags.testFlag(QNetworkInterface::IsLoopBack)) {
            continue;
        }

        const QList<QNetworkAddressEntry> entries =
            networkInterface.addressEntries();
        for (const QNetworkAddressEntry &entry : entries) {
            const QHostAddress address = entry.ip();
            if (address.protocol() == QAbstractSocket::IPv4Protocol &&
                !address.isLoopback() &&
                !address.isNull()) {
                return address;
            }
        }
    }

    return QHostAddress::LocalHost;
}
}

TcpServerWorker::TcpServerWorker(QObject *parent)
    : QObject(parent)
{
}

void TcpServerWorker::startServer()
{
    if (m_server != nullptr && m_server->isListening()) {
        return;
    }

    // QTcpServer必须在本函数中创建，确保它归属于当前TCP工作线程。
    if (m_server == nullptr) {
        m_server = new QTcpServer(this);
        connect(m_server, &QTcpServer::newConnection,
                this, &TcpServerWorker::onNewConnection);
    }

    const QHostAddress listenAddress = selectListenAddress();
    if (!m_server->listen(listenAddress, kServerPort)) {
        emit logMessage(QStringLiteral("TCP服务器启动失败：%1")
                            .arg(m_server->errorString()));
        emit serverStateChanged(false, QString());
        return;
    }

    const QString addressText = listenAddress.toString();
    emit logMessage(QStringLiteral("TCP服务器已启动，监听 %1:%2")
                        .arg(addressText)
                        .arg(kServerPort));
    emit serverStateChanged(true, addressText);
}

void TcpServerWorker::stopServer()
{
    if (m_server == nullptr) {
        emit serverStateChanged(false, QString());
        return;
    }

    m_server->close();

    // 停止时不进行阻塞等待，所有socket都在所属TCP线程中异步销毁。
    const QList<QTcpSocket *> clients = m_clients;
    m_clients.clear();
    m_receiveBuffers.clear();
    for (QTcpSocket *socket : clients) {
        socket->disconnect(this);
        socket->disconnectFromHost();
        socket->deleteLater();
    }

    emit logMessage(QStringLiteral("TCP服务器已停止"));
    emit serverStateChanged(false, QString());
}

void TcpServerWorker::onNewConnection()
{
    while (m_server->hasPendingConnections()) {
        QTcpSocket *socket = m_server->nextPendingConnection();
        if (socket == nullptr) {
            continue;
        }

        m_clients.append(socket);
        connect(socket, &QTcpSocket::readyRead,
                this, &TcpServerWorker::onReadyRead);
        connect(socket, &QTcpSocket::disconnected,
                this, &TcpServerWorker::onClientDisconnected);

        emit logMessage(QStringLiteral("TCP客户端已连接：%1")
                            .arg(peerName(socket)));
    }
}

void TcpServerWorker::onReadyRead()
{
    auto *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == nullptr) {
        return;
    }

    QByteArray &buffer = m_receiveBuffers[socket];
    buffer.append(socket->readAll());

    // TCP是字节流，一次readyRead可能只有半帧，也可能包含多帧。
    while (true) {
        if (buffer.size() < 4) {
            return;
        }

        const quint32 frameLength =
            (static_cast<quint32>(
                 static_cast<quint8>(buffer.at(0))) << 24) |
            (static_cast<quint32>(
                 static_cast<quint8>(buffer.at(1))) << 16) |
            (static_cast<quint32>(
                 static_cast<quint8>(buffer.at(2))) << 8) |
            static_cast<quint32>(
                static_cast<quint8>(buffer.at(3)));

        if (frameLength == 0 || frameLength > kMaximumFrameSize) {
            emit logMessage(
                QStringLiteral("TCP帧长度非法，断开客户端：%1")
                    .arg(peerName(socket)));
            m_receiveBuffers.remove(socket);
            socket->disconnectFromHost();
            return;
        }

        if (buffer.size() < static_cast<qsizetype>(4 + frameLength)) {
            return;
        }

        const QByteArray body =
            buffer.mid(4, static_cast<qsizetype>(frameLength));
        buffer.remove(0, static_cast<qsizetype>(4 + frameLength));

        QJsonParseError parseError;
        const QJsonDocument document =
            QJsonDocument::fromJson(body, &parseError);
        if (parseError.error != QJsonParseError::NoError ||
            !document.isObject()) {
            emit logMessage(
                QStringLiteral("收到无效TCP JSON：%1")
                    .arg(parseError.errorString()));
            continue;
        }

        const QJsonObject message = document.object();
        emit logMessage(
            QStringLiteral("收到来自 %1 的TCP消息：%2")
                .arg(peerName(socket),
                     QString::fromUtf8(
                         QJsonDocument(message).toJson(
                             QJsonDocument::Compact))));

        // 心跳属于连接维护，不触发PC-DMIS或其他业务逻辑。
        if (message.value(QStringLiteral("type")).toString() ==
            QStringLiteral("ping")) {
            QJsonObject pong;
            pong.insert(QStringLiteral("type"), QStringLiteral("pong"));
            pong.insert(QStringLiteral("seq"),
                        message.value(QStringLiteral("seq")));
            if (!writeJsonFrame(socket, pong)) {
                emit logMessage(
                    QStringLiteral("TCP心跳回复失败：%1")
                        .arg(socket->errorString()));
            }
        }
    }
}

void TcpServerWorker::onClientDisconnected()
{
    auto *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == nullptr) {
        return;
    }

    const QString peer = peerName(socket);
    m_clients.removeOne(socket);
    m_receiveBuffers.remove(socket);
    socket->deleteLater();

    emit logMessage(QStringLiteral("TCP客户端已断开：%1").arg(peer));
}

bool TcpServerWorker::writeJsonFrame(
    QTcpSocket *socket, const QJsonObject &object)
{
    if (socket == nullptr ||
        socket->state() != QAbstractSocket::ConnectedState) {
        return false;
    }

    const QByteArray frame = buildJsonFrame(object);
    return socket->write(frame) == frame.size();
}

QString TcpServerWorker::peerName(const QTcpSocket *socket) const
{
    if (socket == nullptr) {
        return QStringLiteral("未知客户端");
    }

    return QStringLiteral("%1:%2")
        .arg(socket->peerAddress().toString())
        .arg(socket->peerPort());
}
