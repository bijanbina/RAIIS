#ifndef RE_FIREFOX_WS_H
#define RE_FIREFOX_WS_H

#include <QObject>
#include <QtDebug>
#include <QtWebSockets/QtWebSockets>
#include "backend.h"

class ReFirefoxWs : public QObject
{
    Q_OBJECT
public:
    explicit ReFirefoxWs(QString ws_url, QObject *parent = nullptr);
    ~ReFirefoxWs();

signals:
    void finished();

private slots:
    void onConnected();
    void onDisconnected();
    void dataReceived(QString message);
    void run();

private:
    void send_js(QString cmd);

    QWebSocket *socket;
    QString cmd_buf;
    QString url;
    int     title_state = 0;
};

#endif // RE_FIREFOX_WS_H
