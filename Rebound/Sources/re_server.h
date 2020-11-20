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

class ReServer : public QObject
{
    Q_OBJECT

public:
    explicit ReServer(QObject *item, QObject *parent = 0);
    ~ReServer();

    void reboundSendKey(const char *data, int size);

signals:
    void errorConnection();
    void clientDisconnected();
    void clientConnected();

public slots:
    void acceptConnection();
    void readyRead();
    void live_timeout();
    void watchdog_timeout();
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


    QObject *ui;
};

#endif // ReServer_H
