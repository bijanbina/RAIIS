#ifndef RE_APACHE_CL_H
#define RE_APACHE_CL_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QObject>
#include <QVector>
#include <stdio.h>
#include <stdlib.h>
#include <QTimer>
#include "backend.h"

class ReApacheCl : public QObject
{
    Q_OBJECT

public:
    explicit ReApacheCl(QObject *parent = 0);
    ~ReApacheCl();

    void write(QString data);
    void start(QString ip, int port);

signals:
    void connected();
    void readyRead(QString data);
    void error();

public slots:
    void tcpConnected();
    void tcpReadyRead();
    void tcpDisplayError(QAbstractSocket::SocketError socketError);
    void tcpDisconnected();
    void watchdogTimeout();
    void liveTimeout();

private:
    QTcpSocket *connection;
    QTimer *live;
    QTimer *watchdog;

    QString c_ip;
    int c_port;
};

#endif // RE_APACHE_CL_H
