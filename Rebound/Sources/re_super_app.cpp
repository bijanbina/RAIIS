#include "re_super.h"
#include <QThread>

void ReSuper::castFrontCmd(CCommand *cmd)
{
    re_mouseMoveC(0, 0);

    cmd->is_ctrl = 1;
    cmd->val1    = RE_MOUSE_UP;

    cmd->val2 = 5;
    cmd->val3 = 1;
    cmd->type  = RE_COMMAND_MOUSE;
    cmd->state = RE_CSTATE_0;
}

void ReSuper::castLastCmd(CCommand *cmd)
{
    re_mouseMoveC(0, 0);

    cmd->is_ctrl = 1;
    cmd->val1    = RE_MOUSE_DOWN;

    cmd->val2 = 5;
    cmd->val3 = 1;
    cmd->type  = RE_COMMAND_MOUSE;
    cmd->state = RE_CSTATE_0;
}

void ReSuper::castRunCmd(CCommand *cmd)
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

void ReSuper::castDukeCmd(CCommand *cmd)
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
