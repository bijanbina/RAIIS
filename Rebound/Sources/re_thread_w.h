#ifndef RE_THREAD_W_H
#define RE_THREAD_W_H

#include <QStringList>

#include "re_state.h"

#include <oleacc.h>
#include <dwmapi.h>
#include "Windows.h"
#include <tlhelp32.h> // to get pid
#include <tchar.h> // to get file path
#include <psapi.h> // For access to GetModuleFileNameEx

#define RE_SPOTIFY_ALBUM_CHILD  "0000"
#define RE_SPOTIFY_ALBUM_PARENT "301000000201201"

typedef struct ReWinSpec
{
    HWND hWnd;
    QString title;
    IAccessible *pAcc;
}ReWinSpec;

typedef struct ReElemSpec
{
    IAccessible *pAcc;
    QString name;
}ReElemSpec;

typedef struct threadStruct
{
    int *mode;
    QString message;
    QStringList *wins_title;
    QStringList *elems_name;
}threadStruct;

class ReThreadW
{
public:
    ReThreadW(threadStruct *thread_data);
    void cleanWins();
    void cleanElems();
    void updateElements(QString app_name, QString parent_path, QString child_path);
    void selectButton(QString name);
    QString cleanTitle(QString title);
    void sortTitles();
    void syncWinsTitle();
    void syncElemsName();


    QVector<ReWinSpec> wins_spec;
    threadStruct *thread_data;
    QStringList wins_title;
    QStringList elems_name;

private:
    ReElemSpec* getElemSpec(QString name);
    ReWinSpec getWinSpec(QString title);
    int getIndex(QString app_name);
    HWND getHWND(QString title);
    QString renameAppName(QString app_name);

    QVector<ReElemSpec*> elems_spec;
    QString getElemName(int index);
    QString getWinTitle(int index);
};

void re_AddHwnd(HWND hwnd, ReThreadW *thread_win);
long reGetPid(HWND hWnd);
QString reGetPName(long pid);
IAccessible* reGetPAcc(HWND hWnd);
long reGetChildCount(IAccessible *pAcc);
void reListChildren(IAccessible *pAcc, QString path);
QString reGetAccName(IAccessible *pAcc, long childId);
IAccessible* reFindAcc(QString path, IAccessible *pAcc);
int reSelectButton(QString name);

void reRunThread(void *thread_struct_void);
void reCleanWins(threadStruct *thread_data);
void reCleanElems(threadStruct *thread_data);

#endif // RE_THREAD_W_H
