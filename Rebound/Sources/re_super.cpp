#include "re_super.h"
#include <QThread>

ReKeyboard ReSuper::key;

ReSuper::ReSuper()
{
}

void ReSuper::cast(int val, CCommand *cmd)
{
    if( val==RE_SUPER_META )
    {
        castMetaCmd(cmd);
    }
    else if( val==RE_SUPER_CAMEL )
    {
        castCamelCmd(cmd);
    }
    else if( val==RE_SUPER_SWITCH )
    {
        castSwitchCmd(cmd);
    }
    else if( val==RE_SUPER_SPOTIFY )
    {
        castLSwitchCmd(cmd);
    }
    else if( val==RE_SUPER_COPY )
    {
        castCopyCmd(cmd);
    }
    else if( val==RE_SUPER_PASTE )
    {
        castPasteCmd(cmd);
    }
    else if( val==RE_SUPER_SELECT )
    {
        castSelectCmd(cmd);
    }
    else if( val==RE_SUPER_LOVE )
    {
        castLoveCmd(cmd);
    }
    else if( val==RE_SUPER_ROGER )
    {
        castRogerCmd(cmd);
    }
    else if( val==RE_SUPER_GAS )
    {
        castRogerCmd(cmd);
    }
    else if( val==RE_SUPER_CARROT )
    {
        castRogerCmd(cmd);
    }
    else if( val==RE_SUPER_DUKE )
    {
        castRogerCmd(cmd);
    }
    else if( val==RE_SUPER_MEDIA )
    {
        castRogerCmd(cmd);
    }
    else if( val==RE_SUPER_FRONT )
    {
        castFrontCmd(cmd);
    }
    else if( val==RE_SUPER_LAST )
    {
        castLastCmd(cmd);
    }
    else if( val==RE_SUPER_POWER )
    {
        castRogerCmd(cmd);
    }
    else if( val==RE_SUPER_RUN )
    {
        castRogerCmd(cmd);
    }
}

void ReSuper::castMetaCmd(CCommand *cmd)
{
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type = RE_COMMAND_NULL;

    qDebug() << "Meta" << ReState::app.pname;

    if( ReState::app.pname==RE_PROC_QT )
    {
        cmd->val1 = KEY_F1;
        cmd->type = RE_COMMAND_DIRS;
    }
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        cmd->val1 = KEY_F5;
        cmd->type = RE_COMMAND_DIRS;
    }
    else if( ReState::app.pname==RE_PROC_GIT )
    {
        re_mouseKey(3);
//        cmd->val1 = KEY_UP;

//        cmd->val2 = 5;
//        cmd->val3 = 1;
//        cmd->type  = RE_COMMAND_DIRS;
//        cmd->state = RE_CSTATE_0;
        qDebug() << "super";
//        cmd = re_getGoGitKraken(val);
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX ||
             ReState::app.pname==RE_PROC_GEKO    ||
             ReState::app.pname==RE_PROC_CHROME )
    {
        cmd->is_ctrl = 1;
        cmd->val1    = KEY_W;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_EXPLORER )
    {
        cmd->is_ctrl = 1;
        cmd->val1    = KEY_W;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_TELEGRAM )
    {
#ifdef WIN32
        recordTelegram();
#else
        system("./Scripts/telegram_voice.sh");
#endif
    }
#ifdef WIN32
    else if( ReState::app.pname==RE_PROC_SLACK )
    {
        SetCursorPos(50, 500);
    }
    else if( ReState::app.pname==RE_PROC_ALTIUM )
    {
        cmd->is_ctrl = 1;
        cmd->val1    = KEY_F4;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
#endif
}

void ReSuper::castCopyCmd(CCommand *cmd)
{
    cmd->is_ctrl = 1;
    cmd->val1    = KEY_C;

    cmd->val2  = 1;
    cmd->val3  = 1;
    cmd->type  = RE_COMMAND_NATO;
    cmd->state = RE_CSTATE_0;
}

void ReSuper::castPasteCmd(CCommand *cmd)
{
    cmd->is_ctrl = 1;
    cmd->val1    = KEY_V;

    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type  = RE_COMMAND_NATO;
    cmd->state = RE_CSTATE_0;
}

// Language switch
void ReSuper::castLSwitchCmd(CCommand *cmd)
{
#ifdef WIN32
    // Switch to next language Need an hwnd
    // to work for console applications
    HWND handle = GetForegroundWindow();
    PostMessage(handle, WM_INPUTLANGCHANGEREQUEST,
                0, (LPARAM)HKL_NEXT);
    makeNull(cmd);
#else
    ///FIXME
#endif
}

void ReSuper::castCamelCmd(CCommand *cmd)
{
    qDebug() << "CreateProcess 1";
#ifdef WIN32
#else
    system("./Scripts/camel");
#endif
    makeNull(cmd);
}

void ReSuper::castSelectCmd(CCommand *cmd)
{
    if( ReState::app.pname==RE_PROC_FIREFOX )
    {
        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->val1 = KEY_F7;
        cmd->type = RE_COMMAND_DIRS;
    }
#ifdef WIN32
    else if( ReState::app.pname==RE_PROC_ALTIUM )
    {
        if( ReState::drag_state )
        {
            re_mouseRelease(1);
            ReState::drag_state = 0;
            re_rmStatus();
        }
        else
        {
            re_mousePress(1);
            ReState::goToDrag();
        }
        makeNull(cmd);
    }
#endif
    else
    {
        key.sendKey(KEY_END);
        cmd->is_shift = 1;
        cmd->val1     = KEY_HOME;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
}

void ReSuper::castLoveCmd(CCommand *cmd)
{
    cmd->is_ctrl = 1;
    cmd->val1    = KEY_LEFT;

    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type  = RE_COMMAND_DIRS;
    cmd->state = RE_CSTATE_0;
}

void ReSuper::castRogerCmd(CCommand *cmd)
{
    cmd->is_ctrl = 1;
    cmd->val1    = KEY_RIGHT;

    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type  = RE_COMMAND_DIRS;
    cmd->state = RE_CSTATE_0;
}

void ReSuper::castSwitchCmd(CCommand *cmd)
{
#ifdef WIN32
    cmd->is_alt = 1;
    cmd->val1   = KEY_TAB;
#else
    cmd->is_super = 1;
    cmd->val1 = KEY_B;
#endif

    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type  = RE_COMMAND_DIRS;
    cmd->state = RE_CSTATE_0;
}

void ReSuper::makeNull(CCommand *cmd)
{
    cmd->is_alt   = 0;
    cmd->is_ctrl  = 0;
    cmd->is_shift = 0;
    cmd->is_super = 0;
    cmd->val1 = 0;

    cmd->val2 = 0;
    cmd->val3 = 1;
    cmd->type  = RE_COMMAND_NULL;
    cmd->state = RE_CSTATE_0;
}

#ifdef WIN32
void ReSuper::recordTelegram()
{
    qDebug() << "recordTelegram";
    ReState::goToRecord();
    re_mouseMoveW_br(30, 30);
    QThread::msleep(100);
    re_mousePress(1);
    QThread::msleep(1000);
    re_mouseMoveW_br(30, 400);
    QThread::msleep(1000);
    re_mouseRelease(1);
}
#endif
