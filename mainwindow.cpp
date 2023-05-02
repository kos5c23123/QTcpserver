#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mySocket = new QTcpSocket(this);
    connect(mySocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSend_clicked()
{
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("hh:mm:ss: ");
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

    char myChar[100];
    if (mySocket->isWritable())
    {
        QString MyStr = ui->Message->text();
        memcpy(myChar, ui->Message->text().toUtf8(), MyStr.length());
        mySocket->write(myChar);
        mySocket->waitForBytesWritten(1000);
        ui->SystemLog->appendPlainText(QString(formattedTimeMsg) + QString(myChar));
        ui->Message->clear();
    }
}

void MainWindow::sendMessage()
{
    QByteArray ID = ui->ClientID->text().toUtf8();
    mySocket->write(ID);
}

void MainWindow::on_btnConnect_clicked()
{
    //Input
    char myChar[100];
    QString MyStr = ui->ServerAddrInput->text();
    memcpy(myChar, ui->ServerAddrInput->text().toUtf8(), MyStr.length());

    // Time
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("hh:mm:ss: ");
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

    qintptr customID = ui->ClientID->text().toLongLong();

    ui->SystemLog->clear();
    mySocket->connectToHost(QString(myChar), 8597);

    if (mySocket->waitForConnected(3000))
    {
        ui->SystemLog->appendPlainText(QString(formattedTimeMsg) + "Connected to server " + QString(myChar) + " successful");
    }
    else
    {
        ui->SystemLog->appendPlainText(QString(formattedTimeMsg) + "Connected to server " + QString(myChar) + " failed");
    }
}


void MainWindow::on_btnDisconnect_clicked()
{
    //Input
    char myChar[100];
    QString MyStr = ui->ServerAddrInput->text();
    memcpy(myChar, ui->ServerAddrInput->text().toUtf8(), MyStr.length());

    //Time
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("hh:mm:ss: ");
    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();

    if (mySocket->isOpen())
    {
        mySocket->close();
        ui->SystemLog->appendPlainText(QString(formattedTimeMsg) + "Disconnected from the server " + QString(myChar));
    }
}



void MainWindow::readyRead()
{
    QByteArray myByte;
    myByte = mySocket->readAll();
    ui->MessageRec->appendPlainText(QString(myByte));
}



