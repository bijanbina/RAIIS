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
#include "re_exec.h"

#define RE_TIMEOUT   1000
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
    QTimer *timer;
    char charBuffer;
    bool isBufferEmpty;
    bool commandMode;
    int commandIndex;
    short commandByte;

    QObject *ui;
    ReExec exec;
};

#endif // ReClient_H
