#ifndef RE_CONNECTION_H
#define RE_CONNECTION_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QObject>
#include <QVector>
#include <stdio.h>
#include <stdlib.h>
#include <QTimer>
#include <QSignalMapper>
#include "backend.h"

class ReConnection : public QObject
{
    Q_OBJECT

public:
    explicit ReConnection(QTcpSocket *con,
                          QObject *parent = 0);
    ~ReConnection();

    void write(QString data);

signals:
    void clientDisconnected();
    void clientConnected();
    void clientReadyRead(QString data);
    void clientError();

public slots:
    void readyRead();
    void displayError(QAbstractSocket::SocketError socketError);
    void handleDisconnect();
    void watchdogTimeout();
    void liveTimeout();

private:
    QTcpSocket *connection;
    QTimer *live;
    QTimer *watchdog;
};

#endif // RE_CONNECTION_H
