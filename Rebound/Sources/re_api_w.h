#ifndef REAPIW_H
#define REAPIW_H

#include <QObject>

#include "Windows.h"
#include <psapi.h> // For access to GetModuleFileNameEx
#include <tchar.h> // to get file path
#include <tlhelp32.h> // to get pid
#include <QStringList>
#include <oleacc.h>
#include <dwmapi.h>

typedef struct ReWinSpec
{
    QString title;
    HWND hWnd;
    IAccessible *pAcc;
}ReWinSpec;

typedef struct ReElemSpec
{
    QString name;
    IAccessible *pAcc;
}ReElemSpec;

class ReApiW : public QObject
{
    Q_OBJECT
public:
    explicit ReApiW(QObject *parent = nullptr);
    QString reGetPNameA();
    QString reRenameAppName(QString app_name);
    QString reMakeTitleTidy(QString title);
    long reGetPid(HWND hWnd);
    QString reGetPName(long pid);

    QStringList win_title;
    QVector<ReWinSpec*> wins_spec;
    QVector<ReElemSpec*> elems_spec;

private:
    void bijSortTitles();
    HWND getHWND(QString title);
    ReWinSpec* getWinSpec(QString title);
    QStringList listAllElements(QString Title, QString parent_path, QString child_path);
    IAccessible* reGetPAcc(HWND hWnd);
    QString reGetAccName(IAccessible *pAcc, long childId);
    long reGetChildCount(IAccessible *pAcc);
    IAccessible* reFindAcc(QString path, IAccessible *pAcc);
    void reListChildren(IAccessible *pAcc, QString path);
};

#endif // REAPIW_H
