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


// First 100 used for ASCII characters
#define RE_SUPER_META    201
#define RE_SUPER_CAMEL   202 //currently colon
#define RE_SUPER_SWITCH  203
#define RE_SUPER_KICK    204
#define RE_SUPER_COMMENT 205
#define RE_SUPER_COPY    206
#define RE_SUPER_PASTE   207
#define RE_SUPER_SIDE    208
#define RE_SUPER_LOVE    209
#define RE_SUPER_ROGER   210
#define RE_SUPER_RESIST  211
#define RE_SUPER_SPOTIFY 212
#define RE_SUPER_DOUBLE  213
#define RE_SUPER_SELECT  214
#define RE_SUPER_DRAG    215
#define RE_SUPER_SHOT    216
#define RE_SUPER_MAGIC   217
#define RE_SUPER_WINDOW  218
#define RE_SUPER_GAS     219
#define RE_SUPER_CARROT  220
#define RE_SUPER_DUKE    221
#define RE_SUPER_MEDIA   222
#define RE_SUPER_FRONT   223
#define RE_SUPER_LAST    224
#define RE_SUPER_POWER   225
#define RE_SUPER_RUN     226
#define RE_SUPER_SKY     227
#define RE_SUPER_DIVE    228
#define RE_SUPER_LAUNCH  229

#define RE_CHESS_KICK    301
#define RE_CHESS_COMMENT 302
#define RE_CHESS_SIDE    303
#define RE_CHESS_DOUBLE  304
#define RE_CHESS_RESIST  305
#define RE_CHESS_DRAG    306
#define RE_CHESS_SHOT    307
#define RE_CHESS_MAGIC   308
#define RE_CHESS_RUN     309

#define RE_MOUSE_LEFT    401
#define RE_MOUSE_MIDDLE  402
#define RE_MOUSE_RIGHT   403
#define RE_MOUSE_UP      404
#define RE_MOUSE_DOWN    405

#define RE_META_OPEN     501
#define RE_META_SYS      502
#define RE_META_START    503
#define RE_META_FOX      504
#define RE_META_PAGE     505
#define RE_META_GO       506
#define RE_META_MUSIC    507
#define RE_META_CLOSE    508
#define RE_META_MOUSE    509


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
    int state = RE_CSTATE_0; //for repeat digithub

    int is_shift = 0;
    int is_ctrl  = 0;
    int is_alt   = 0;
    int is_super = 0; // win key
}CCommand;

bool re_isLastCmdFunction(QVector<CCommand> commands);
bool re_isLastMeta(QVector<CCommand> commands);
bool re_isLastMod(QVector<CCommand> commands);
bool re_isLastQt(QVector<CCommand> commands);
int  re_keyCode2Digit(QString key_code);
int  re_keyCode2Digit(int code);

#endif // RE_COMMANDS_H
