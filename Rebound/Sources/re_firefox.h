#ifndef RE_FIREFOX_H
#define RE_FIREFOX_H

#include <QObject>
#include <QtDebug>
#include <QtWebSockets/QtWebSockets>
#include "backend.h"
#include "re_firefox_ws.h"
#include "re_commands.h"
#include "re_lua.h"

#define RE_FFGEAR_COUNT 16
//                        1    2   3   4   5   6  7  8  9  10
#define RE_FFGEAR_DELAY { 100, 50, 25, 10, 10, 5, 5, 5, 5,  5,  \
                          5  ,  5,  5,  5,  5}
#define RE_FFGEAR_STEP  { 1  , 2 ,  3,  4,  5, 6, 7, 8, 9, 20, \
                          25 , 40, 50, 60, 70}

class ReFirefox : public QObject
{
    Q_OBJECT
public:
    explicit ReFirefox(QObject *parent = nullptr);
    ~ReFirefox();
    void sendScroll();
    void refreshURL();
    void reset();
    void scrollDown(int speed, QString st_cmd);
    void scrollUp(int speed, QString st_cmd);
    void scrollEscape();

    int sc_speed = 5;
    int sc_dir   = 0;  // 0 deactive, other active

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
    QString  status_cmd;
    QString  cmd_buf;
    QString  ws_buf;
    ReLua   *lua;
    int      sc_dirb = 0;  // buffer (not final)
    QVector<ReFirefoxWs *> childs;
    QVector<QThread *>     childs_th;
    int speed_table[RE_FFGEAR_COUNT] = RE_FFGEAR_DELAY;
    int step_table [RE_FFGEAR_COUNT] = RE_FFGEAR_STEP;
};

#endif // RE_FIREFOX_H
