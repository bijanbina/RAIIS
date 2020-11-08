#ifndef BACKEND_H
#define BACKEND_H

#include <QQmlApplicationEngine>
#include <QQmlProperty>
#include <QDebug>
#include <stdio.h>
#include <unistd.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#define COM_NAME "com.binaee.assistant"
#define ORG_NAME "org.binaee.assistant"
#define ASSISTANT_PATH "/home/bijan/Project/Assistant/"

#define RE_CLIENT 0
#define RE_SERVER 1

#define RE_PORT      7610
#define RE_IP        "192.168.88.25"

//#define RE_TEST_EN
//#define RE_DUBUG_TCP

#define RE_TIMEOUT    1000
#define RE_WATCHDOG   1000  //Watchdog interval
#define RE_Live       100   //Live send interval
#define RE_CHECK_BTN  4     //Live send interval
#define RE_CHECK_IN   4     //check input(native mode)
#define RE_TAB_TIME   900   //Alt pressed time

struct screen_pos{
    int x;
    int y;
};

struct assistant_options{
    bool strictLoad;
    int  timeout;
    int  currentLanguage;
} ;

assistant_options loadOptions();

int getIntCommand(char *command);
QString getStrCommand(QString *command);

screen_pos getPrimaryScreen();
void changeLaguageBack();

void updateScreenInfo(QObject *item);

void hideItem(QObject *item);
int isItemVisible(QObject *item);

#ifdef _WIN32
void executeAhk(QString name);
void executeUi(QString name);
#endif

#endif // BACKEND_H
