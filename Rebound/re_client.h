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

#ifdef __linux__
#include "re_exec.h"
#endif

class ReClient : public QObject
{
    Q_OBJECT

public:
    explicit ReClient(QObject *parent = 0);
    ~ReClient();
signals:
    void errorConnection();
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

#ifdef __linux__
    ReExec exec;
#endif
};

#endif // ReClient_H
