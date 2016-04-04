#ifndef BACKEND_H
#define BACKEND_H

#include <QQmlApplicationEngine>
#include <QQmlProperty>
#include <stdio.h>
#include <unistd.h>

#define COM_NAME "com.binaee.assistant"
#define ORG_NAME "org.binaee.assistant"
#define ASSISTANT_PATH "/home/bijan/Project/Assistant/"


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
