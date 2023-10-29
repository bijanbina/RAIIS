#ifndef ReServer_H
#define ReServer_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QObject>
#include <QVector>
#include <stdio.h>
#include <stdlib.h>
#include <QTimer>
#include <QQmlProperty>
#include "re_state.h"
#include "re_connection.h"

class ReServer : public QObject
{
    Q_OBJECT

public:
    explicit ReServer(ReState *st, QObject *parent = 0);
    ~ReServer();

    void reboundSendKey(const char *data, int size);

    ReConnection *connection;

signals:
    void clientDisconnected();
    void clientConnected();
    void clientReqSuspend();

public slots:
    void acceptConnection();
    void readyRead(QString data);
    void handleDisconnect();

private:
    QTcpServer *server;
    ReState *state;
};

#endif // ReServer_H
