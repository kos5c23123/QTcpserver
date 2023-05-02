#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

#include "mythread.h"

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);
    void startServer();

signals:

public slots:

private:
    QTcpServer *server;

protected:
    void incomingConnection(qintptr socketDescriptor);

};

#endif // MYTCPSERVER_H
