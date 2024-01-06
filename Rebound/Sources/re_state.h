#ifndef RE_STATE_H
#define RE_STATE_H

#include <QString>
#include <QQmlProperty>
#include <QFileInfo>
#include "backend.h"
#include "re_firefox.h"
#include "re_commands.h"
#include "re_status_file.h"
#include "ch_monitor.h"

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
    static bool isSleep();
    static void enScroll(int dir, int speed);
    static bool isEscape(CCommand cmd);
    static int  stopFFScroll();

    static int  remote_id;
    static bool sleep_state;
    static bool dictate_state;
    static bool record_state;
    static bool remote_state;
    static bool drag_state;
    static int  ch_count; //Chess Count
    static ReWindow app; //Active Window
    static CCommand last_cmd;
    static ReFirefox *fl;
};

#endif // RE_STATE_H
