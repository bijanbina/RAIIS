#include "re_captain.h"
#include <unistd.h>
#include <fcntl.h>

ReCaptain::ReCaptain(ReState *st, QObject *parent): QObject(parent)
{
    state = st;
    meta  = new ReMeta (state);
    super = new ReSuper(state);
    state->last_cmd.type = RE_COMMAND_NULL;
}

ReCaptain::~ReCaptain()
{
    delete meta;
}

void ReCaptain::execKeyboard(CCommand command)
{
    re_modPress(command);

    for( int j=0 ; j<command.val2 ; j++ )
    {
        if( command.val1==RE_SUPER_LOVE )
        {
            CCommand cmd;
            cmd.is_ctrl = 1;
            cmd.val1 = KEY_LEFT;
            cmd.val2 = 1;

            execKeyboard(cmd);
        }
        else if( command.val1==RE_SUPER_ROGER )
        {
            CCommand cmd;
            cmd.is_ctrl = 1;
            cmd.val1 = KEY_RIGHT;
            cmd.val2 = 1;

            execKeyboard(cmd);
        }
        else
        {
            QThread::msleep(10); //little tweak
            ReKeyboard::sendKey(command.val1);
        }
    }

    re_modRelease(command);
//    qDebug() << "pressModifier" << modifiers.count();
}

void ReCaptain::execute(QVector<CCommand> commands)
{
    for( int i=0 ; i<commands.length() ; i++ )
    {
        if( state->isSleep() )
        {
            int ret = execSleep(commands[i]);
            if( ret )
            {
                commands.clear();
                return;
            }
        }
        else
        {
            execCommand(commands[i]);
        }
    }
}

int ReCaptain::execSleep(CCommand command)
{
    if( command.type==RE_COMMAND_NULL ||
        command.is_super==0 )
    {
        return 0;
    }
    else // is_super==1
    {
        if( isWakeUp(command) )
        {
            if( state->dictate_state )
            {
                wakeDictate();
            }
            else if( state->record_state )
            {
                wakeRecord();
            }
            else
            {
                state->wakeUp();
                execCommand(command);
                qDebug() << "Wake Up";
                return 1;
            }
        }
        else if( isSpeakerSw(command) )
        {
            execCommand(command);
            return 0;
        }
    }

    return 0;
}

void ReCaptain::execCommand(CCommand command)
{
    state->last_cmd = command;
    if( command.type==RE_COMMAND_NATO ||
        command.type==RE_COMMAND_DIRS ||
        command.type==RE_COMMAND_DIGIT )
    {
        if( state->isEscape(command) )
        {
            if( state->resetState() )
            {
                return;
            }
        }

        execKeyboard(command);
    }
    else if( command.type==RE_COMMAND_META )
    {
        execMeta(command);
    }
    else if( command.type==RE_COMMAND_SUPER )
    {
        for( int j=0 ; j<command.val2 ; j++ )
        {
            CCommand cmd; //dummy var
            super->castCmd(command.val1, &cmd);
        }
    }
    else if( command.type==RE_COMMAND_QDIGIT )
    {
        re_getQtCmd(command);
    }
}

bool ReCaptain::isLastRepeatable()
{
    int cmd_type = state->last_cmd.type;

    if( state->fl->sc_dir )
    {
        return false;
    }

    if( cmd_type!=RE_COMMAND_NULL )
    {
        if( state->last_cmd.is_alt  || state->last_cmd.is_shift ||
            state->last_cmd.is_ctrl || state->last_cmd.is_super )
        {
            if( state->last_cmd.val1 )
            {
                return true;
            }
        }
    }

    if( cmd_type==RE_COMMAND_DIRS )
    {
        return true;
    }
    else if( cmd_type==RE_COMMAND_DIGIT )
    {
        return false;
    }
    else if( cmd_type==RE_COMMAND_NATO )
    {
        return false;
    }
    else if( cmd_type==RE_COMMAND_META )
    {
        if( state->last_cmd.val2 )
        {
            return true;
        }
    }
    else if( cmd_type==RE_COMMAND_SUPER )
    {
        return true;
    }


    return false;
}

bool ReCaptain::isWakeUp(CCommand command)
{
    if( command.type==RE_COMMAND_NULL )
    {
        return false;
    }

    if( command.is_super==0 ||
        command.is_alt  ==1 ||
        command.is_ctrl ==1 ||
        command.is_shift==1 )
    {
        return false;
    }

    if( command.val1>=KEY_0 &&
        command.val1<KEY_7 )
    {
        return true;
    }

    return false;
}

bool ReCaptain::isSpeakerSw(CCommand command)
{

    if( command.type==RE_COMMAND_NULL )
    {
        return false;
    }

    if( command.is_super==0 ||
        command.is_alt  ==1 ||
        command.is_ctrl ==1 ||
        command.is_shift==1 )
    {
        return false;
    }

    if( command.val1==KEY_BACKSPACE &&
        command.val2==1 )
    {
        return true;
    }

    return false;
}

void ReCaptain::execMeta(CCommand command)
{
    CCommand translated;
    for( int j=0 ; j<command.val3 ; j++ )
    {
        translated = meta->castMeta(command.val1,
                                    command.val2);

        if( translated.type==RE_COMMAND_NATO ||
            translated.type==RE_COMMAND_DIRS ||
            translated.type==RE_COMMAND_DIGIT )
        {
            execKeyboard(translated);
        }
    }
}

void ReCaptain::wakeDictate()
{
    re_mouseKey(1);
    state->dictate_state = 0;
    QThread::msleep(500);

    // remove super+num
    ReKeyboard::pressKey(KEY_LEFTCTRL);
    ReKeyboard::pressKey(KEY_LEFTSHIFT);
    ReKeyboard::sendKey(KEY_LEFT);
    QThread::msleep(10);
    ReKeyboard::sendKey(KEY_LEFT);
    ReKeyboard::releaseKey(KEY_LEFTSHIFT);
    ReKeyboard::releaseKey(KEY_LEFTCTRL);
    QThread::msleep(100);

    ReKeyboard::sendKey(KEY_BACKSPACE);
    QThread::msleep(5); //little tweak
    ReKeyboard::sendKey(KEY_BACKSPACE);
    QThread::msleep(5); //little tweak

    // select all
    ReKeyboard::pressKey(KEY_LEFTCTRL);
    QThread::msleep(5); //little tweak
    ReKeyboard::sendKey(KEY_A);
    QThread::msleep(5); //little tweak
    ReKeyboard::releaseKey(KEY_LEFTCTRL);
    QThread::msleep(2000);

    // copy
    ReKeyboard::pressKey(KEY_LEFTCTRL);
    QThread::msleep(5); //little tweak
    ReKeyboard::sendKey(KEY_C);
    ReKeyboard::releaseKey(KEY_LEFTCTRL);
    QThread::msleep(1000);

    // quit
    ReKeyboard::pressKey(KEY_LEFTMETA);
    ReKeyboard::sendKey(KEY_Q);
    ReKeyboard::releaseKey(KEY_LEFTMETA);
    QThread::msleep(400);

    // paste
    ReKeyboard::pressKey(KEY_LEFTCTRL);
    ReKeyboard::sendKey(KEY_V);
    ReKeyboard::releaseKey(KEY_LEFTCTRL);

    state->wakeUp();
}

void ReCaptain::wakeRecord()
{
    state->record_state = 0;
    QThread::msleep(500);

    re_mouseMoveW(30, 30);
    QThread::msleep(100);
    re_mouseKey(1);

    state->wakeUp();
}
