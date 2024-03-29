#include "re_meta_oc.h"
#ifdef WIN32
#include "re_keyboard_w.h"
#else
#include "re_keyboard_l.h"
#endif

QString re_getOpenXed(int val)
{
    QString cmd;

    if( val==KEY_LEFT )
    {
        cmd = "xdotool key ctrl+alt+Page_Up";
    }
    else if( val==KEY_RIGHT )
    {
        cmd = "xdotool key ctrl+alt+Page_Down";
    }
    else if( val==KEY_F ) //focus
    {
        system("xdotool key --delay 200 super+ctrl+k");
        QThread::msleep(100); //little tweak
        cmd = "xdotool key --delay 200 super+ctrl+k";
    }

    return cmd;
}

QString re_getOpenGitKraken(int val)
{
    QString cmd;

    if( val==KEY_B )
    {
        system("xdotool type 'BaTool: '");
    }
    else if( val==KEY_M )
    {
        cmd = "xdotool key ctrl+M";
    }
    else if( val==KEY_N )
    {
        system("xdotool type 'NATO: '");
    }
    else if( val==KEY_R )
    {
        system("xdotool type 'Rebound-Linux: '");
    }
    else if( val==KEY_F ) //focus
    {
        system("xdotool key --delay 200 super+ctrl+k");
        QThread::msleep(100); //little tweak
        cmd = "xdotool key --delay 200 super+ctrl+k";
    }
    else if( val==KEY_P ) //push
    {
        system("xdotool key ctrl+Enter");
        QThread::msleep(100); //little tweak
        system("xdotool key ctrl+p");
        QThread::msleep(100); //little tweak
        system("xdotool type push");
        QThread::msleep(100); //little tweak
        cmd = "xdotool key Enter";
    }
    else if( val>0 && val<10 ) //tab
    {
        cmd = "xdotool key ctrl+";
        cmd += QString::number(val);
    }

    return cmd;
}

QString re_getOpenFirefox(int val)
{
    QString cmd;

    if( val==KEY_LEFT ) //focus
    {
        cmd = "xdotool key ctrl+shift+Tab";
    }
    else if( val==KEY_RIGHT )
    {
        cmd = "xdotool key ctrl+Tab";
    }
    else if( val==KEY_F ) //find
    {
        cmd = "xdotool key ctrl+F";
    }
    else if( val>0 && val<10 ) //tab
    {
        cmd = "xdotool key alt+";
        cmd += QString::number(val);
    }

    return cmd;
}

QString re_getOpenNautilus(int val)
{
    QString cmd;
    if( val==KEY_BACKSPACE )
    {
        cmd = "xdotool key alt+Up";
    }
    return cmd;
}

QString re_getCloseXed(int val)
{
    QString cmd;

    if( val==KEY_LEFT )
    {
        cmd = "xdotool key ctrl+alt+Page_Up";
    }
    else if( val==KEY_RIGHT )
    {
        cmd = "xdotool key ctrl+alt+Page_Down";
    }
    else if( val==KEY_F ) //focus
    {
        system("xdotool key --delay 200 super+ctrl+k");
        QThread::msleep(100); //little tweak
        cmd = "xdotool key --delay 200 super+ctrl+k";
    }

    return cmd;
}

QString re_getCloseGitKraken(int val)
{
    QString cmd;

    if( val==KEY_B )
    {
        system("xdotool type 'BaTool: '");
    }
    else if( val==KEY_M )
    {
        cmd = "xdotool key ctrl+M";
    }
    else if( val==KEY_N )
    {
        system("xdotool type 'NATO: '");
    }
    else if( val==KEY_R )
    {
        system("xdotool type 'Rebound-Linux: '");
    }
    else if( val==KEY_F ) //focus
    {
        system("xdotool key --delay 200 super+ctrl+k");
        QThread::msleep(100); //little tweak
        cmd = "xdotool key --delay 200 super+ctrl+k";
    }
    else if( val==KEY_P ) //push
    {
        system("xdotool key ctrl+Enter");
        QThread::msleep(100); //little tweak
        system("xdotool key ctrl+p");
        QThread::msleep(100); //little tweak
        system("xdotool type push");
        QThread::msleep(100); //little tweak
        cmd = "xdotool key Enter";
    }
    else if( val>0 && val<10 ) //tab
    {
        cmd = "xdotool key ctrl+";
        cmd += QString::number(val);
    }

    return cmd;
}

QString re_getCloseFirefox(int val)
{
    QString cmd;

    if( val==KEY_LEFT ) //focus
    {
        cmd = "xdotool key ctrl+shift+Tab";
    }
    else if( val==KEY_RIGHT )
    {
        cmd = "xdotool key ctrl+Tab";
    }
    else if( val==KEY_F ) //find
    {
        cmd = "xdotool key ctrl+F";
    }
    else if( val>0 && val<10 ) //tab
    {
        cmd = "xdotool key alt+";
        cmd += QString::number(val);
    }

    return cmd;
}

QString re_getCloseNautilus(int val)
{
    QString cmd;
    if( val==KEY_BACKSPACE )
    {
        cmd = "xdotool key alt+Up";
    }
    return cmd;
}
