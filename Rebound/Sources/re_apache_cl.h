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
#define FA_START_PACKET "<START>\n"
#define FA_END_PACKET   "\n<END>\n"

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
    void reconnect();
    void watchdogTimeout();
    void liveTimeout();

private:
    QTcpSocket *con;
    QTimer *live;
    QTimer *watchdog;

    QString c_ip;
    QByteArray read_buf;
    int c_port;
};

#endif // RE_APACHE_CL_H
