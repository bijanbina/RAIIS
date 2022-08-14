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
//        QString system(re_getOpenCmd(state, arg);
//        system(cmd.toStdString().c_str());
    }
    else if( meta==RE_META_CLOSE )
    {
//        QString system(re_getCloseCmd(state, arg);
//        system(cmd.toStdString().c_str());
    }
    else if( meta==RE_META_SYS )
    {
        castSystemCmd(arg, &cmd);
    }
    else if( meta==RE_META_START )
    {

    }
    else if( meta==RE_META_FOX )
    {
        castFoxCmd(arg, &cmd);
    }
    else if( meta==RE_META_PAGE )
    {
        castPageCmd(arg, &cmd);
    }
    else if( meta==RE_META_GO )
    {
        if( arg==RE_APP_SLEEP )
        {
            state->goToSleep();
        }
        else
        {
            castGoCmd(arg, &cmd);
        }
    }
    else if( meta==RE_META_SKY ||
             meta==RE_META_DIVE )
    {
        if( (arg<KEY_1) || (arg>KEY_9) )
        {
            return cmd;
        }
        execScrollCmd(meta, arg-KEY_1);
    }
    else if( meta==RE_META_MUSIC )
    {
        castMusicCmd(arg, &cmd);
    }
    else if( meta==RE_META_MOUSE )
    {
        castMouseCmd(arg, &cmd);
    }
    else if( meta==RE_META_TOUCH )
    {
        castTouchCmd(arg, &cmd);
    }

    return cmd;
}

void ReMeta::castMouseCmd(int val, CCommand *cmd)
{

    if( val==KEY_LEFT )
    {
        re_mouseKey(1);
    }
    else if( val==KEY_M )
    {
        re_mouseKey(2);
    }
    else if( val==KEY_RIGHT )
    {
        re_mouseKey(3);
    }
#ifndef WIN32
    else if( val==KEY_F ) //focus
    {
        system("xdotool key --delay 200 super+ctrl+k");
        QThread::msleep(100); //little tweak
        system("xdotool key --delay 200 super+ctrl+k");
    }
    else if( val==KEY_C ) //center
    {
        system("xdotool mousemove 960 540");
    }
#endif

}

void ReMeta::castSystemCmd(int val, CCommand *cmd)
{
    if( val==KEY_A )
    {
        system("xdotool set_desktop 0");
    }
    else if( val>=KEY_1 &&
             val<=KEY_9 )
    {
#ifdef WIN32
        int desktop_id = val-KEY_1;
        state->super->virt->setDesktop(desktop_id);
#endif
    }
    else if( val==KEY_T )
    {
        system("gnome-terminal");
    }
    else if( val==KEY_V )
    {
        system("~/.config/polybar/awesomewm/vpn_switch.sh");
    }
    else if( val==KEY_LEFT )
    {
        system("xdotool key --delay 200 Super+b");
    }
    else if( val==KEY_RIGHT )
    {
        system("xdotool key Menu");
    }
    else if( val==RE_META_CLOSE )
    {
        system("xdotool key Alt+F4");
    }
    else if( val==KEY_UP )
    {
        system("dbus-send --dest=com.benjamin.chess"
               " / com.benjamin.chess.show string:\"\"");
    }

    else
    {
        qDebug() << "Unknown System" << val;
    }
}

void ReMeta::castFoxCmd(int val, CCommand *cmd)
{
    state->last_cmd.type = RE_COMMAND_NULL;

    if( val==RE_APP_LINK )
    {
        cmd->mod_list.append(KEY_LEFTCTRL);
        cmd->mod_list.append(KEY_LEFTSHIFT);
        cmd->val1 = KEY_F;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
        cmd->state = RE_CSTATE_0;
    }
}

void ReMeta::castMusicCmd(int val, CCommand *cmd)
{
#ifdef WIN32
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type  = RE_COMMAND_MOD;
    cmd->state = RE_CSTATE_0;
#else
    //////SHOULD GET FIXED WITH THE NEW SYSTEM
    QString cmd_str = "./Scripts/music.sh ";
#endif

    if( val==KEY_ENTER )
    {
#ifdef WIN32
        cmd->val1 = VK_MEDIA_PLAY_PAUSE;
#else
        cmd_str += "play";
#endif
    }
    else if( val==KEY_LEFT )
    {
#ifdef WIN32
        cmd->val1 = VK_MEDIA_PREV_TRACK;
#else
        cmd_str += "prev";
#endif
    }
    else if( val==KEY_RIGHT )
    {
#ifdef WIN32
        cmd->val1 = VK_MEDIA_NEXT_TRACK;
#else
        cmd_str += "next";
#endif
    }
    else if( val==KEY_UP )
    {
#ifdef WIN32
        cmd->val1 = VK_VOLUME_UP;
#else
        cmd_str += "up";
#endif
    }
    else if( val==KEY_DOWN )
    {
#ifdef WIN32
        cmd->val1 = VK_VOLUME_DOWN;
#else
        cmd_str += "down";
#endif
    }
    else
    {
        qDebug() << "Unknown Music" << val;
        return;
    }

#ifdef __linux__
    cmd_str += " >/dev/null";
    system(cmd_str.toStdString().c_str());
#endif
}

void ReMeta::execScrollCmd(int meta, int val)
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

void ReMeta::castGoCmd(int val, CCommand *cmd)
{
    //////SHOULD GET FIXED WITH THE NEW SYSTEM
    qDebug() << "GO" << state->app.pname;

    if( state->app.pname==RE_PROC_EDITOR )
    {
        re_getGoXed(val);
    }
    else if( state->app.pname==RE_PROC_QT ||
             state->app.pname==RE_PROC_VSCODE )
    {
        re_getGoQt(val);
    }
    else if( state->app.pname==RE_PROC_GIT )
    {
        re_getGoGitKraken(val, cmd);
    }
    else if( state->app.pname==RE_PROC_FIREFOX ||
             state->app.pname==RE_PROC_GEKO )
    {
        re_castGoFirefox(val, cmd);
    }
    else if( state->app.pname==RE_PROC_EXPLORER )
    {
        re_getGoNautilus(val, cmd);
    }
}

void ReMeta::castPageCmd(int val, CCommand *cmd)
{
    qDebug() << "Page" << state->app.pname;

    if( state->app.pname==RE_PROC_EDITOR )
    {
//        system(re_getGoXed(val);
    }
    else if( state->app.pname==RE_PROC_QT ||
             state->app.pname==RE_PROC_VSCODE )
    {
        if( val==KEY_DOWN ||
            val==KEY_UP )
        {
            cmd->val1  = KEY_DOWN;
            cmd->val2  = 30; //press count
            cmd->type  = RE_COMMAND_DIRS;
            cmd->state = RE_CSTATE_0;
        }
    }
    else
    {
        if( val==KEY_DOWN )
        {
            cmd->val1  = KEY_NEXT;
            cmd->val2  = 1; //press count
            cmd->type  = RE_COMMAND_DIRS;
            cmd->state = RE_CSTATE_0;
        }
        if( val==KEY_UP )
        {
            cmd->val1  = KEY_PAGEUP;
            cmd->val2  = 1; //press count
            cmd->type  = RE_COMMAND_DIRS;
            cmd->state = RE_CSTATE_0;
        }
    }
}

void ReMeta::castTouchCmd(int val, CCommand *cmd)
{
    qDebug() << "Touch" << state->app.pname
             << val;

    if( val==KEY_DOWN )
    {
        re_mouseMoveR(0, 100);
    }
    else if( val==KEY_UP )
    {
        re_mouseMoveR(0, -100);
    }
    else if( val==KEY_RIGHT )
    {
        re_mouseMoveR(100, 0);
    }
    else if( val==KEY_LEFT )
    {
        re_mouseMoveR(-100, 0);
    }
    else if( val==KEY_1 )
    {
        re_mouseMoveR(-27, -22);
    }
    else if( val==KEY_2 )
    {
        re_mouseMoveR(0, -22);
    }
    else if( val==KEY_3 )
    {
        re_mouseMoveR(27, -22);
    }
    else if( val==KEY_4 )
    {
        re_mouseMoveR(-27, 0);
    }
    else if( val==KEY_6 )
    {
        re_mouseMoveR(22, 0);
    }
    else if( val==KEY_7 )
    {
        re_mouseMoveR(-27, 22);
    }
    else if( val==KEY_8 )
    {
        re_mouseMoveR(0, 22);
    }
    else if( val==KEY_9 )
    {
        re_mouseMoveR(27, 22);
    }
}
