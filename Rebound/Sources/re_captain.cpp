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
            if( commands[i].type!=RE_COMMAND_MOD )
            {
                continue;
            }
            else //type==RE_COMMAND_MOD
            {
                if( isWakeUp(commands[i]) )
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
                        execCommand(commands[i]);
                        commands.clear();
                        qDebug() << "Wake Up";
                        return;
                    }
                }
                else if( isSpeakerSw(commands[i]) )
                {
                    execCommand(commands[i]);
                    return;
                }
            }
        }
        else
        {
            execCommand(commands[i]);
        }
    }
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

        for( int j=0 ; j<command.val2 ; j++ )
        {
            key->sendKey(command.val1);
            QThread::msleep(5); //little tweak
        }
    }
    else if( command.type==RE_COMMAND_MOD )
    {
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
    else if( cmd_type==RE_COMMAND_MOD )
    {
        if( state->last_cmd.val1 )
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
    if( command.type!=RE_COMMAND_MOD )
    {
        return false;
    }

    if( command.mod_list.size()==0 )
    {
        return false;
    }

    if( command.mod_list[0]==KEY_META )
    {
        if( command.val1>=KEY_0 &&
            command.val1<KEY_7 )
        {
            return true;
        }
    }

    return false;
}

bool ReCaptain::isSpeakerSw(CCommand command)
{
    if( command.type!=RE_COMMAND_MOD )
    {
        return false;
    }

    if( command.mod_list.size()==0 )
    {
        return false;
    }

    if( command.mod_list[0]==KEY_META )
    {
        if( command.val1==KEY_BACKSPACE &&
            command.val2==1 )
        {
            return true;
        }
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
            for( int j=0 ; j<translated.val2 ; j++ )
            {
                key->sendKey(translated.val1);
                QThread::msleep(5); //little tweak
            }
        }
        else if( translated.type==RE_COMMAND_MOD )
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
    key->pressKey(KEY_LEFTCTRL);
    key->pressKey(KEY_LEFTSHIFT);
    key->sendKey(KEY_LEFT);
    QThread::msleep(10);
    key->sendKey(KEY_LEFT);
    key->releaseKey(KEY_LEFTSHIFT);
    key->releaseKey(KEY_LEFTCTRL);
    QThread::msleep(100);

    key->sendKey(KEY_BACKSPACE);
    QThread::msleep(5); //little tweak
    key->sendKey(KEY_BACKSPACE);
    QThread::msleep(5); //little tweak

    // select all
    key->pressKey(KEY_LEFTCTRL);
    QThread::msleep(5); //little tweak
    key->sendKey(KEY_A);
    QThread::msleep(5); //little tweak
    key->releaseKey(KEY_LEFTCTRL);
    QThread::msleep(2000);

    // copy
    key->pressKey(KEY_LEFTCTRL);
    QThread::msleep(5); //little tweak
    key->sendKey(KEY_C);
    key->releaseKey(KEY_LEFTCTRL);
    QThread::msleep(1000);

    // quit
    key->pressKey(KEY_META);
    key->sendKey(KEY_Q);
    key->releaseKey(KEY_META);
    QThread::msleep(400);

    // paste
    key->pressKey(KEY_LEFTCTRL);
    key->sendKey(KEY_V);
    key->releaseKey(KEY_LEFTCTRL);

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
