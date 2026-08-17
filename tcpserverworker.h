#pragma once

#include <QByteArray>
#include <QHash>
#include <QJsonObject>
#include <QList>
#include <QObject>

class QTcpServer;
class QTcpSocket;

// TCP服务器工作对象。
//
// 本类只在专用TCP线程中使用。QTcpServer、QTcpSocket和每个客户端的
// 收包缓存都由该线程管理，主线程只能通过信号槽启动或停止服务器。
class TcpServerWorker final : public QObject
{
    Q_OBJECT

public:
    explicit TcpServerWorker(QObject *parent = nullptr);

public slots:
    // 在本机所有IPv4网卡的7788端口启动服务器。
    void startServer();

    // 停止监听并关闭当前所有客户端连接。
    void stopServer();

    // 业务执行成功后，按原请求的id和seq回复ACK。
    void completeBusinessRequest(quint64 requestToken,
                                 const QString &data);

    // 业务执行失败时丢弃待回复请求，不向机器人发送任何消息。
    void discardBusinessRequest(quint64 requestToken);

signals:
    void serverStateChanged(bool running, const QString &listenAddress);
    void logMessage(const QString &message);
    void businessRequestReceived(quint64 requestToken,
                                 const QString &payload);

private slots:
    // 接收并初始化所有等待处理的客户端连接。
    void onNewConnection();

    // 读取当前客户端数据，按长度前缀拆帧并解析JSON。
    void onReadyRead();

    // 清理已经断开的客户端及其收包缓存。
    void onClientDisconnected();

private:
    struct PendingBusinessRequest
    {
        QTcpSocket *socket = nullptr;
        QJsonObject message;
    };

    // 将JSON对象编码成“4字节大端长度 + UTF-8 JSON”并写入客户端。
    bool writeJsonFrame(QTcpSocket *socket, const QJsonObject &object);

    // 返回用于日志显示的客户端地址。
    QString peerName(const QTcpSocket *socket) const;

    QTcpServer *m_server = nullptr;
    QList<QTcpSocket *> m_clients;
    QHash<QTcpSocket *, QByteArray> m_receiveBuffers;
    QHash<quint64, PendingBusinessRequest> m_pendingBusinessRequests;
    quint64 m_nextBusinessRequestToken = 1;
};
