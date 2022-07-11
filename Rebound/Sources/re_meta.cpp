#include "re_meta.h"
#ifdef WIN32
#include "re_keyboard_w.h"
#else
#include "re_keyboard_l.h"
#endif

ReMeta::ReMeta(ReState *st, QObject *parent): QObject(parent)
{
    state = st;
}

ReMeta::~ReMeta()
{
    ;
}

void ReMeta::execMeta(CCommand command)
{
    if( command.val2==0 )
    {
        return;
    }

    if( command.val1==RE_META_OPEN )
    {
//        QString cmd = re_getOpenCmd(state, command.val2);
//        system(cmd.toStdString().c_str());
    }
    else if( command.val1==RE_META_CLOSE )
    {
//        QString cmd = re_getCloseCmd(state, command.val2);
//        system(cmd.toStdString().c_str());
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
        getScrollCmd(command.val1, command.val2-1);
    }
    else if( command.val1==RE_META_MUSIC )
    {
        QString cmd = getMusicCmd(command.val2);
        system(cmd.toStdString().c_str());
    }
    else if( command.val1==RE_META_MOUSE )
    {
        QString cmd = getMouseCmd(command.val2);
        system(cmd.toStdString().c_str());
    }
    else if( command.val1==RE_META_TOUCH )
    {
        QString cmd = getTouchCmd(command.val2);
        system(cmd.toStdString().c_str());
    }
}

QString ReMeta::getMouseCmd(int val)
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

QString ReMeta::getSystemCmd(int val)
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
    else if( val==RE_META_CLOSE )
    {
        cmd = "xdotool key Alt+F4";
    }
    else if( val==KEY_UP )
    {
        cmd  = "dbus-send --dest=com.benjamin.chess";
        cmd += " / com.benjamin.chess.show string:\"\"";
    }

    else
    {
        qDebug() << "Unknown System" << val;
        return "";
    }

    return cmd;
}

QString ReMeta::getMusicCmd(int val)
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

void ReMeta::getScrollCmd(int meta, int val)
{
    QString direction;
    if( meta==RE_META_SKY )
    {
        direction = " up ";
    }
    else if( meta==RE_META_DIVE )
    {
        direction = " down ";
    }

    state->enScroll(meta, val);
}

QString ReMeta::getGoCmd(int val)
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
    else if( state->app.pname=="GeckoMain" ||
             state->app.pname=="firefox" )
    {
        cmd = re_getGoFirefox(val);
    }
    else if( state->app.pname=="nautilus" )
    {
        cmd = re_getGoNautilus(val);
    }

    return cmd;
}

QString ReMeta::getPageCmd(int val)
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

QString ReMeta::getTouchCmd(int val)
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
    else if( val==KEY_1 )
    {
        cmd = "xdotool mousemove_relative -- -27 -22";
    }
    else if( val==KEY_2 )
    {
        cmd = "xdotool mousemove_relative -- 0 -22";
    }
    else if( val==KEY_3 )
    {
        cmd = "xdotool mousemove_relative -- 27 -22";
    }
    else if( val==KEY_4 )
    {
        cmd = "xdotool mousemove_relative -- -27 0";
    }
    else if( val==KEY_6 )
    {
        cmd = "xdotool mousemove_relative 22 0";
    }
    else if( val==KEY_7 )
    {
        cmd = "xdotool mousemove_relative -- -27 22";
    }
    else if( val==KEY_8 )
    {
        cmd = "xdotool mousemove_relative 0 22";
    }
    else if( val==KEY_9 )
    {
        cmd = "xdotool mousemove_relative 27 22";
    }

    return cmd;
}
