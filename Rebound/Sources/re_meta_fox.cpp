#include "re_meta_fox.h"
#ifdef WIN32
#include "re_keyboard_w.h"
#else
#include "re_keyboard_l.h"
#endif
#include "re_mouse.h"

ReMetaFox::ReMetaFox()
{
}

QString ReMetaFox::castXed(int val)
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

// Or VsCode
void ReMetaFox::castCode(int val, CCommand *cmd)
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
//    else if( val==KEY_M )
//    {
//        cmd = "xdotool click 2";
//    }
//    else if( val==KEY_RIGHT )
//    {
//        cmd = "xdotool click 3";
//    }
//    else if( val==KEY_F ) //focus
//    {
//        system("xdotool key --delay 200 super+ctrl+k");
//        QThread::msleep(100); //little tweak
//        cmd = "xdotool key --delay 200 super+ctrl+k";
//    }
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

void ReMetaFox::castQt(int val, CCommand *cmd)
{
    if( val==KEY_LEFT || val==KEY_RIGHT )
    {
        cmd->is_alt   = 1;
        cmd->is_shift = 1;
        cmd->val1 = KEY_RIGHT;

        cmd->val2  = 1;
        cmd->val3  = 1;
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

void ReMetaFox::csatGitKraken(int val, CCommand *cmd)
{
    if( val==KEY_B )
    {
        system("xdotool type 'BaTool: '");
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
        system("xdotool type 'NATO: '"); ///FIXME windows
    }
    else if( val==KEY_R )
    {
        system("xdotool type 'Rebound-Linux: '");
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

void ReMetaFox::castFirefox(int val, CCommand *cmd)
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
}

void ReMetaFox::castNautilus(int val, CCommand *cmd)
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

void ReMetaFox::castAltium(int val, CCommand *cmd)
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

void ReMetaFox::castSlack(int val, CCommand *cmd)
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
