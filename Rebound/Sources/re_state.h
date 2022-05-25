#ifndef RE_STATE_H
#define RE_STATE_H

#ifdef __linux__
#endif

#include <QObject>
#include <QString>
#include <QQmlProperty>
#include <QFileInfo>
#include "re_commands.h"
#include "re_state_const.h"
//#include "re_firefox_l.h"

class ReState : public QObject
{
    Q_OBJECT
public:
    explicit ReState(QObject *parent = 0);

    void rmStatusFile();
    void rmSpexFile();
    void setMode(int mode);
    int  getMode();

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
    bool isEscape(CCommand command);
    void resetState();

#ifdef _WIN32
    ReApiW *api;
    ReHardwareW *hardware;
#endif
#ifdef __linux__
//    ReApiL *api;
#endif
    int  ui_visible;
    int  i_mode;
    bool sleep_state = 0;
    int  scroll_spd  = 0;
    int  scroll_dir  = 0; // 0 deactive, other active
    bool chess_mode  = 0;
    int  utube_mode  = 0;
    ReWindow app; //Active Window
    CCommand last_cmd;
    ReFirefoxL *fl;

signals:
    void updateMode();

private:
    int i_proc;
};

#endif // RESTATE_H
