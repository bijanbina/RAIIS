#include "re_admin_win.h"
#include "re_window_w.h"
#include "mm_api.h"

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    ReWindowW *re_win = (ReWindowW *)lParam;
    if( re_isNormalHwnd(hwnd) )
    {
        re_win->addHwnd(hwnd);
    }

    return TRUE;
}

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
    char buffer[128];
    GetClassNameA(hwnd, buffer, 128);
    QString class_name = buffer;

    if( class_name=="CabinetWClass" )
    {
        *(HWND*)lParam = hwnd;
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

int re_cleanRemoteId(QString title)
{
    QStringList split = title.split('-');
    QStringList id_split = split[0].split(" ");

    return id_split[0].toInt();
}

int re_isNormalHwnd(HWND hwnd)
{
    char buffer[128];
    int written = GetWindowTextA(hwnd, buffer, 128);
    if( written==0 || strlen(buffer)==0 )
    {
        return 0;
    }

    if( IsWindowVisible(hwnd)==0 )
    {
        return 0;
    }

    int cloaked;
    DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, 4);
    if( cloaked )
    {
        return 0;
    }

    HWND shell_window = GetShellWindow();
    if( hwnd==shell_window )
    {
        return 0;
    }

    RECT rc;
    GetWindowRect(hwnd, &rc);
    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;
    int opacity = re_getWindowOpacity(hwnd);

    if( width  <MM_MINWIN_WIDTH ||
        height <MM_MINWIN_HEIGHT ||
        opacity<MM_MINWIN_OPACITY ) //|| (rc.bottom<0)
    {
        return 0;
    }

    return 1;
}

ReWindow re_readWindow(HWND hwnd)
{
    ReWindow win;
    char buffer[128];

    int success = GetWindowTextA(hwnd, buffer, 128); //get title
    if ( success==0 )
    {
        qDebug() << hwnd << "Failed to GetWindowTextA";
    }

    win.hWnd = hwnd;
    win.title = buffer;
    win.pname = mm_getPName(mm_getPid(hwnd));
    win.verify = 1; //always new windows are verified

    return win;
}
