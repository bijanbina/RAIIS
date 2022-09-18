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

#define RE_EXPLORER_ID 0
#define RE_FIREFOX_ID  1
#define RE_SPOTIFY_ID  2

typedef struct ReElemSpec
{
    IAccessible *pAcc;
    QString name;
}ReElemSpec;

typedef struct threadStruct
{
    QString  message;
    ReState *state;
    QStringList *wins_title;
    QStringList *elems_name;
    QVector<ReWindow> windows;
    ReKeyboard  *key;
}threadStruct;

class ReThreadW
{
public:
    ReThreadW(threadStruct *thread_data);
    void cleanWins();
    void clearWins();
    void cleanElems();
    void updateElements(QString app_name, QString parent_path, QString child_path);
    void selectButton(QString name);
    QString cleanTitle(QString title);
    void sortApp();
    void syncWinsTitle();
    void syncElemsName();
    void updateActiveWindow();

    QVector<ReWindow> windows;
    threadStruct *thread_data;
    QStringList elems_name;
    ReWindow win_active;

private:
    ReElemSpec* getElemSpec(QString name);
    ReWindow getWinSpec(QString title);
    int getIndex(QString app_name);
    HWND getHWND(QString title);
    QString renameAppName(QString app_name);
    void checkFocus();

    QVector<ReElemSpec*> elems_spec;
    QString getElemName(int index);
    QString getWinTitle(int index);
};

void re_AddHwnd(HWND hwnd, ReThreadW *thread_w);
void re_getType(ReWindow *win);
void re_InsertWindow(ReThreadW *thread_w, ReWindow win);

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

int re_isVpnConnected();

#endif // RE_THREAD_W_H
