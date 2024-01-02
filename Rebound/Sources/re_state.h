#ifndef RE_STATE_H
#define RE_STATE_H

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

    void goToSleep();
    void goToDictate();
    void goToRecord();
    void goToRemote(int rid=0);
    void goToDrag();
    void wakeUp();
    bool isSleep();
    void enScroll(int dir, int speed);
    bool isEscape(CCommand cmd);
    int  stopFFScroll();
    void sendPipeChess(const char *data);
    void sendPipeMom(const char *data);

#ifdef _WIN32
    HANDLE connectPipe(const char *pipe_name);

    HANDLE pipe_chess;
    HANDLE pipe_mom;
#endif
    int  remote_id = 0;
    bool sleep_state = 0;
    bool dictate_state = 0;
    bool record_state = 0;
    bool remote_state = 0;
    bool drag_state = 0;
    int  ch_count  = 0; //Chess Count
    QStringList wins_title;
    QStringList elems_name;
    ReWindow app; //Active Window
    CCommand last_cmd;
    ReFirefox *fl;
};

#endif // RE_STATE_H
