#include "re_mouse.h"
#ifdef WIN32
#include "re_keyboard_w.h"
#include <Windows.h>
#endif

void re_mouseKey(int btn)
{
#ifdef WIN32
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dx = 0;
    input.mi.dy = 0;
    input.mi.mouseData = 0;

    if( btn==1 )
    {
        input.mi.dwFlags = (MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP);
    }
    else if( btn==2 )
    {
        input.mi.dwFlags = (MOUSEEVENTF_MIDDLEDOWN|MOUSEEVENTF_MIDDLEUP);
    }
    else if( btn==3 )
    {
        input.mi.dwFlags = (MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP);
    }
    else if( btn==4 )
    {
        input.mi.dwFlags = MOUSEEVENTF_WHEEL;
        input.mi.mouseData = WHEEL_DELTA;
    }
    else if( btn==5 )
    {
        input.mi.dwFlags = MOUSEEVENTF_WHEEL;
        input.mi.mouseData = -WHEEL_DELTA;
    }

    input.mi.dwExtraInfo = NULL;
    input.mi.time = 0;
    SendInput(1, &input,sizeof(INPUT));
#else
    QString cmd = "xdotool click ";;

    cmd += QString::number(btn);
    system(cmd.toStdString().c_str());
#endif
}

void re_mouseMoveR(int x, int y)
{
#ifdef WIN32
    POINT pt;
    GetCursorPos(&pt);

    int x2 = pt.x + x;
    int y2 = pt.y + y;

    SetCursorPos(x2, y2);
#else
    QString cmd = "xdotool mousemove_relative ";

    if( x<0 )
    {
        cmd += "-- ";
    }
    cmd += QString::number(x);
    cmd += " ";
    cmd += QString::number(y);
#endif
}

void re_mouseMoveW(int x_offset, int y_offset)
{
#ifdef WIN32
    RECT active_rect;
    HWND active_win = GetForegroundWindow();
    GetWindowRect(active_win, &active_rect);
    int x = active_rect.right + x_offset;
    int y = active_rect.bottom + y_offset;
    SetCursorPos(x, y);
#endif
}

void re_mousePress(int btn)
{
#ifdef WIN32
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dx = 0;
    input.mi.dy = 0;

    if( btn==1 )
    {
        input.mi.dwFlags=(MOUSEEVENTF_LEFTDOWN);
    }
    else if( btn==2 )
    {
        input.mi.dwFlags=(MOUSEEVENTF_MIDDLEDOWN);
    }
    else if( btn==3 )
    {
        input.mi.dwFlags=(MOUSEEVENTF_RIGHTDOWN);
    }

    input.mi.mouseData = 0;
    input.mi.dwExtraInfo = NULL;
    input.mi.time = 0;
    SendInput(1, &input,sizeof(INPUT));
#endif
}

void re_mouseRelease(int btn)
{
#ifdef WIN32
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dx = 0;
    input.mi.dy = 0;

    if( btn==1 )
    {
        input.mi.dwFlags=(MOUSEEVENTF_LEFTUP);
    }
    else if( btn==2 )
    {
        input.mi.dwFlags=(MOUSEEVENTF_MIDDLEUP);
    }
    else if( btn==3 )
    {
        input.mi.dwFlags=(MOUSEEVENTF_RIGHTUP);
    }

    input.mi.mouseData = 0;
    input.mi.dwExtraInfo = NULL;
    input.mi.time = 0;
    SendInput(1, &input,sizeof(INPUT));
#endif
}
