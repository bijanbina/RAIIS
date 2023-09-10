#ifndef RE_COMMANDS_H
#define RE_COMMANDS_H

#ifdef _WIN32
#include "re_api_w.h"
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
#define RE_COMMAND_MOD    4 //Modifiers
#define RE_COMMAND_META   5
#define RE_COMMAND_SUPER  6
#define RE_COMMAND_QDIGIT 7

// Repeat count state (2-digit)
#define RE_CSTATE_0  0
#define RE_CSTATE_1  1
#define RE_CSTATE_2  2

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
#define RE_META_MOUSE   11
#define RE_META_TOUCH   12

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

#define RE_APP_FIREFOX  301
#define RE_APP_FILES    302
#define RE_APP_SPOTIFY  303
#define RE_APP_ATOM     304
#define RE_APP_DING     305 //fox ding
#define RE_APP_LINK     306 //fox link
#define RE_APP_SLEEP    307 //go sleep

typedef struct ReWindow
{
    // Verify Clear On Each Enumeration To
    int  verify; //verify hwnd still exist
    int  type;
    QString title;
    QString pname;
    int pid;
#ifdef _WIN32
    HWND hWnd;
    IAccessible *pAcc;
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
    int type = RE_COMMAND_NULL;
    int state = RE_CSTATE_0;
    QVector<int> mod_list; //modifiers list
}CCommand;

bool re_isLastCmdFunction(QVector<CCommand> commands);
bool re_isLastMeta(QVector<CCommand> commands);
bool re_isLastMod(QVector<CCommand> commands);
bool re_isLastGo(QVector<CCommand> commands);
bool re_isLastQt(QVector<CCommand> commands);
int  re_keyCode2Digit(QString key_code);
int  re_keyCode2Digit(int code);

#endif // RE_COMMANDS_H
