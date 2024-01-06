#include "re_admin_win.h"
#include "re_window_w.h"

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char buffer[128];
    ReWindowW *thread_w = (ReWindowW *)lParam;
    int written = GetWindowTextA(hwnd, buffer, 128);
    if( written && strlen(buffer)!=0 )
    {
        re_AddHwnd(hwnd, thread_w);
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
