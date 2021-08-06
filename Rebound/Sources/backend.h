#ifndef BACKEND_H
#define BACKEND_H

#include <QQmlApplicationEngine>
#include <QQmlProperty>
#include <QtDBus>
#include <QDebug>
#include <stdio.h>
#include <unistd.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#define COM_NAME "com.binaee.rebound"
#define ORG_NAME "org.binaee.rebound"

#define RE_DEBUG_WIN //show window detection debug info

#define RE_CLIENT 0
#define RE_SERVER 1

#define RE_PORT      7610
#define RE_IP        "192.168.88.25"

//#define RE_TEST_EN
//#define RE_DUBUG_TCP

#define RE_TIMEOUT        1000
#define RE_WATCHDOG       1000  //Watchdog interval
#define RE_Live           100   //Live send interval
#define RE_CHECK_BTN      4     //Live send interval
#define RE_CHECK_IN       4     //check input(native mode)
#define RE_TAB_TIME       900   //Alt pressed time
#define RE_EXEC_TIMEOUT   1500  //Command execution timeout

#define RE_SCR_UI      1     //UI Mode
#define RE_SCR_YOUTUBE 2     //YouTube Mode
#define RE_SCR_SPOTIFY 3     //Spotify Mode

struct screen_pos
{
    int x;
    int y;
};

int getIntCommand(char *command);
QString getStrCommand(QString command);

screen_pos getPrimaryScreen();
void changeLaguageBack();

void updateScreenInfo(QObject *item);

int isItemVisible(QObject *item);

#ifdef _WIN32
void executeAhk(QString name);
void executScript(QString name, int id);
#endif

#endif // BACKEND_H
