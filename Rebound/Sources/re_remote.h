#ifndef RE_REMOTE_H
#define RE_REMOTE_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

#include "backend.h"
#include "re_preprocessor.h"

class ReRemote : public QObject
{
    Q_OBJECT
public:
    ReRemote(RePreProcessor *pre, QObject *parent = NULL);
    ~ReRemote();

public slots:
    void send(QString k_type, QString k_code);

signals:
    void dirs(const QString &args);
    void nato(QString args);
    void meta(QString args);
    void apps(QString args);
    void spex(QString args);
    void type(QString args);
    void super(QString args);
    void digit(QString args);
    void debug(QString args);
    void modifier(QString args);

private slots:
    void connected();
    void displayError(QAbstractSocket::SocketError socketError);
    void disconnected();
    void readyRead();

private:
    void processCommand(QString k_type, QString k_code);

    QTcpSocket tcpClient;
};

#endif // RE_REMOTE_H
