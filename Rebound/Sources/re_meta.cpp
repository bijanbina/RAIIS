#include "re_meta.h"
#ifdef WIN32
#include "re_keyboard_w.h"
#include "mm_api.h"
#else
#include "re_keyboard_l.h"
#endif

ReMeta::ReMeta()
{
    fox   = new ReMetaFox;
    mouse = new ReMetaMos;
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
        ReState::last_cmd.type = RE_COMMAND_NULL;
    }
    else if( meta==RE_META_SKY ||
             meta==RE_META_DIVE )
    {
        if( ReState::app.pname!=RE_PROC_FIREFOX )
        {
            return cmd;
        }
        if( (KEY_1<=arg && arg<=KEY_9) )
        {
            execScrollCmd(meta, arg-KEY_1+1);
        }
        else if( KEY_A<=arg && arg<=KEY_F )
        {
            execScrollCmd(meta, arg-KEY_A+10);
        }
        else
        {
            return cmd;
        }
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
    else if( val==KEY_UP )
    {
        re_mouseKey(4);
    }
    else if( val==KEY_DOWN )
    {
        re_mouseKey(5);
    }
    else if( val==KEY_P ||
             val==KEY_S ||
             val==KEY_L ||
             val==KEY_R )
    {
        mouse->castMonitor(val);
    }
    else if( val==KEY_U ||
             val==KEY_D ||
             val==KEY_G ||
             val==KEY_H )
    {
        mouse->castScroll(val);
    }
    else if( val==KEY_1 )
    {
        mouse->castMonitor(val);
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
    if( val>=KEY_1 &&
             val<=KEY_9 )
    {
#ifdef WIN32
        QString cmd_str = "Sys_";
        cmd_str += QString::number(val-KEY_0);
        cmd_str += CH_NP_SEPARATOR;
        RePipe::sendMom(cmd_str.toStdString().c_str());
#endif
    }
    else if( val==KEY_A )
    {
        system("xdotool set_desktop 0");
    }
    else if( val==KEY_K )
    {
        // Multimedia CPanel Recording Tab
        system("calc");
    }
    else if( val==KEY_M )
    {
        // Multimedia CPanel Recording Tab
        system("mmsys.cpl,1");
    }
    else if( val==KEY_T )
    {
        system("gnome-terminal");
    }
    else if( val==KEY_S )
    {
        sendChessCmd("screenshot");
        ReState::ch_count = 4;
    }
    else if( val==KEY_R )
    {
        ReState::goToRemote();
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
    else if( val==KEY_END )
    {
        re_getSysEnd();
    }
    else if( val==RE_SUPER_KICK )
    {
        sendChessCmd("system", "show");
        ReState::ch_count = 2;
    }
    else if( val==RE_SUPER_SIDE )
    {
        sendChessCmd("system", "side");
        ReState::ch_count = 2;
    }
    else if( val==RE_SUPER_COMMENT )
    {
        sendChessCmd("system", "comment");
        ReState::ch_count = 2;
    }
    else if( val==RE_SUPER_DOUBLE )
    {
        sendChessCmd("system", "double");
        ReState::ch_count = 2;
    }
    else if( val==RE_SUPER_DRAG )
    {
        sendChessCmd("system", "drag");
        ReState::ch_count = 4;
    }
    else
    {
        qDebug() << "Unknown System" << val;
    }
}

void ReMeta::castFoxCmd(int val, CCommand *cmd)
{
    //////SHOULD GET FIXED WITH THE NEW SYSTEM
    qDebug() << "FOX" << ReState::app.pname;

    if( ReState::app.pname==RE_PROC_EDITOR )
    {
        fox->castXed(val);
    }
    else if( ReState::app.pname==RE_PROC_QT ||
             ReState::app.pname==RE_PROC_VSCODE )
    {
        fox->castCode(val, cmd);
    }
    else if( ReState::app.pname==RE_PROC_GIT )
    {
        fox->csatGitKraken(val, cmd);
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX ||
             ReState::app.pname==RE_PROC_GEKO    ||
             ReState::app.pname==RE_PROC_CHROME )
    {
        fox->castFirefox(val, cmd);

        if( val==KEY_L )
        {
            ReState::last_cmd.type = RE_COMMAND_NULL;
        }
    }
    else if( ReState::app.pname==RE_PROC_EXPLORER )
    {
        fox->castNautilus(val, cmd);
    }
#ifdef WIN32
    else if( ReState::app.pname==RE_PROC_ALTIUM )
    {
        fox->castAltium(val, cmd);
    }
#endif
}

void ReMeta::castMusicCmd(int val, CCommand *cmd)
{
#ifdef WIN32
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type  = RE_COMMAND_DIRS;
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

    ReState::enScroll(meta, val);
}

void ReMeta::castPageCmd(int val, CCommand *cmd)
{
    qDebug() << "Page" << ReState::app.pname;

    if( ReState::app.pname==RE_PROC_EDITOR )
    {
//        system(re_getGoXed(val);
    }
    else if( ReState::app.pname==RE_PROC_QT ||
             ReState::app.pname==RE_PROC_VSCODE )
    {
        if( val==KEY_DOWN ||
            val==KEY_UP )
        {
            cmd->val1  = val;
            cmd->val2  = 30; //press count
            cmd->type  = RE_COMMAND_DIRS;
            cmd->state = RE_CSTATE_0;
        }
        if( val==KEY_RIGHT ||
            val==KEY_LEFT )
        {
            cmd->is_alt   = 1;
            cmd->is_shift = 1;
            cmd->val1 = KEY_RIGHT;

            cmd->val2  = 1;
            cmd->val3  = 1;
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
    qDebug() << "Touch" << ReState::app.pname
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

void ReMeta::sendChessCmd(QString cmd, QString arg)
{
#ifdef WIN32
    QString pipe_data = cmd + CH_NP_SEPARATOR + arg;
    RePipe::sendChess(pipe_data.toStdString().c_str());
//    qDebug() << "pipe" << pipe_data;
#else
    QString pipe_data = "dbus-send --dest=com.benjamin.chess";
    pipe_data += "dbus-send --dest=com.benjamin.chess";
    pipe_data += " / com.benjamin.chess.show string:\"";
    pipe_data += cmd + "\"";
    system(pipe_data.toStdString().c_str());
#endif
}
