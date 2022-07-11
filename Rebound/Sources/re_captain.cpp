#include "re_captain.h"
#include <unistd.h>
#include <fcntl.h>

ReCaptain::ReCaptain(ReState *st, QObject *parent): QObject(parent)
{
    state = st;
    meta  = new ReMeta (state);
    super = new ReSuperL(state);
    key   = new ReKeyboard;
    state->last_cmd.type = RE_COMMAND_NULL;
}

ReCaptain::~ReCaptain()
{
    delete meta;
    delete super;
}

void ReCaptain::execModifier(CCommand command)
{
    int len = command.mod_list.size();
    for( int i=0 ; i<len ; i++ )
    {
        key->pressKey(command.mod_list[i]);
    }

    for( int j=0 ; j<command.val2 ; j++ )
    {
        key->sendKey(command.val1);
        QThread::msleep(30); //little tweak
    }

    QThread::msleep(70); //little tweak
    for( int i=0 ; i<len ; i++ )
    {
        key->releaseKey(command.mod_list[len-i-1]);
    }
//    qDebug() << "pressModifier" << modifiers.count();
}

void ReCaptain::releaseModifiers()
{
    int c = modifiers.count();
    for( int i=c ; i>0 ; i-- )
    {
//        qDebug() << "releaseModifiers" << modifiers[i-1].val1;
        key->releaseKey(modifiers[i-1].val1);
        QThread::msleep(100); //little tweak
    }
    modifiers.clear();
}

void ReCaptain::execute(QVector<CCommand> commands)
{
    for( int i=0 ; i<commands.length() ; i++ )
    {
        if( state->isSleep() )
        {
            if( commands[i].type!=RE_COMMAND_META )
            {
                continue;
            }
            else //type==RE_COMMAND_META
            {
                if( isWakeUp(commands[i]) )
                {
                    state->wakeUp();
                    commands.clear();
                    qDebug() << "Wake Up";
                    return;
                }
            }
        }
        else
        {
            execCommand(commands[i]);
        }
    }
//    releaseModifiers();
}

void ReCaptain::execCommand(CCommand command)
{
    state->last_cmd = command;
    if( command.type==RE_COMMAND_NATO ||
        command.type==RE_COMMAND_DIRS ||
        command.type==RE_COMMAND_DIGIT )
    {
        for( int j=0 ; j<command.val2 ; j++ )
        {
            key->sendKey(command.val1);
            QThread::msleep(5); //little tweak
        }

        if( state->isEscape(command) )
        {
            state->resetState();
        }
    }
    else if( command.type==RE_COMMAND_MOD )
    {
        execModifier(command);
    }
    else if( command.type==RE_COMMAND_META )
    {
        for( int j=0 ; j<command.val3 ; j++ )
        {
            meta->execMeta(command);
        }
    }
    else if( command.type==RE_COMMAND_SUPER )
    {
        for( int j=0 ; j<command.val3 ; j++ )
        {
            super->exec(command);
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
    if( command.type==RE_COMMAND_META )
    {
        if( command.val1==RE_META_GO )
        {
            if( command.val2==17 ) //wake->w->17
            {
                return true;
            }
        }
    }

    return false;
}
