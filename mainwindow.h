#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSend_clicked();

    void on_btnConnect_clicked();

    void on_btnDisconnect_clicked();

    void sendMessage();

    void readyRead();

private:
    Ui::MainWindow *ui;
    QTcpSocket  *mySocket;
};
#endif // MAINWINDOW_H
