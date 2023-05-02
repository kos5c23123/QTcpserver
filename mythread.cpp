#include "mythread.h"

MyThread::MyThread(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
}

void MyThread::run()
{
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    qDebug() << socketDescriptor << " Client connected";

    //Time
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("hh:mm:ss: ");
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

    //Addr
    QHostAddress localAddress = QHostAddress(QHostAddress::LocalHost);
    QString localIp = localAddress.toString();

    QString message = "Client " + QString::number(socketDescriptor).toUtf8() +" connected to server " + localIp;

    socket->write(QString("%1 %2").arg(formattedTimeMsg, message).toLocal8Bit());


    exec();
}

void MyThread::readyRead()
{

    QByteArray Data = socket->readAll();

    qDebug() << socketDescriptor << " Data: " << Data;

    //Time
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("hh:mm:ss: ");
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

    socket->write(formattedTimeMsg + Data + " [ACK:" + QString::number(socketDescriptor).toUtf8() + "]" );

}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";


    socket->deleteLater();
    exit(0);
}
