#ifndef RE_META_L_H
#define RE_META_L_H

#include <QVector>
#include <linux/uinput.h>

#include "backend.h"
#include "re_state.h"

#define RE_COMMAND_KEY   1
#define RE_COMMAND_NATO  2
#define RE_COMMAND_DIGIT 3
#define RE_COMMAND_MOD   4 //Modifiers
#define RE_COMMAND_META  5

#define RE_META_OPEN    1
#define RE_META_SYS     2
#define RE_META_WAKE    3
#define RE_META_START   4
#define RE_META_FOX     5
#define RE_META_PAGE    6
#define RE_META_GO      7
#define RE_META_SKY     8
#define RE_META_DIVE    9
#define RE_META_MUSIC   10
#define RE_META_CLOSE   11

typedef struct CaptainCommand
{
    int val1;
    int val2;
    int val3;
    int type;
}CaptainCommand;


class ReMetaL : public QObject
{
    Q_OBJECT

public:
    ReMetaL(ReState *st, QObject *parent = NULL);
    ~ReMetaL();

    void execMeta(CaptainCommand command);

private:
    QString getMusicCmd(int val);
    QString getSystemCmd(int val);
    QString getScrollCmd(bool scroll_mode, int meta, int val);

    int uinput_f;

    ReState *state;
};



#endif // RE_META_L_H
