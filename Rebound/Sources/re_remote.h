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
#include "re_pipe.h"
#endif

#include "re_apache_cl.h"
#include "re_preprocessor.h"
#include "ta_ini.h"

#define BT_BAR_RESULT     "bar_result"
#define BT_BAR_DIR_WS     "..\\..\\Benjamin\\Mom\\Labels\\"
#define BT_BAR_RESULT_WS  "l1_benjamin.lbl"
#define BT_HISTORY_UPDATE 300  // update interval in ms
#define BT_HISTORY_LEN    10   // maximum number of words in history

typedef struct BtHistory
{
    QString word;
    time_t  time;
}BtHistory;

class ReRemote : public QObject
{
    Q_OBJECT
public:
    ReRemote(RePreProcessor *pre, QObject *parent = NULL);
    ~ReRemote();

public slots:
    void send(QString word);
    void shiftHistory();

signals:
    void dirs(const QString &args);
    void nato(QString args);
    void meta(QString args);
    void spex(QString args);
    void type(QString args);
    void super(QString args);
    void digit(QString args);
    void debug(QString args);
    void modifier(QString args);

private slots:
    void readyRead(QString read_data);

private:
    void processCommand(QString k_type, QString k_code);
    int  procSpecialKey(QString word);
    int  procChess(QString word);
    int  procSuper(QString word);
    int  procDigit(QString word);
    int  procMouse(QString word);
    void procScroll(QString word);
    void writeResult();
    void runLua(QString word);
    void wakeRemote();

    QVector<BtHistory>  history;
    QTimer    *timer_history;

    QString last_word;
    int     last_history_count; // keep track of last write count
                                // to prevent unnessary write that
                                // clash with BaTool
    int     is_last_mouse;

    ReApacheCl *apache_rx;
    ReApacheCl *apache_tx;

#ifdef WIN32
    lua_State   *lst;
#endif
};

#endif // RE_REMOTE_H
