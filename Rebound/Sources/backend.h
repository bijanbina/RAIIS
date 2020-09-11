#ifndef BACKEND_H
#define BACKEND_H

#include <QQmlApplicationEngine>
#include <QQmlProperty>
#include <stdio.h>
#include <unistd.h>

#define COM_NAME "com.binaee.assistant"
#define ORG_NAME "org.binaee.assistant"
#define ASSISTANT_PATH "/home/bijan/Project/Assistant/"

#define RE_CLIENT 0
#define RE_SERVER 1

#define RE_PORT      7610
#define RE_IP        "192.168.88.25"

//#define RE_TEST_EN
//#define RE_NATIVE_EN

#define RE_TIMEOUT    1000
#define RE_WATCHDOG   1000  //Watchdog interval
#define RE_Live       100   //Live send interval
#define RE_CHECK_BTN  10    //Live send interval

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

#endif // BACKEND_H
