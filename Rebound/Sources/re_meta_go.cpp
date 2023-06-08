#include "re_meta_go.h"
#ifdef WIN32
#include "re_keyboard_w.h"
#else
#include "re_keyboard_l.h"
#endif

QString re_getGoXed(int val)
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
void re_getGoCode(int val, CCommand *cmd)
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

void re_getGoGitKraken(int val, CCommand *cmd)
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

void re_castGoFirefox(int val, CCommand *cmd)
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

void re_getGoNautilus(int val, CCommand *cmd)
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
