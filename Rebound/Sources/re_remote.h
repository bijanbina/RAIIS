#ifndef RE_REMOTE_H
#define RE_REMOTE_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

#ifdef WIN32
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#endif

#include "backend.h"
#include "re_preprocessor.h"

class ReRemote : public QObject
{
    Q_OBJECT
public:
    ReRemote(RePreProcessor *pre, QObject *parent = NULL);
    ~ReRemote();

public slots:
    void send(QString word);

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
    void connectToHost();
    void liveTimeout();
    void watchdogTimeout();

private:
    void processCommand(QString k_type, QString k_code);
    int  procChess(QString word);
    int  procSuper(QString word);
    int  procMouse(QString word);
    void runLua(QString word);
    void wakeRemote();

    ReState    *state;
    ReChess    *chess;
    QString     last_word;
    QTcpSocket  tcpClient;
    ReMetaMos  *mouse;

    QTimer *live;
    QTimer *c_timer;
    QTimer *watchdog;

#ifdef WIN32
    lua_State   *lst;
    ReWin32Virt *virt;
#endif
};

#endif // RE_REMOTE_H
