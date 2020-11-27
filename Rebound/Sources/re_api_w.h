#ifndef REAPIW_H
#define REAPIW_H

#include <QObject>
#include <QtDebug>
#include "Windows.h"
#include <psapi.h> // For access to GetModuleFileNameEx
#include <tchar.h> // to get file path
#include <tlhelp32.h> // to get pid
#include <QStringList>
#include <oleacc.h>
#include <dwmapi.h>
#include <shobjidl.h>
#include <shlguid.h>

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
#define RE_PROC_TELEGRAM    8

class ReApiW : public QObject
{
    Q_OBJECT
public:
    explicit ReApiW(QObject *parent = nullptr);
    QString getPNameA();
    long getPid(HWND hWnd);
    QString getPName(long pid);
    QString getAccName(IAccessible *pAcc, long childId);
    QString getWinTitle(int index);
    QString getElemName(int index);
    void setActiveWindow(HWND hWnd);
    void openApp(int appid);
    QString getLinkPath(QString path);

    QStringList wins_title;
    QStringList elems_name;

private slots:

private:
};

#endif // REAPIW_H
