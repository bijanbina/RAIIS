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
#include "re_connection.h"

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
    void startTransfer(const char* command);
    void sendBuffer();
    void displayError();
    void disconnected();
    void readyRead(QString read_data);

private:
    QTcpSocket tcp_client;
    ReConnection *connection;

    char char_buffer;
    bool is_buffer_empty;

    QTimer *timer;
    QObject *ui;
};

#endif // ReClient_H
