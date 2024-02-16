#ifndef RE_CHESS_H
#define RE_CHESS_H

#include <QThread>

#include "backend.h"
#include "re_state.h"
#include "re_modifier.h"
#ifdef WIN32
#include "re_pipe.h"
#endif

#define CH_DRAG_NORM   0
#define CH_DRAG_STATE1 1
#define CH_DRAG_STATE2 2

class ReChess
{
public:
    ReChess();
    ~ReChess();

    static void dirs (const QString &arg);
    static void nato (const QString &arg);
    static void super(const QString &arg,
               QVector<CCommand> cmd_buf); //single shot meta cmd
    static void digit(const QString &arg);

    static void showChess(int val);
    static int  isChessCmd(QString text);
    static void sendCmd(QString cmd, QString arg="");
    static void setCount(int val);

private:
    static void sendChessKey(QString text);
    static void resetChess();
    static void handleBackspace();
    static void addCount(int val);

    static QObject   *root;
    static CCommand   mod_cmd;

    static int meta_mode;
    static int drag_mode;
    static int persist_mode;
};

#endif // RE_CHESS_H
