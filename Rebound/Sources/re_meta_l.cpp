#include "re_meta_l.h"

ReMetaL::ReMetaL(ReState *st, QObject *parent): QObject(parent)
{
    state = st;
}

ReMetaL::~ReMetaL()
{
    ;
}

void ReMetaL::execMeta(CCommand command)
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
        system(cmd.toStdString().c_str());
    }
    else if( command.val1==RE_META_START )
    {

    }
    else if( command.val1==RE_META_FOX )
    {
        state->last_cmd.type = RE_COMMAND_NULL;
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
        if( command.val2==RE_META_PAGE )
        {
            QString cmd = "xdotool key Ctrl+Alt+g";
            cmd += " &";
            system(cmd.toStdString().c_str());
        }
    }
    else if( command.val1==RE_META_PAGE )
    {
        QString cmd = getPageCmd(command.val2);
        system(cmd.toStdString().c_str());
    }
    else if( command.val1==RE_META_GO )
    {
        if( command.val2==RE_APP_SLEEP )
        {
            state->goToSleep();
        }
        else
        {
            QString cmd = getGoCmd(command.val2);
            system(cmd.toStdString().c_str());
        }
    }
    else if( command.val1==RE_META_SKY ||
             command.val1==RE_META_DIVE )
    {
        if( (command.val2<1) || (command.val2>9) )
        {
            return;
        }
        QString cmd = getScrollCmd(state->scroll_mode,
                                   command.val1, command.val2);
        system(cmd.toStdString().c_str());
    }
    else if( command.val1==RE_META_MUSIC )
    {
        QString cmd = getMusicCmd(command.val2);
        system(cmd.toStdString().c_str());
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
    else if( command.val1==RE_SUPER_META )
    {
        QString cmd = getSwitchCmd(command.val2);
        system(cmd.toStdString().c_str());
    }
    else if( command.val1==RE_SUPER_CAMEL )
    {
        qDebug() << "CreateProcess 1";
        system("./Scripts/camel");
        qDebug() << "CreateProcess 2";
    }
    else if( command.val1==RE_META_TOUCH )
    {
        QString cmd = getTouchCmd(command.val2);
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
    else if( val==KEY_C ) //center
    {
        cmd = "xdotool mousemove 960 540";
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

    if( val==RE_APP_FIREFOX )
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
        state->chess_mode = 1;
        cmd = "echo 'Chess' > ~/.config/polybar/awesomewm/ben_status";
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
        cmd = "xdotool key --delay 200 Super+b";
    }
    else if( val==KEY_RIGHT )
    {
        cmd = "xdotool key --delay 200 Super+b";
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
    QString cmd = "./Scripts/music.sh ";

    if( val==KEY_ENTER )
    {
        cmd += "play";
    }
    else if( val==KEY_LEFT )
    {
        cmd += "prev";
    }
    else if( val==KEY_RIGHT )
    {
        cmd += "next";
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
    QString cmd;
    if( state->app.pname=="GeckoMain" )
    {
        QString change_gear;
        QString direction;
        cmd = "./Scripts/scroll";
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
        state->enScroll(meta, val);
    }
    else
    {
        cmd  = "xdotool key --repeat ";
        cmd += QString::number(val);
        if( meta==RE_META_SKY )
        {
            cmd += " Page_Up";
        }
        else if( meta==RE_META_DIVE )
        {
            cmd += " Page_Down";
        }
    }

    return cmd;
}

QString ReMetaL::getGoCmd(int val)
{
    QString cmd;

    qDebug() << "GO" << state->app.pname;

    if( state->app.pname=="xed" )
    {
        cmd = re_getGoXed(val);
    }
    else if( state->app.pname=="qtcreator" ||
             state->app.pname=="code-oss" )
    {
        cmd = re_getGoQt(val);
    }
    else if( state->app.pname=="gitkraken" )
    {
        cmd = re_getGoGitKraken(val);
    }
    else if( state->app.pname=="GeckoMain" )
    {
        cmd = re_getGoFirefox(val);
    }
    else if( state->app.pname=="nautilus" )
    {
        cmd = re_getGoNautilus(val);
    }

    return cmd;
}

QString ReMetaL::getPageCmd(int val)
{
    QString cmd;

    qDebug() << "Page" << state->app.pname;

    if( state->app.pname=="xed" )
    {
//        cmd = re_getGoXed(val);
    }
    else if( state->app.pname=="qtcreator" ||
             state->app.pname=="code-oss" )
    {
        if( val==KEY_DOWN )
        {
            cmd = "xdotool key --repeat 30 Down";
        }
        if( val==KEY_UP )
        {
            cmd = "xdotool key --repeat 30 Up";
        }
    }
    else
    {
        if( val==KEY_DOWN )
        {
            cmd = "xdotool key Next";
        }
        if( val==KEY_UP )
        {
            cmd = "xdotool key Prior";
        }
    }

    return cmd;
}

QString ReMetaL::getTouchCmd(int val)
{
    QString cmd;

    qDebug() << "Touch" << state->app.pname
             << val;

    if( val==KEY_DOWN )
    {
        cmd = "xdotool mousemove_relative 0 100";
    }
    else if( val==KEY_UP )
    {
        cmd = "xdotool mousemove_relative 0 -100";
    }
    else if( val==KEY_RIGHT )
    {
        cmd = "xdotool mousemove_relative 100 0";
    }
    else if( val==KEY_LEFT )
    {
        cmd = "xdotool mousemove_relative -- -100 0";
    }

    return cmd;
}
