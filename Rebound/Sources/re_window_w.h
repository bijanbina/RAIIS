#ifndef RE_WINDOW_W_H
#define RE_WINDOW_W_H

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

#define MM_MINWIN_HEIGHT   600
#define MM_MINWIN_WIDTH    100
#define MM_MINWIN_OPACITY  100

class ReWindowW : public QObject
{
    Q_OBJECT
public:
    explicit ReWindowW();
    void cleanWins();
    void clearWins();
    void selectButton(QString name);
    void sortApp();
    void updateActiveWindow();

    QVector<ReWindow> windows;
    QStringList *wins_title;
    QStringList *elems_name;
    ReKeyboard    *key;
    ReWindow win_active;

public slots:
    void    start();

private:
    HWND    getHWND(QString title);
    QString renameAppName(QString app_name);

    QVector<ReElemSpec*> elems_spec;
    QString getElemName(int index);
    QString getWinTitle(int index);
};

void re_AddHwnd(HWND hwnd, ReWindowW *thread_w);
void re_InsertWindow(ReWindowW *thread_w, ReWindow win);
int  re_cleanRemoteId(QString title);

int reSelectButton(QString name);

#endif // RE_WINDOW_W_H
