#ifndef RE_COMMANDS_H
#define RE_COMMANDS_H

#ifdef _WIN32
#include "re_hardware_w.h"
#include "re_keyboard_w.h"
#endif
#ifdef __linux__
#include <QObject>
#include <QDebug>
#include <QStringList>
#include "re_keyboard_l.h"
#endif

#define RE_COMMAND_NULL   0
#define RE_COMMAND_DIRS   1
#define RE_COMMAND_NATO   2
#define RE_COMMAND_DIGIT  3
#define RE_COMMAND_MOUSE  4
#define RE_COMMAND_META   5
#define RE_COMMAND_SUPER  6
#define RE_COMMAND_QDIGIT 7
#define RE_COMMAND_CHESS  8

// Repeat count state (2-digit)
#define RE_CSTATE_0  0
#define RE_CSTATE_1  1
#define RE_CSTATE_2  2


#define RE_SUPER_META    101
#define RE_SUPER_CAMEL   102 //currently colon
#define RE_SUPER_SWITCH  103
#define RE_SUPER_KICK    104
#define RE_SUPER_COMMENT 105
#define RE_SUPER_COPY    106
#define RE_SUPER_PASTE   107
#define RE_SUPER_SIDE    108
#define RE_SUPER_LOVE    109
#define RE_SUPER_ROGER   110
#define RE_SUPER_RESIST  111
#define RE_SUPER_SPOTIFY 112
#define RE_SUPER_DOUBLE  113
#define RE_SUPER_SELECT  114
#define RE_SUPER_DRAG    115
#define RE_SUPER_SHOT    116
#define RE_SUPER_MAGIC   117
#define RE_SUPER_WINDOW  118
#define RE_SUPER_GAS     119
#define RE_SUPER_CARROT  120
#define RE_SUPER_DUKE    121
#define RE_SUPER_MEDIA   122
#define RE_SUPER_FRONT   123
#define RE_SUPER_LAST    124
#define RE_SUPER_POWER   125
#define RE_SUPER_RUN     126

#define RE_CHESS_KICK    201
#define RE_CHESS_COMMENT 202
#define RE_CHESS_SIDE    203
#define RE_CHESS_DOUBLE  204
#define RE_CHESS_RESIST  205
#define RE_CHESS_DRAG    206
#define RE_CHESS_SHOT    207
#define RE_CHESS_MAGIC   208
#define RE_CHESS_RUN     209

#define RE_MOUSE_LEFT    301
#define RE_MOUSE_MIDDLE  302
#define RE_MOUSE_RIGHT   303
#define RE_MOUSE_UP      304
#define RE_MOUSE_DOWN    305

#define RE_META_OPEN     401
#define RE_META_SYS      402
#define RE_META_START    403
#define RE_META_FOX      404
#define RE_META_PAGE     405
#define RE_META_GO       406
#define RE_META_SKY      407
#define RE_META_DIVE     408
#define RE_META_MUSIC    409
#define RE_META_CLOSE    410
#define RE_META_MOUSE    411
#define RE_META_TOUCH    412

typedef struct ReWindow
{
    // Verify Clear On Each Enumeration To
    int  verify; //verify hwnd still exist
    QString title;
    QString pname;
    int pid;
#ifdef _WIN32
    HWND hWnd;
#endif
#ifdef __linux__
    unsigned long hWnd;
    int desktop_id;
#endif
}ReWindow;

// Captain Command
typedef struct CCommand
{
    int val1;
    int val2;
    int val3;
    int type  = RE_COMMAND_NULL;
    int state = RE_CSTATE_0; //for repeat digit

    int is_shift = 0;
    int is_ctrl  = 0;
    int is_alt   = 0;
    int is_super = 0; // win key
}CCommand;

bool re_isLastCmdFunction(QVector<CCommand> commands);
bool re_isLastMeta(QVector<CCommand> commands);
bool re_isLastMod(QVector<CCommand> commands);
bool re_isLastGo(QVector<CCommand> commands);
bool re_isLastQt(QVector<CCommand> commands);
int  re_keyCode2Digit(QString key_code);
int  re_keyCode2Digit(int code);

#endif // RE_COMMANDS_H
