#ifndef MM_API_H
#define MM_API_H

#include <QString>
#ifdef WIN32
#include <Windows.h>
#endif
#define MAX_TITLE_LEN 200

typedef struct MmApplication
{
    QString shortcut_name;
    QString exe_name;
    QString exe_path;
    QString working_dir;
    QString win_title;
    QString pname;
    int workspace;
#ifdef WIN32
    DWORD pid = 0;
    HWND hwnd = 0;
#endif
}MmApplication;

#ifdef WIN32
void mm_focus(HWND hwnd);
void mm_focus(MmApplication app);
long mm_getPid(HWND hWnd);
HWND mm_getHWND(MmApplication *app);
void mm_launchApp(MmApplication *app, QString arg="");
void mm_launchScript(QString path, QString arg="");
MmApplication mm_launchLnk(QString app_name, QString arg="");
void mm_getLinkPath(QString path, MmApplication *app);
void mm_getLinkPathUser(QString path, MmApplication *app);
void mm_getLinkPathAll(QString path, MmApplication *app);
HRESULT mm_ResolveIt(LPCSTR lnk_path, MmApplication *app);
QString mm_getPName(long pid);
QString mm_getWinTitle(HWND hwnd);
#endif

#endif // MM_API_H
