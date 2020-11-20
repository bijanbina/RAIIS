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

    QStringList wins_title;
    QStringList elems_name;

private slots:

private:
};

#endif // REAPIW_H
