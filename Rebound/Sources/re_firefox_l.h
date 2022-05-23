#ifndef RE_FIREFOX_L_H
#define RE_FIREFOX_L_H

#include <QObject>
#include <QtDebug>
#include <QtWebSockets/QtWebSockets>
#include "backend.h"
#include "re_firefox_ws.h"

class ReFirefoxL : public QObject
{
    Q_OBJECT
public:
    explicit ReFirefoxL(QObject *parent = nullptr);
    ~ReFirefoxL();
    void sendScroll();

signals:
    void startChild();

private slots:
    void urlCheck(QString title, QString ws);
    void onConnected();
    void onDisconnected();
    void dataReceived(QString message);

private:
    void send_js(QString cmd);
    QWebSocket *socket;
    QString cmd_buf;
    QVector<ReFirefoxWs *> childs;
    QVector<QThread *>     childs_th;
};

#endif // RE_FIREFOX_L_H
