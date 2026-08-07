#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QApplication::setApplicationName(QStringLiteral("PC-DMIS 坐标读取测试"));
    QApplication::setOrganizationName(QStringLiteral("PCDMISQtTest"));

    MainWindow window;
    window.show();

    return application.exec();
}

