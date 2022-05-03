#include "re_meta_go_l.h"

QString re_getGoXed(int val)
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

QString re_getGoQt(int val)
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
    else if( val==KEY_M )
    {
        cmd = "xdotool click 2";
    }
    else if( val==KEY_RIGHT )
    {
        cmd = "xdotool click 3";
    }
    else if( val==KEY_F ) //focus
    {
        system("xdotool key --delay 200 super+ctrl+k");
        QThread::msleep(100); //little tweak
        cmd = "xdotool key --delay 200 super+ctrl+k";
    }

    return cmd;
}

QString re_getGoGitKraken(int val)
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

QString re_getGoFirefox(int val)
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

QString re_getGoNautilus(int val)
{
    QString cmd;
    if( val==KEY_BACKSPACE )
    {
        cmd = "xdotool key alt+Up";
    }
    return cmd;
}
