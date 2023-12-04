#ifndef RE_STATE_H
#define RE_STATE_H

#ifdef __linux__
#endif

#include <QObject>
#include <QString>
#include <QQmlProperty>
#include <QFileInfo>
#include "backend.h"
#include "re_firefox.h"
#include "re_commands.h"
#include "re_status_file.h"
#include "ch_monitor.h"

class ReState : public QObject
{
    Q_OBJECT
public:
    explicit ReState(QObject *parent = 0);
    ~ReState();

    void readStatusFile();

    void updateApp(ReWindow active_window);
    void toggleUi(QObject *item);

    void goToSleep();
    void goToDictate();
    void goToRecord();
    void goToRemote();
    void goToDrag();
    void wakeUp();
    bool isSleep();
    void enScroll(int dir, int speed);
    bool isEscape(CCommand command);
    int  resetState();
    void sendPipeChess(const char *data);
    void sendPipeMom(const char *data);

#ifdef _WIN32
    HANDLE connectChessPipe(const char *pipe_name);

    ReHardwareW *hardware;
    HANDLE pipe_chess;
    HANDLE pipe_mom;
#endif
    int  ui_visible;
    int  i_mode;
    bool sleep_state = 0;
    bool dictate_state = 0;
    bool record_state = 0;
    bool remote_state = 0;
    bool drag_state = 0;
    int  ch_count  = 0; //Chess Count
    int  utube_mode  = 0;
    QStringList wins_title;
    QStringList elems_name;
    ReWindow app; //Active Window
    CCommand last_cmd;
    ReFirefox *fl;
    ChMonitor *mon;
};

#endif // RE_STATE_H
