#ifndef RESTATE_H
#define RESTATE_H

#ifdef __linux__
#endif

#include <QObject>
#include <QString>
#include <QQmlProperty>
#include "re_commands.h"

class ReState : public QObject
{
    Q_OBJECT
public:
    explicit ReState(QObject *parent = 0);

    void rmStatusFile();
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
