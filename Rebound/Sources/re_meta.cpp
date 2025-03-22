#include "re_meta.h"
#include "re_chess.h"
#ifdef WIN32
#include "re_keyboard_w.h"
#include "re_virtual_w.h"
#include "mm_api.h"
#else
#include "re_keyboard_l.h"
#endif

HWND focus_hwnd;
HWND open_hwnd;
BOOL CALLBACK EnumOpen(HWND hwnd, LPARAM lParam)
{
    MmApplication *app = (MmApplication *)lParam; // requested pname
    QString win_title = mm_getWinTitle(hwnd);

    // skip hidden window
    if( IsWindowVisible(hwnd)==0 )
    {
        return TRUE;
    }

    // skip windows bs windows
    if( win_title.isEmpty() )
    {
        return TRUE;
    }

    // skip windows not on current desktop
    if( ReVirtualW::isCurrentDesktop(hwnd)==0 &&
        app->workspace==0 )
    {
        return TRUE;
    }

    // skip active window
    if( hwnd==focus_hwnd )
    {
        return TRUE;
    }

    long pid = mm_getPid(hwnd);
    QString pname = mm_getPName(pid);
    pname = QFileInfo(pname).completeBaseName();
    qDebug() << pname << app->exe_name;
    if( pname==app->exe_name )
    {
        open_hwnd = hwnd;
        return FALSE;
    }

    return TRUE;
}

ReMeta::ReMeta()
{
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
        castOpenCmd(arg, &cmd);
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
    else if( meta==RE_META_POWER )
    {
        castPowerCmd(arg, &cmd);
    }
    else if( meta==RE_META_MUSIC )
    {
        castMusicCmd(arg, &cmd);
    }
    else if( meta==RE_META_MOUSE )
    {
        castMouseCmd(arg, &cmd);
    }

    return cmd;
}

void ReMeta::castOpenCmd(int val, CCommand *cmd)
{
    MmApplication app;
    if( val==KEY_E )
    {
        app.exe_name = "explorer";
    }
    if( val==KEY_F )
    {
        app.exe_name = "firefox";
    }
    else if( val==KEY_Q )
    {
        app.exe_name = "qtcreator";
    }
    execOpen(&app);
}

void ReMeta::execOpen(MmApplication *app)
{
    if( app->exe_name.isEmpty() )
    {
        return;
    }

    app->workspace = 0;
    focus_hwnd = GetForegroundWindow();
    open_hwnd  = 0;
    EnumWindows(EnumOpen, (LPARAM) app);

    if( open_hwnd==0 )
    {
        // search without workspace criteria
        app->workspace = -1;
        EnumWindows(EnumOpen, (LPARAM) app);
    }

    mm_focus(open_hwnd);
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
        ReMetaMos::castMonitor(val);
    }
    else if( val==KEY_U ||
             val==KEY_D ||
             val==KEY_G ||
             val==KEY_H )
    {
        ReMetaMos::castScroll(val);
    }
    else if( val==KEY_1 )
    {
        ReMetaMos::castMonitor(val);
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
    else if( val==KEY_D )
    {
        if( ReState::dim_opacity==RE_DIM_OPAC )
        {
            ReState::dim_opacity = 255;
        }
        else
        {
            ReState::dim_opacity = RE_DIM_OPAC;
        }
    }
    else if( val==KEY_K )
    {
        // Windows Calculator
        system("calc");
    }
    else if( val==KEY_H )
    {
        ReChess::sendCmd("toggle");
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
        ReChess::sendCmd("screenshot");
        ReState::ch_count = 4;
    }
    else if( val==KEY_V )
    {
        system("~/.config/polybar/awesomewm/vpn_switch.sh");
    }
    else if( val==KEY_LEFT )
    {
#ifdef WIN32
        cmd->is_super = 1;
        cmd->is_shift = 1;
        cmd->val1 = val;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
#else
        system("xdotool key --delay 200 Super+b");
#endif
    }
    else if( val==KEY_RIGHT )
    {
#ifdef WIN32
        cmd->is_super = 1;
        cmd->is_shift = 1;
        cmd->val1 = val;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
#else
        system("xdotool key Menu");
#endif
    }
    else if( val==KEY_DOWN )
    {
        ReState::goToSleep();
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
    else if( val==KEY_Z )
    {
        re_execSpeech();
    }
    else if( val==RE_SUPER_KICK )
    {
       ReChess::sendCmd("system", "show");
       ReChess::setCount(2);
    }
    else if( val==RE_SUPER_SIDE )
    {
       ReChess::sendCmd("system", "side");
       ReChess::setCount(2);
    }
    else if( val==RE_SUPER_COMMENT )
    {
       ReChess::sendCmd("system", "comment");
       ReChess::setCount(2);
    }
    else if( val==RE_SUPER_DOUBLE )
    {
       ReChess::sendCmd("system", "double");
       ReChess::setCount(2);
    }
    else if( val==RE_SUPER_DRAG )
    {
           ReChess::sendCmd("system", "drag");
        ReState::ch_count = 4;
    }
    else if( val==RE_SUPER_TOUCH )
    {
        ReChess::sendCmd("system", "touch");
        ReState::ch_count = 999;
    }
    else if( val==RE_SUPER_SELECT )
    {
        ReChess::sendCmd("select");
        ReChess::setCount(2);
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
        ReMetaFox::castXed(val);
    }
    else if( ReState::app.pname==RE_PROC_VSCODE ||
             ReState::app.pname==RE_PROC_VIVADO )
    {
        ReMetaFox::castCode(val, cmd);
    }
    else if( ReState::app.pname==RE_PROC_QT )
    {
        ReMetaFox::castQt(val, cmd);
    }
    else if( ReState::app.pname==RE_PROC_GIT )
    {
        ReMetaFox::csatGitKraken(val, cmd);
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX ||
             ReState::app.pname==RE_PROC_GEKO    ||
             ReState::app.pname==RE_PROC_CHROME  ||
             ReState::app.pname==RE_PROC_VIVALDI )
    {
        ReMetaFox::castFirefox(val, cmd);

        if( val==KEY_L )
        {
            ReState::last_cmd.type = RE_COMMAND_NULL;
        }
    }
    else if( ReState::app.pname==RE_PROC_EXPLORER )
    {
        ReMetaFox::castNautilus(val, cmd);
    }
#ifdef WIN32
    else if( ReState::app.pname==RE_PROC_ALTIUM )
    {
        ReMetaFox::castAltium(val, cmd);
    }
    else if( ReState::app.pname==RE_PROC_SLACK )
    {
        ReMetaFox::castSlack(val, cmd);
    }
    else
    {
        ReMetaFox::castFirefox(val, cmd);
    }
#endif
}

void ReMeta::castPowerCmd(int val, CCommand *cmd)
{
    //////SHOULD GET FIXED WITH THE NEW SYSTEM
    qDebug() << "Power" << ReState::app.pname;

    if( ReState::app.pname==RE_PROC_EDITOR )
    {
        ReMetaPower::castXed(val);
    }
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        ReMetaPower::castCode(val, cmd);
    }
    else if( ReState::app.pname==RE_PROC_QT )
    {
        ReMetaPower::castQt(val, cmd);
    }
    else if( ReState::app.pname==RE_PROC_GIT )
    {
        ReMetaPower::csatGitKraken(val, cmd);
    }
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
