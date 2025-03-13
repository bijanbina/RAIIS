#ifndef BACKEND_H
#define BACKEND_H

#include <QQmlApplicationEngine>
#include <QQmlProperty>
#include <QDebug>
#include <stdio.h>
#include <unistd.h>
#include "re_config.h"

#ifdef _WIN32
    #include <windows.h>
#endif

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

QString getDiffTime(clock_t start);

#ifdef _WIN32
void executeAhk(QString name);
void executScript(QString name, int id);
int  isWinExplorer(QString title);
#endif

#endif // BACKEND_H
