#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    sock = new QTcpSocket();
    connect(sock, SIGNAL(connected()), this, SLOT(OnConnected()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
    connect(sock, SIGNAL(disconnected()), this, SLOT(OnDisconnected()));
}

void MainWindow::Connect(QString& addr, qint16 port)
{
    sock->connectToHost(addr, port);
}

void MainWindow::OnConnected()
{
    qDebug() << "Connected Successfully";
    QHostAddress addr =  sock->peerAddress();
    qint16 port = sock->peerPort();

    QString peer = addr.toString().append(':').append(QString().arg(port));
    QString sendData("hello ");
    sendData.append(peer).append(',').append("I'm client");
    sock->write(sendData.toStdString().c_str());
}

void MainWindow::OnReadyRead()
{
    if (sock->isReadable()) {
        qint64 available = sock->bytesAvailable();
        if (available < 8) {
            return;
        }

        qDebug() << "read data";
    }
}

void MainWindow::OnDisconnected() {

}
