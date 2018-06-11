#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Init(void);
    void Connect(QString &addr, qint16 port);

private slots:
    void OnConnected();
    void OnReadyRead();
    void OnDisconnected();
signals:
    void SockConnected();

private:
    Ui::MainWindow *ui;
    QTcpSocket *sock;
};

#endif // MAINWINDOW_H
