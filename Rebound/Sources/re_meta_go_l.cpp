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

    if( val==KEY_LEFT )
    {
        cmd = "xdotool click 1";
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

    if( val==KEY_B ) //focus
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
    else if( val==KEY_R ) //focus
    {
        system("xdotool type 'Rebound-Linux: '");
    }
    else if( val==KEY_F ) //focus
    {
        system("xdotool key --delay 200 super+ctrl+k");
        QThread::msleep(100); //little tweak
        cmd = "xdotool key --delay 200 super+ctrl+k";
    }
    else if( val>0 && val<10 ) //tab
    {
        cmd = "xdotool key ctrl+";
        cmd += QString::number(val);
        qDebug() << "KEY_0" << cmd;
    }

    return cmd;
}
