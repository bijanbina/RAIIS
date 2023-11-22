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

#define FA_LIVE_PACKET  "--Live--"
#define FA_START_PACKET "<START>\r\n"
#define FA_END_PACKET   "\r\n<END>\r\n"

class ReApacheCl : public QObject
{
    Q_OBJECT

public:
    explicit ReApacheCl(QObject *parent = 0);
    ~ReApacheCl();

    void write(QString data);
    void start(QString ip, int port);
    QByteArray processBuffer();

signals:
    void connected();
    void readyRead(QString data);

public slots:
    void tcpConnected();
    void tcpReadyRead();
    void tcpDisplayError(QAbstractSocket::SocketError socketError);
    void disconnected();
    void watchdogTimeout();
    void liveTimeout();

private:
    QTcpSocket *con;
    QTimer *live;
    QTimer *watchdog;

    QString c_ip;
    QByteArray read_buf;
    clock_t start_of_app;
    int c_port;
};

#endif // RE_APACHE_CL_H
