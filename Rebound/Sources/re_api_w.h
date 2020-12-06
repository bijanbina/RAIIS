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

#define RE_WIN_UNKNOWN     1
#define RE_WIN_SPOTIFY     2
#define RE_WIN_FIREFOX     3
#define RE_WIN_EXPLORER    4
#define RE_WIN_READING     5
#define RE_WIN_QT          6
#define RE_WIN_TEXTEDITOR  7
#define RE_WIN_OVERVIEW    8
#define RE_WIN_TELEGRAM    9
#define RE_WIN_TERMINAL    10
#define RE_WIN_YOUTUBE     11

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
    QString getLinkPathB(QString path);

    QStringList wins_title;
    QStringList elems_name;

private slots:

private:
};

#endif // REAPIW_H
