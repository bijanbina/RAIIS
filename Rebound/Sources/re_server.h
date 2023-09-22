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
#include "backend.h"
#include "re_state.h"

class ReServer : public QObject
{
    Q_OBJECT

public:
    explicit ReServer(ReState *st, QObject *parent = 0);
    ~ReServer();

    void reboundSendKey(const char *data, int size);

signals:
    void errorConnection();
    void clientDisconnected();
    void clientConnected();
    void clientReqSusspend();

public slots:
    void acceptConnection();
    void readyRead();
    void liveTimeout();
    void watchdogTimeout();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    long bytesReceived;
    QTcpServer *server;
    QTcpSocket *connection_socket;

    QVector<QString> stack;
    int code;
    char code_char[4];

    QString message;
    char charBuffer;
    bool isBufferEmpty;
    bool commandMode;
    int commandIndex;
    short commandByte;

    QTimer *live;
    QTimer *watchdog;
    QTimer *bufferTimer;


    ReState *state;
};

#endif // ReServer_H
