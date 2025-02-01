#include "re_meta_power.h"
#ifdef WIN32
#include "re_keyboard_w.h"
#else
#include "re_keyboard_l.h"
#endif
#include "re_mouse.h"

ReMetaPower::ReMetaPower()
{
}

QString ReMetaPower::castXed(int val)
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

// VsCode
void ReMetaPower::castCode(int val, CCommand *cmd)
{
    if( val==KEY_LEFT )
    {
        cmd->is_ctrl  = 1;
        cmd->is_shift = 1;
        cmd->val1 = KEY_TAB;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_RIGHT )
    {
        cmd->is_ctrl = 1;
        cmd->val1 = KEY_TAB;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
    if( val==KEY_A )
    {
        cmd->is_ctrl  = 1;
        cmd->val1 = KEY_1;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_B )
    {
        cmd->is_ctrl = 1;
        cmd->val1 = KEY_2;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_DOWN || val==KEY_UP )
    {
        cmd->val1  = val;
        cmd->val2  = 30; //press count
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
    else if( val>=KEY_1 &&
             val<=KEY_9 ) //tab
    {
        cmd->is_alt = 1;
        cmd->val1 = val;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
}

void ReMetaPower::castQt(int val, CCommand *cmd)
{
    POINT mos_pos;
    GetCursorPos(&mos_pos);
    ReKeyboard::pressKey(KEY_LEFTCTRL);
    ReKeyboard::sendKey(KEY_T);
    ReKeyboard::releaseKey(KEY_LEFTCTRL);

//    QThread::msleep(100); //little tweak
//    ReKeyboard::sendKey(KEY_LEFT);
//    QThread::msleep(100); //little tweak
//    ReKeyboard::sendKey(KEY_LEFT);
    QThread::msleep(100); //little tweak
    re_mouseMoveW_bl(100, 200);
    ReKeyboard::sendKey(val);
    QThread::msleep(100); //little tweak
    cmd->val1 = KEY_ESC;

    cmd->val2  = 1;
    cmd->val3  = 1;
    cmd->type  = RE_COMMAND_DIRS;
    cmd->state = RE_CSTATE_0;

    SetCursorPos(mos_pos.x, mos_pos.y);
}

void ReMetaPower::csatGitKraken(int val, CCommand *cmd)
{
    if( val==KEY_B )
    {
        ReKeyboard::type("BaTool: ");
    }
    if( val==KEY_C )
    {
        ReKeyboard::type("Chess: ");
    }
    else if( val==KEY_M )
    {
        cmd->is_ctrl = 1;
        cmd->val1 = KEY_M;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_N )
    {
        ReKeyboard::type("NATO: "); ///FIXME windows
    }
    else if( val==KEY_R )
    {
#ifdef WIN32
        ReKeyboard::type("Rebound-Windows: ");
#else
        ReKeyboard::type("Rebound-Linux: ");
#endif
    }
    else if( val==KEY_LEFT ) //tab
    {
        cmd->is_ctrl  = 1;
        cmd->is_shift = 1;
        cmd->val1 = KEY_TAB;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_RIGHT )
    {
        cmd->is_ctrl  = 1;
        cmd->val1 = KEY_TAB;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
    else if( val>=KEY_1 &&
             val<=KEY_9 ) //tab
    {
        cmd->is_ctrl  = 1;
        cmd->val1 = val;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_P ) //push
    {
        system("xdotool key ctrl+Enter");
        QThread::msleep(100); //little tweak
        system("xdotool key ctrl+p");
        QThread::msleep(100); //little tweak
        system("xdotool type push");
        QThread::msleep(100); //little tweak
        system("xdotool key Enter");
    }
}

void ReMetaPower::castFirefox(int val, CCommand *cmd)
{
    if( val==KEY_LEFT ) //tab
    {
        cmd->is_ctrl  = 1;
        cmd->is_shift = 1;
        cmd->val1 = KEY_TAB;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_RIGHT )
    {
        cmd->is_ctrl  = 1;
        cmd->val1 = KEY_TAB;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_DOWN )
    {
        cmd->val1  = KEY_NEXT;
        cmd->val2  = 1; //press count
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_UP )
    {
        cmd->val1  = KEY_PAGEUP;
        cmd->val2  = 1; //press count
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_F ) //find
    {
        cmd->is_ctrl  = 1;
        cmd->is_shift = 1;
        cmd->val1 = KEY_F;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( val>=KEY_1 &&
             val<=KEY_9 ) //tab
    {
#ifdef WIN32
        cmd->is_ctrl  = 1;
#else
        cmd->is_alt = 1;
#endif
        cmd->val1 = val;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_L )
    {
        cmd->is_ctrl  = 1;
        cmd->is_shift = 1;
        cmd->val1 = KEY_F;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_O )
    {
        ReState::goToSleep();
//        ReKeyboard::sendKey(VK_SCROLL);
        re_mouseMoveW_br(1180, 60);
        QThread::msleep(50);
        re_mouseKey(1);
        QThread::msleep(50);
        re_mouseMoveW_br(1100, 60);
        QThread::msleep(50);
        re_mouseKey(1);
    }
}

void ReMetaPower::castNautilus(int val, CCommand *cmd)
{
    if( val==KEY_BACKSPACE )
    {
        cmd->is_alt = 1;
        cmd->val1 = KEY_UP;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
    else if( val>=KEY_1 &&
             val<=KEY_9 ) //tab
    {
        cmd->is_alt = 1;
        cmd->val1 = val;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_DIGIT;
        cmd->state = RE_CSTATE_0;
    }
}

void ReMetaPower::castAltium(int val, CCommand *cmd)
{
    if( val==KEY_LEFT ) //next layer
    {
        cmd->val1 = KEY_MINUS;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_RIGHT )
    {
        cmd->val1 = KEY_KPPLUS;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_F ) //find
    {
        cmd->is_ctrl  = 1;
        cmd->is_shift = 1;
        cmd->val1 = KEY_F;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_I ) //injection
    {
        int pid = ReState::app.pid;
        qDebug() << ">>>>>>>>>>>>>>>INJA" << pid;
#ifdef WIN32
        ReInject::inject(pid);
#endif
    }
    else if( val>=KEY_1 &&
             val<=KEY_9 ) //tab
    {
#ifdef WIN32
        cmd->is_ctrl  = 1;
#else
        cmd->is_alt = 1;
#endif
        cmd->val1 = val;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_L )
    {
        cmd->is_ctrl  = 1;
        cmd->is_shift = 1;
        cmd->val1 = KEY_F;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
}

void ReMetaPower::castSlack(int val, CCommand *cmd)
{
    if( val==KEY_HOME ) //next layer
    {
        re_mouseMoveW(200, 400);

        cmd->is_ctrl = 1;
        cmd->val1    = RE_MOUSE_UP;

        cmd->val2 = 20;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOUSE;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_END )
    {
        re_mouseMoveW(200, 400);

        cmd->is_ctrl = 1;
        cmd->val1    = RE_MOUSE_DOWN;

        cmd->val2 = 20;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOUSE;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_M ) //message
    {

    }
    else if( val>=KEY_1 &&
             val<=KEY_9 ) //tab
    {
#ifdef WIN32
        cmd->is_ctrl  = 1;
#else
        cmd->is_alt = 1;
#endif
        cmd->val1 = val;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_L )
    {
        cmd->is_ctrl  = 1;
        cmd->is_shift = 1;
        cmd->val1 = KEY_F;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_U ) //unread
    {
        re_mouseMoveW(300, 400);
        int count = 10;
        for( int j=0 ; j<count ; j++ )
        {
            re_mouseKey(4);
            QThread::msleep(50);
        }

        re_mouseMoveW(300, 150);
        QThread::msleep(50);
        re_mouseKey(1);

        re_mouseMoveC(0, 0);
        QThread::msleep(50);
        re_mouseKey(1);
    }
    else if( val==KEY_T ) //thread
    {
        re_mouseMoveW(300, 400);
        int count = 10;
        for( int j=0 ; j<count ; j++ )
        {
            re_mouseKey(4);
            QThread::msleep(50);
        }

        re_mouseMoveW(300, 180);
        QThread::msleep(50);
        re_mouseKey(1);

        re_mouseMoveC(0, 0);
        QThread::msleep(50);
        re_mouseKey(1);
    }
}
