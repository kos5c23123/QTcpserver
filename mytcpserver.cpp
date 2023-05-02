#include "mytcpserver.h"
#include "mythread.h"

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer{parent}
{
}

void MyTcpServer::startServer()
{
    int port = 8597;

    if(!this->listen(QHostAddress::Any,port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening to port " << port << "...";
    }
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting...";

    MyThread *thread = new MyThread(socketDescriptor, this);

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}
