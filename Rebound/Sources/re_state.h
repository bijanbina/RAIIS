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

typedef struct ReWinSpec
{
    // verify clear on each enumeration to
    int  verify; //verify hwnd still exist
    HWND hWnd;
    QString title;
    QString pname;
    IAccessible *pAcc;
}ReWinSpec;

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
    void updateApp(ReWinSpec active_window);
    void toggleUi(QObject *item);
    void propageteMode(int mode);
    void updateTitles(QObject *item);
    void showSwither(QObject *item);

#ifdef _WIN32
    ReApiW *api;
#endif
    int ui_visible;
    int i_mode;
    ReWinSpec app; //Active Window

signals:
    void updateMode();

private:
    int i_proc;
};

#endif // RESTATE_H
