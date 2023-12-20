#include "re_super.h"
#include <QThread>

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
