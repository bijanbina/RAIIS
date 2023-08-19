#ifndef RE_REMOTE_H
#define RE_REMOTE_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

#include "backend.h"

class ReRemote : public QObject
{
    Q_OBJECT
public:
    ReRemote(QObject *parent = NULL);
    ~ReRemote();

public slots:
    void send(QString k_type, QString k_code);

signals:
    void process(QString k_type, QString k_code);

private slots:
    void connected();
    void displayError(QAbstractSocket::SocketError socketError);
    void disconnected();
    void readyRead();

private:
    QTcpSocket tcpClient;
};

#endif // RE_REMOTE_H
