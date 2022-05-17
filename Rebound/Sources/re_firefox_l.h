#ifndef RE_FIREFOX_L_H
#define RE_FIREFOX_L_H

#include <QObject>
#include <QtDebug>
#include <QtWebSockets/QtWebSockets>
#include "backend.h"

class ReFirefoxL : public QObject
{
    Q_OBJECT
public:
    explicit ReFirefoxL(QObject *parent = nullptr);
    void sendScroll();


private slots:
    void onConnected();
    void onDisconnected();
    void dataReceived(QString message);

private:
    void send_js(QString cmd);
    QWebSocket *socket;
    QString cmd_buf;
};

#endif // RE_FIREFOX_L_H
