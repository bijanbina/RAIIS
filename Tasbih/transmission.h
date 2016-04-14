#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QObject>
#include <QVector>
#include <stdio.h>
#include <stdlib.h>
#include <QTimer>
#include <QQmlProperty>

#define TR_PORT_ADDRESS 7651

class Transmission : public QObject
{
    Q_OBJECT

public:
    explicit Transmission(QObject *item, QObject *parent = 0);
    ~Transmission();
signals:
    void errorConnection();
private slots:
    void connected();
    void start(QString IP);
    void startTransfer(const char* command);
    void displayError(QAbstractSocket::SocketError socketError);
    void sendBuffer();
    void updateNumber();
private:
    QTcpSocket tcpClient;

    QVector<QString> stack;
    int code;
    char code_char[4];

    QString message;
    QTimer *bufferTimer;
    char charBuffer;
    bool isBufferEmpty;
    bool commandMode;
    int commandIndex;
    short commandByte;

    QObject *ui;
};

#endif // TRANSMISSION_H
