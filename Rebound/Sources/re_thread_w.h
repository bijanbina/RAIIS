#ifndef RE_THREAD_W_H
#define RE_THREAD_W_H

#include <QStringList>

#include "re_state.h"
#include "re_win32_acc.h"
#include "re_win32_win.h"

#include <dwmapi.h>
#include <tlhelp32.h> // to get pid
#include <tchar.h> // to get file path
#include <psapi.h> // For access to GetModuleFileNameEx

#define RE_SPOTIFY_ALBUM_CHILD  "0000"
#define RE_SPOTIFY_ALBUM_PARENT "301000000201201"

#define RE_EXPLORER_ID 0
#define RE_FIREFOX_ID  1
#define RE_SPOTIFY_ID  2

typedef struct threadStruct
{
    QString  message;
    ReState *state;
    QStringList *wins_title;
    QStringList *elems_name;
    QVector<ReWindow> windows;
    ReKeyEmulator    *key;
}threadStruct;

class ReThreadW
{
public:
    ReThreadW(threadStruct *thread_data);
    void cleanWins();
    void clearWins();
    void selectButton(QString name);
    QString cleanTitle(QString title);
    void sortApp();
    void syncWinsTitle();
    void updateActiveWindow();

    QVector<ReWindow> windows;
    threadStruct *thread_data;
    QStringList elems_name;
    ReWindow win_active;

private:
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

int reSelectButton(QString name);

void reRunThread(void *thread_struct_void);
void reCleanWins(threadStruct *thread_data);
void reCleanElems(threadStruct *thread_data);

#endif // RE_THREAD_W_H
