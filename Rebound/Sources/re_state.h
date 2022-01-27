#ifndef RESTATE_H
#define RESTATE_H

#ifdef __linux__
#endif

#include <QObject>
#include <QString>
#include <QQmlProperty>

#ifdef _WIN32
#include "re_api_w.h"
#include "re_hardware_w.h"
#endif
#ifdef __linux__
#include "re_api_l.h"
#include <X11/Xlib.h>
#endif

#define RE_COMMAND_DIRS  1
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
#define RE_META_MOUSE   12
#define RE_META_META    13

#define RE_META_SUPER   1 //Used for val2

#define RE_APP_GITHUB   301
#define RE_APP_FIREFOX  302
#define RE_APP_FILES    303
#define RE_APP_SPOTIFY  304
#define RE_APP_ATOM     305
#define RE_APP_DING     306 //fox ding
#define RE_APP_LINK     307 //fox link
#define RE_APP_SLEEP    308 //go sleep

#define RE_KEY_FMIN    59 //F1
#define RE_KEY_FMAX    68 //F10

typedef struct ReWindow
{
    // verify clear on each enumeration to
    int  verify; //verify hwnd still exist
    int  type;
    QString title;
    QString pname;
#ifdef _WIN32
    HWND hWnd;
    IAccessible *pAcc;
#endif
#ifdef __linux__
    Window hWnd; //pid
    int pid;
    int desktop_id;
#endif
}ReWindow;

class ReState : public QObject
{
    Q_OBJECT
public:
    explicit ReState(QObject *parent = 0);
    void setMode(int mode);
    int getMode();

    void setProcess(QString name);
    void setProcess(int proc);
    int getProcess();
    void updateApp(ReWindow active_window);
    void toggleUi(QObject *item);
    void propageteMode(int mode);
    void updateTitles(QObject *item);
    void showSwither(QObject *item);

    void goToSleep();
    void wakeUp();
    bool isSleep();
    void enScroll(int dir, int speed);
    void disScroll();

#ifdef _WIN32
    ReApiW *api;
    ReHardwareW *hardware;
#endif
#ifdef __linux__
    ReApiL *api;
#endif
    int  ui_visible;
    int  i_mode;
    int  vpn_connected = 0;
    int  youtube_mode  = 0;
    bool sleep_state = 0;
    bool scroll_mode = 0;
    int  scroll_dir  = 0;
    ReWindow app; //Active Window

signals:
    void updateMode();

private:
    int i_proc;
};

#endif // RESTATE_H
