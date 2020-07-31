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
#include <QGamepad>
#include "backend.h"

class ReServer : public QObject
{
    Q_OBJECT

public:
    explicit ReServer(QObject *item, QObject *parent = 0);
    ~ReServer();
signals:
    void errorConnection();

public slots:
    void acceptConnection();
    void readyRead();
    void displayError(QAbstractSocket::SocketError socketError);
    void buttonAChanged(bool);
    void buttonBChanged(bool);
    void buttonXChanged(bool);
    void buttonYChanged(bool);

    void buttonL1Changed(bool);
    void buttonL2Changed(double);
    void buttonR1Changed(bool);
    void buttonR2Changed(double);

    void buttonAxisLxChanged(double);
    void buttonAxisLyChanged(double);
    void buttonAxisRxChanged(double);
    void buttonAxisRyChanged(double);

private:
    long bytesReceived;
    QTcpServer *server;
    QTcpSocket *connection_socket;

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
    QGamepad *pad;

    QObject *ui;
};

#endif // ReServer_H
