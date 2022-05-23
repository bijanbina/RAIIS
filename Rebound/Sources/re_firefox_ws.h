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
    void finished(QString title, QString ws);

public slots:
    void run();

private slots:
    void onConnected();
    void onDisconnected();
    void dataReceived(QString message);

private:
    void send_js(QString cmd);

    QWebSocket *socket;
    QString cmd_buf;
    QString url;
    QString title;
    int     title_state = 0;
};

#endif // RE_FIREFOX_WS_H
