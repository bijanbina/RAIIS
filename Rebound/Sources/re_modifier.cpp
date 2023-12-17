#include "re_modifier.h"
#include <QThread>

CCommand re_modCreate(QString text)
{
    CCommand cmd;
    cmd.val1  = 0;
    cmd.val2  = 1;
    cmd.type  = RE_COMMAND_NATO;
    cmd.state = RE_CSTATE_0;

    int val = text.toInt();
    re_modApplyVal(&cmd, val);

    return cmd;
}

void re_modApplyVal(CCommand *cmd, int val)
{
    if( val==KEY_LEFTSHIFT )
    {
        cmd->is_shift = 1;
    }
    else if( val==KEY_LEFTALT )
    {
        cmd->is_alt = 1;
    }
    else if( val==KEY_LEFTCTRL )
    {
        cmd->is_ctrl = 1;
    }
    else if( val==KEY_LEFTMETA )
    {
        cmd->is_super = 1;
    }
}

void re_modPress(CCommand cmd)
{
    if( cmd.type==RE_COMMAND_NULL )
    {
        return;
    }

    if( cmd.is_super )
    {
        ReKeyboard::pressKey(KEY_LEFTMETA);
    }

    if( cmd.is_alt )
    {
        ReKeyboard::pressKey(KEY_LEFTALT);
    }

    if( cmd.is_shift )
    {
        ReKeyboard::pressKey(KEY_LEFTSHIFT);
    }

    if( cmd.is_ctrl )
    {
        ReKeyboard::pressKey(KEY_LEFTCTRL);
    }
}

void re_modRelease(CCommand cmd)
{
    if( cmd.type==RE_COMMAND_NULL )
    {
        return;
    }

    re_modWait(cmd);
    if( cmd.is_alt )
    {
        ReKeyboard::releaseKey(KEY_LEFTALT);
    }

    if( cmd.is_shift )
    {
        ReKeyboard::releaseKey(KEY_LEFTSHIFT);
    }

    if( cmd.is_ctrl )
    {
        ReKeyboard::releaseKey(KEY_LEFTCTRL);
    }

    if( cmd.is_super )
    {
        ReKeyboard::releaseKey(KEY_LEFTMETA);
    }
}

void re_modWait (CCommand cmd, int val)
{
    if( cmd.is_alt  || cmd.is_shift ||
        cmd.is_ctrl || cmd.is_super )
    {
        QThread::msleep(val); //little tweak
    }
}
