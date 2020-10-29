#ifndef RESTATE_H
#define RESTATE_H

#include <QObject>
#include <QString>
#include <QQmlProperty>

#ifdef _WIN32
#include "re_api_w.h"
#endif

#define RE_MODE_APPLICATION 1
#define RE_MODE_SWITCH      2
#define RE_MODE_MAIN        3
#define RE_MODE_READING     4
#define RE_MODE_FIREFOX     5
#define RE_MODE_SPOTIFY     6
#define RE_MODE_HIDDEN      7

#define RE_PROC_UNKNOWN     1
#define RE_PROC_SPOTIFY     1
#define RE_PROC_FIREFOX     2
#define RE_PROC_NAUTILUS    3
#define RE_PROC_READING     4
#define RE_PROC_QT          5
#define RE_PROC_GEDIT       6
#define RE_PROC_OVERVIEW    7

class ReState : public QObject
{
    Q_OBJECT
public:
    explicit ReState(QObject *parent = 0);
    void setMode(int mode);
    int getMode();

    void setProcess(QString name);
    void setProcess(int proc);
    int getProcess();
    void updateProcess();
    void toggleUi(QObject *item);
    void propageteMode(int mode);

    ReApiW *api;
    int ui_visible;
    int i_mode;

signals:
    void updateMode();

private:
    int i_proc;
};

#endif // RESTATE_H
