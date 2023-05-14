#ifndef MM_API_H
#define MM_API_H

#include <QString>
#include <Windows.h>

typedef struct MmApplication
{
    QString shortcut_name;
    QString exe_name;
    QString exe_path;
    QString working_dir;
    QString win_title;
    DWORD pid = 0;
    QString pname;
    int workspace;
    HWND hwnd = 0;
}MmApplication;

void mm_launchApp(MmApplication *app, QString arg="");
void mm_launchScript(QString path, QString arg="");
void mm_launchLnk(QString app_name, QString arg="");
void mm_getLinkPath(QString path, MmApplication *app);
void mm_getLinkPathUser(QString path, MmApplication *app);
void mm_getLinkPathAll(QString path, MmApplication *app);
HRESULT mm_ResolveIt(LPCSTR lnk_path, MmApplication *app);

#endif // MM_API_H
