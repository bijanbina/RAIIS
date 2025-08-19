#ifndef RE_STATE_H
#define RE_STATE_H

#include <QString>
#include <QQmlProperty>
#include <QFileInfo>
#include <QDir>
#include "backend.h"
#include "re_commands.h"
#include "re_status_file.h"
#include "ch_monitor.h"
#include "re_link_tx.h"
#ifdef _WIN32
#include "re_keyboard_w.h"
#endif
#ifdef __linux__
#include "re_keyboard_l.h"
#endif

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

class ReState
{
public:
    ReState();
    ~ReState();

    static void init();

    static void readStatusFile();

    static void updateApp(ReWindow active_window);

    static void goToSleep();
    static void goToDictate();
    static void goToRecord();
    static void goToRemote(int rid=0);
    static void goToDrag();
    static void wakeUp();
    static void enScroll(int dir, int speed);
    static void setScroll(QString pos);
    static bool isEscape(CCommand cmd);
    static int  stopFFScroll();

    static int  remote_id; // current    pc id
    static int  rust_id;   // controlled pc id
    static int  dim_opacity;
    static bool sleep_state;
    static bool dictate_state;
    static bool record_state;
    static bool remote_state;
    static bool drag_state;
    static int  ch_count; //Chess Count
    static ReWindow  app; //Active Window
    static CCommand  last_cmd;
    static ReLinkTx *link_tx;
};

#endif // RE_STATE_H
