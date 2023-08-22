#include "re_meta_mos.h"
#ifdef WIN32
#include "re_keyboard_w.h"
#else
#include "re_keyboard_l.h"
#endif

ReMetaMos::ReMetaMos(ReState *st, QObject *parent):
    QObject(parent)
{
    state = st;
}

void ReMetaMos::castMonitor(int val)
{
    int x = 0;
    int y = 0;

    if( val==KEY_P ) //Primary
    {
        x  = state->mon->primary.x;
        x += state->mon->primary.width/2;
        y  = state->mon->primary.y;
        y += state->mon->primary.height/2;
    }
    else if( val==KEY_S ) //Secondary
    {
        x  = state->mon->secondary.x;
        x += state->mon->secondary.width/2;
        y  = state->mon->secondary.y;
        y += state->mon->secondary.height/2;
    }
    else if( val==KEY_L ) //Primary Left Side
    {
        x  = state->mon->primary.x;
        x += state->mon->primary.width/4;
        y  = state->mon->primary.y;
        y += state->mon->primary.height/2;
    }
    else if( val==KEY_R ) //Primary Left Side
    {
        x  = state->mon->primary.x;
        x += state->mon->primary.width*3/4;
        y  = state->mon->primary.y;
        y += state->mon->primary.height/2;
    }
#ifdef WIN32
    SetCursorPos(x, y);
#else
#endif
}

// Or VsCode
void ReMetaMos::castCode(int val, CCommand *cmd)
{
    if( val==KEY_LEFT )
    {
        cmd->mod_list.append(KEY_LEFTCTRL);
        cmd->mod_list.append(KEY_LEFTSHIFT);
        cmd->val1 = KEY_TAB;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_RIGHT )
    {
        cmd->mod_list.append(KEY_LEFTCTRL);
        cmd->val1 = KEY_TAB;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
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
        cmd->mod_list.append(KEY_LEFTALT);
        cmd->val1 = val;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
        cmd->state = RE_CSTATE_0;
    }
}

void ReMetaMos::csatGitKraken(int val, CCommand *cmd)
{
    if( val==KEY_B )
    {
        system("xdotool type 'BaTool: '");
    }
    else if( val==KEY_M )
    {
        cmd->mod_list.append(KEY_LEFTCTRL);
        cmd->val1 = KEY_M;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
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
        cmd->mod_list.append(KEY_LEFTCTRL);
        cmd->mod_list.append(KEY_LEFTSHIFT);
        cmd->val1 = KEY_TAB;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_RIGHT )
    {
        cmd->mod_list.append(KEY_LEFTCTRL);
        cmd->val1 = KEY_TAB;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
        cmd->state = RE_CSTATE_0;
    }
    else if( val>=KEY_1 &&
             val<=KEY_9 ) //tab
    {
        cmd->mod_list.append(KEY_LEFTCTRL);
        cmd->val1 = val;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
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

void ReMetaMos::castFirefox(int val, CCommand *cmd)
{
    if( val==KEY_LEFT ) //tab
    {
        cmd->mod_list.append(KEY_LEFTCTRL);
        cmd->mod_list.append(KEY_LEFTSHIFT);
        cmd->val1 = KEY_TAB;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_RIGHT )
    {
        cmd->mod_list.append(KEY_LEFTCTRL);
        cmd->val1 = KEY_TAB;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_F ) //find
    {
        cmd->mod_list.append(KEY_LEFTCTRL);
        cmd->mod_list.append(KEY_LEFTSHIFT);
        cmd->val1 = KEY_F;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
        cmd->state = RE_CSTATE_0;
    }
    else if( val>=KEY_1 &&
             val<=KEY_9 ) //tab
    {
#ifdef WIN32
        cmd->mod_list.append(KEY_LEFTCTRL);
#else
        cmd->mod_list.append(KEY_LEFTALT);
#endif
        cmd->val1 = val;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_L )
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

void ReMetaMos::castNautilus(int val, CCommand *cmd)
{
    if( val==KEY_BACKSPACE )
    {
        cmd->mod_list.append(KEY_LEFTALT);
        cmd->val1 = KEY_UP;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
        cmd->state = RE_CSTATE_0;
    }
    else if( val>=KEY_1 &&
             val<=KEY_9 ) //tab
    {
        cmd->mod_list.append(KEY_LEFTALT);
        cmd->val1 = val;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
        cmd->state = RE_CSTATE_0;
    }
}

void ReMetaMos::castAltium(int val, CCommand *cmd)
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
        cmd->mod_list.append(KEY_LEFTCTRL);
        cmd->mod_list.append(KEY_LEFTSHIFT);
        cmd->val1 = KEY_F;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
        cmd->state = RE_CSTATE_0;
    }
    else if( val>=KEY_1 &&
             val<=KEY_9 ) //tab
    {
#ifdef WIN32
        cmd->mod_list.append(KEY_LEFTCTRL);
#else
        cmd->mod_list.append(KEY_LEFTALT);
#endif
        cmd->val1 = val;

        cmd->val2 = 1;
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOD;
        cmd->state = RE_CSTATE_0;
    }
    else if( val==KEY_L )
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
