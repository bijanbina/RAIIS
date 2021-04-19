#ifndef ReAdmin_H
#define ReAdmin_H

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

class ReAdminWin : public QObject
{
    Q_OBJECT

public:
    explicit ReAdminWin(int port, QObject *parent = 0);
    ~ReAdminWin();

signals:
    void errorConnection();
    void clientDisconnected();
    void clientConnected();
    void clientReqSusspend();

public slots:
    void acceptConnection();
    void readyRead();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    long bytesReceived;
    QTcpServer *server;
    QTcpSocket *connection_socket;

    QString message;
};

#endif // ReAdmin_H
