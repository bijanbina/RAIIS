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

CCommand ReMeta::castMeta(int meta, int arg)
{
    CCommand cmd; //dummy var
    cmd.type = RE_COMMAND_NATO;
    cmd.val1 = 0;
    cmd.val2 = 0;

    if( arg==0 )
    {
        return cmd;
    }

    if( meta==RE_META_OPEN )
    {
//        QString cmd = re_getOpenCmd(state, arg);
//        system(cmd.toStdString().c_str());
    }
    else if( meta==RE_META_CLOSE )
    {
//        QString cmd = re_getCloseCmd(state, arg);
//        system(cmd.toStdString().c_str());
    }
    else if( meta==RE_META_SYS )
    {
        return castSystemCmd(arg);
    }
    else if( meta==RE_META_START )
    {

    }
    else if( meta==RE_META_FOX )
    {
        castFoxCmd(arg);
    }
    else if( meta==RE_META_PAGE )
    {
        QString cmd = getPageCmd(arg);
        system(cmd.toStdString().c_str());
    }
    else if( meta==RE_META_GO )
    {
        if( arg==RE_APP_SLEEP )
        {
            state->goToSleep();
        }
        else
        {
            QString cmd = getGoCmd(arg);
            system(cmd.toStdString().c_str());
        }
    }
    else if( meta==RE_META_SKY ||
             meta==RE_META_DIVE )
    {
        if( (arg<KEY_1) || (arg>KEY_9) )
        {
            return cmd;
        }
        getScrollCmd(meta, arg-1);
    }
    else if( meta==RE_META_MUSIC )
    {
        QString cmd = getMusicCmd(arg);
        system(cmd.toStdString().c_str());
    }
    else if( meta==RE_META_MOUSE )
    {
        QString cmd = getMouseCmd(arg);
        system(cmd.toStdString().c_str());
    }
    else if( meta==RE_META_TOUCH )
    {
        QString cmd = getTouchCmd(arg);
        system(cmd.toStdString().c_str());
    }

    return cmd;
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

CCommand ReMeta::castSystemCmd(int val)
{
    CCommand cmd; //dummy var
    cmd.type = RE_COMMAND_NATO;
    cmd.val1 = 0;
    cmd.val2 = 0;

    if( val==KEY_A )
    {
        system("xdotool set_desktop 0");
    }
    else if( val>=KEY_1 &&
             val<=KEY_9 )
    {
        int desktop_id = val-KEY_1;
        state->super->virt->setDesktop(desktop_id);
    }
    else if( val==KEY_T )
    {
        system("gnome-terminal");
    }
    else if( val==KEY_V )
    {
        system("~/.config/polybar/awesomewm/vpn_switch.sh");
    }
    else
    {
        qDebug() << "Unknown System" << val;
    }

    return cmd;
}

CCommand ReMeta::castFoxCmd(int val)
{
    CCommand cmd; //dummy var
    cmd.type = RE_COMMAND_NATO;
    cmd.val1 = 0;
    cmd.val2 = 0;
    state->last_cmd.type = RE_COMMAND_NULL;

    if( val==RE_APP_LINK )
    {
        cmd.mod_list.append(KEY_CTRL);
        cmd.val1 = KEY_F;

        cmd.val2 = 1;
        cmd.val3 = 1;
        cmd.type  = RE_COMMAND_MOD;
        cmd.state = RE_CSTATE_0;
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

    if( state->app.pname==RE_PROC_EDITOR )
    {
        cmd = re_getGoXed(val);
    }
    else if( state->app.pname==RE_PROC_QT ||
             state->app.pname==RE_PROC_VSCODE )
    {
        cmd = re_getGoQt(val);
    }
    else if( state->app.pname==RE_PROC_GIT )
    {
        cmd = re_getGoGitKraken(val);
    }
    else if( state->app.pname==RE_PROC_FIREFOX ||
             state->app.pname==RE_PROC_GEKO )
    {
        cmd = re_getGoFirefox(val);
    }
    else if( state->app.pname==RE_PROC_EXPLORER )
    {
        cmd = re_getGoNautilus(val);
    }

    return cmd;
}

QString ReMeta::getPageCmd(int val)
{
    QString cmd;

    qDebug() << "Page" << state->app.pname;

    if( state->app.pname==RE_PROC_EDITOR )
    {
//        cmd = re_getGoXed(val);
    }
    else if( state->app.pname==RE_PROC_QT ||
             state->app.pname==RE_PROC_VSCODE )
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
