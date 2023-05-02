#include "mainwindow.h"
#include "mytcpserver.h"

#include <QApplication>

#include <QTcpServer>
#include <QTcpSocket>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyTcpServer server;
    server.startServer();

    MainWindow w;
    w.show();
    return a.exec();
}
