#ifndef RE_META_L_H
#define RE_META_L_H

#include <QVector>
#include <linux/uinput.h>

#include "backend.h"
#include "re_state.h"

#define RE_COMMAND_DIRS   1
#define RE_COMMAND_NATO  2
#define RE_COMMAND_DIGIT 3
#define RE_COMMAND_MOD   4 //Modifiers
#define RE_COMMAND_META  5

#define RE_META_OPEN    1
#define RE_META_SYS     2
#define RE_META_START   3
#define RE_META_FOX     4
#define RE_META_PAGE    5
#define RE_META_GO      6
#define RE_META_SKY     7
#define RE_META_DIVE    8
#define RE_META_MUSIC   9
#define RE_META_CLOSE   10
#define RE_META_SWITCH  11

#define RE_APP_GITHUB   301
#define RE_APP_FIREFOX  302
#define RE_APP_FILES    303
#define RE_APP_SPOTIFY  304
#define RE_APP_ATOM     305
#define RE_APP_DING     306 //fox ding
#define RE_APP_LINK     307 //fox link
#define RE_APP_SLEEP    308 //go sleep

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
    QString getSwitchCmd(int val);
    QString getScrollCmd(bool scroll_mode, int meta, int val);

    int uinput_f;

    ReState *state;
};



#endif // RE_META_L_H
