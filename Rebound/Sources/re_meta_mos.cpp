#include "re_meta_mos.h"
#ifdef WIN32
#include "re_keyboard_w.h"
#else
#include "re_keyboard_l.h"
#endif

ReMetaMos::ReMetaMos()
{
}

void ReMetaMos::castMonitor(int val)
{
    int x = 0;
    int y = 0;

    if( val==KEY_P ) //Primary
    {
        x  = ChMonitor::primary.x;
        x += ChMonitor::primary.width/2;
        y  = ChMonitor::primary.y;
        y += ChMonitor::primary.height/2;
    }
    else if( val==KEY_S ) //Secondary
    {
        x  = ChMonitor::secondary.x;
        x += ChMonitor::secondary.width/2;
        y  = ChMonitor::secondary.y;
        y += ChMonitor::secondary.height/2;
    }
    else if( val==KEY_L ) //Primary Left Side
    {
        x  = ChMonitor::primary.x;
        x += ChMonitor::primary.width/4;
        y  = ChMonitor::primary.y;
        y += ChMonitor::primary.height/2;
    }
    else if( val==KEY_R ) //Primary Left Side
    {
        x  = ChMonitor::primary.x;
        x += ChMonitor::primary.width*3/4;
        y  = ChMonitor::primary.y;
        y += ChMonitor::primary.height/2;
    }
#ifdef WIN32
    SetCursorPos(x, y);
#else
#endif
}

void ReMetaMos::castScroll(int val)
{
    int key = 0;
    int count = 4;

    if( val==KEY_U ) //Up
    {
        key = 4;
    }
    else if( val==KEY_D ) //Down
    {
        key = 5;
    }
    else if( val==KEY_H ) //High
    {
        key = 4;
        count = 6;
    }
    else if( val==KEY_G ) //Ground
    {
        key = 5;
        count = 6;
    }

#ifdef WIN32
    for( int i=0 ; i<count ; i++ )
    {
        QThread::msleep(10);
        re_mouseKey(key);
    }
#else
#endif
}

// Or VsCode
void ReMetaMos::castCode(int val, CCommand *cmd)
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

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
}

