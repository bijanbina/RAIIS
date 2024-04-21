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


// First 256 used for ASCII characters
#define RE_SUPER_META    301
#define RE_SUPER_CAMEL   302 //currently colon
#define RE_SUPER_SWITCH  303
#define RE_SUPER_KICK    304
#define RE_SUPER_COMMENT 305
#define RE_SUPER_COPY    306
#define RE_SUPER_PASTE   307
#define RE_SUPER_SIDE    308
#define RE_SUPER_LOVE    309
#define RE_SUPER_ROGER   310
#define RE_SUPER_RESIST  311
#define RE_SUPER_SPOTIFY 312
#define RE_SUPER_DOUBLE  313
#define RE_SUPER_SELECT  314
#define RE_SUPER_DRAG    315
#define RE_SUPER_SHOT    316
#define RE_SUPER_MAGIC   317
#define RE_SUPER_WINDOW  318
#define RE_SUPER_GAS     319
#define RE_SUPER_CARROT  320
#define RE_SUPER_DUKE    321
#define RE_SUPER_MEDIA   322
#define RE_SUPER_FRONT   323
#define RE_SUPER_LAST    324
#define RE_SUPER_POWER   325
#define RE_SUPER_RUN     326
#define RE_SUPER_SKY     327
#define RE_SUPER_DIVE    328
#define RE_SUPER_LAUNCH  329
#define RE_SUPER_JAMES   330
#define RE_SUPER_NEXT    331
#define RE_SUPER_WEST    332

#define RE_CHESS_KICK    401
#define RE_CHESS_COMMENT 402
#define RE_CHESS_SIDE    403
#define RE_CHESS_DOUBLE  404
#define RE_CHESS_RESIST  405
#define RE_CHESS_DRAG    406
#define RE_CHESS_SHOT    407
#define RE_CHESS_MAGIC   408
#define RE_CHESS_RUN     409

#define RE_MOUSE_LEFT    501
#define RE_MOUSE_MIDDLE  502
#define RE_MOUSE_RIGHT   503
#define RE_MOUSE_UP      504
#define RE_MOUSE_DOWN    505

#define RE_META_OPEN     601
#define RE_META_SYS      602
#define RE_META_START    603
#define RE_META_FOX      604
#define RE_META_PAGE     605
#define RE_META_POWER    606
#define RE_META_MUSIC    607
#define RE_META_CLOSE    608
#define RE_META_MOUSE    609


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
