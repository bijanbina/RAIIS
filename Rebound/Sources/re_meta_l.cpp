#include "re_meta_l.h"

ReMetaL::ReMetaL(ReState *st, QObject *parent): QObject(parent)
{
    state = st;
}

ReMetaL::~ReMetaL()
{
    ;
}

void ReMetaL::execMeta(CaptainCommand command)
{
    if( command.val2==0 )
    {
        return;
    }

    if( command.val1==RE_META_OPEN )
    {
        QString cmd = "./Scripts/open ";
        cmd += QString::number(command.val2)+ " &";
        system(cmd.toStdString().c_str());
    }
    else if( command.val1==RE_META_SYS )
    {
        QString cmd = getSystemCmd(command.val2);

        if( command.val3==0 )
        {
            command.val3 = 1; //change default to 1
        }

        for( int j=0 ; j<command.val3 ; j++ )
        {
            system(cmd.toStdString().c_str());
        }
    }
    else if( command.val1==RE_META_START )
    {

    }
    else if( command.val1==RE_META_FOX )
    {
        if( command.val2==RE_APP_DING )
        {
            QString cmd = "xdotool key Ctrl+F";
            cmd += " &";
            system(cmd.toStdString().c_str());
        }
        if( command.val2==RE_APP_LINK )
        {
            QString cmd = "xdotool key Ctrl+F";
            cmd += " &";
            system(cmd.toStdString().c_str());
        }
    }
    else if( command.val1==RE_META_PAGE )
    {

    }
    else if( command.val1==RE_META_GO )
    {
        if( command.val2==RE_APP_SLEEP )
        {
            state->goToSleep();
        }
    }
    else if( command.val1==RE_META_SKY ||
             command.val1==RE_META_DIVE )
    {
        QString cmd = getScrollCmd(state->scroll_mode,
                                   command.val1, command.val2);
        state->enScroll(command.val1, command.val2);
        system(cmd.toStdString().c_str());
    }
    else if( command.val1==RE_META_MUSIC )
    {
        QString cmd = getMusicCmd(command.val2);

        if( command.val3==0 )
        {
            command.val3 = 1; //change default to 1
        }

        for( int j=0 ; j<command.val3 ; j++ )
        {
            system(cmd.toStdString().c_str());
        }
    }
    else if( command.val1==RE_META_SWITCH )
    {
        QString cmd = getSwitchCmd(command.val2);
        system(cmd.toStdString().c_str());
    }
    else if( command.val1==RE_META_MOUSE )
    {
        QString cmd = getMouseCmd(command.val2);
        system(cmd.toStdString().c_str());
    }
    else if( command.val1==RE_META_META )
    {
        QString cmd = getSwitchCmd(command.val2);
        system(cmd.toStdString().c_str());
    }
}

QString ReMetaL::getMouseCmd(int val)
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
    else
    {
        qDebug() << "Unknown Switch" << val;
        return "";
    }

    return cmd;
}


QString ReMetaL::getSwitchCmd(int val)
{
    QString cmd = "./Scripts/switcher ";

    if( val==RE_APP_GITHUB )
    {
        cmd += "gitkraken";
    }
    else if( val==RE_APP_FIREFOX )
    {
        cmd += "firefox";
    }
    else if( val==RE_APP_FILES )
    {
        cmd += "nautilus";
    }
    else if( val==RE_APP_SPOTIFY )
    {
        cmd += "spotify";
    }
    else if( val==RE_APP_ATOM )
    {
        cmd += "gedit";
    }
    else if( val==KEY_LEFT )
    {
        cmd = "xdotool key Super+Shift+Left";
    }
    else if( val==KEY_RIGHT )
    {
        cmd = "xdotool key Super+Shift+Right";
    }
    else if( val==KEY_Q )
    {
        cmd += "Qt";
    }
    else if( val==KEY_T )
    {
        cmd += "Terminal";
    }
    else
    {
        qDebug() << "Unknown Switch" << val;
        return "";
    }

    return cmd;
}

QString ReMetaL::getSystemCmd(int val)
{
    QString cmd;

    if( val==KEY_A )
    {
        cmd = "xdotool set_desktop 0";
    }
    else if( val==KEY_B )
    {
        cmd = "xdotool set_desktop 1";
    }
    else if( val==KEY_C )
    {
        cmd = "xdotool set_desktop 2";
    }
    else if( val==KEY_D )
    {
        cmd = "xdotool set_desktop 3";
    }
    else if( val==KEY_E )
    {
        cmd = "xdotool set_desktop 4";
    }
    else if( val==KEY_T )
    {
        cmd = "gnome-terminal";
    }
    else if( val==KEY_V )
    {
        cmd = "~/.config/polybar/awesomewm/vpn_switch.sh";
    }
    else if( val==KEY_LEFT )
    {
        cmd = "xdotool key --delay 200 Ctrl+Super+k";
    }
    else if( val==KEY_RIGHT )
    {
        cmd = "xdotool key --delay 200 Ctrl+Super+k";
    }
    else if( val==KEY_CLOSE )
    {
        cmd = "xdotool key Alt+F4";
    }
    else
    {
        qDebug() << "Unknown System" << val;
        return "";
    }

    return cmd;
}

QString ReMetaL::getMusicCmd(int val)
{
    QString cmd = "dbus-send --print-reply --dest="
                  "org.mpris.MediaPlayer2.spotify "
                  "/org/mpris/MediaPlayer2 ";

    if( val==KEY_ENTER )
    {
        cmd += "org.mpris.MediaPlayer2.Player.PlayPause";
    }
    else if( val==KEY_LEFT )
    {
        cmd += "org.mpris.MediaPlayer2.Player.Previous";
    }
    else if( val==KEY_RIGHT )
    {
        cmd += "org.mpris.MediaPlayer2.Player.Next";
    }
    else
    {
        qDebug() << "Unknown Music" << val;
        return "";
    }

    cmd += " >/dev/null";

    return cmd;
}

QString ReMetaL::getScrollCmd(bool scroll_mode, int meta, int val)
{
    QString change_gear;
    QString direction;
    QString cmd = "./Scripts/scroll";
    if( scroll_mode )
    {
        change_gear = " 0 ";
    }
    else
    {
        change_gear = " 1 ";
    }

    if( meta==RE_META_SKY )
    {
        direction = " up ";
    }
    else if( meta==RE_META_DIVE )
    {
        direction = " down ";
    }

    cmd += direction;
    cmd += change_gear;
    cmd += QString::number(val);

    return cmd;
}
