#ifndef RE_CHESS_H
#define RE_CHESS_H

#include <QObject>
#include <QThread>

#include "backend.h"
#include "re_state.h"
#include "re_modifier.h"

#define CH_DRAG_NORM   0
#define CH_DRAG_STATE1 1
#define CH_DRAG_STATE2 2

class ReChess : public QObject
{
    Q_OBJECT
public:
    ReChess(ReState *st, QObject *parent = NULL);
    ~ReChess();

    void dirs (const QString &arg);
    void nato (const QString &arg);
    void super(const QString &arg,
               QVector<CCommand> cmd_buf); //single shot meta cmd
    void digit(const QString &arg);

    void showChess(int val);
    int  isChessCmd(QString text);
    void sendChessCmd(QString cmd, QString arg="");
    void setCount(int val);

private:
    void sendChessKey(QString text);
    void resetChess();
    void handleBackspace();
    void addCount(int val);

    QObject   *root;
    ReState   *state;
    CCommand   mod_cmd;


    int meta_mode;
    int drag_mode;
    int persist_mode;
    QString commands_str; //just for debug purpose
};

#endif // RE_CHESS_H
