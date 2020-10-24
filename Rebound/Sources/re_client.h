#ifndef ReClient_H
#define ReClient_H

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

class ReClient : public QObject
{
    Q_OBJECT

public:
    explicit ReClient(QObject *item, QObject *parent = 0);
    ~ReClient();

    void sendData(const char *data, int size);

signals:
    void errorConnection();
    void newKey(QString key);

private slots:
    void connected();
    void start();
    void watchdog_timeout();
    void live_timeout();
    void startTransfer(const char* command);
    void displayError(QAbstractSocket::SocketError socketError);
    void sendBuffer();
    void disconnected();
    void readyRead();

private:
    QTcpSocket tcpClient;

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
    QTimer *timer;
    QTimer *watchdog;

    QObject *ui;
};

#endif // ReClient_H
