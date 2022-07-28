#include "re_keyboard_w.h"

void re_mouseKey(int btn)
{
#ifdef WIN32
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dx = 0;
    input.mi.dy = 0;

    if( btn==1 )
    {
        input.mi.dwFlags=(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP);
    }
    else if( btn==2 )
    {
        input.mi.dwFlags=(MOUSEEVENTF_MIDDLEDOWN|MOUSEEVENTF_MIDDLEUP);
    }
    else if( btn==3 )
    {
        input.mi.dwFlags=(MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP);
    }

    input.mi.mouseData = 0;
    input.mi.dwExtraInfo = NULL;
    input.mi.time = 0;
    SendInput(1, &input,sizeof(INPUT));
#else
    QString cmd = "xdotool click ";;

    cmd += QString::number(btn);
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
