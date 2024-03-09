#include "re_captain.h"
#include <unistd.h>
#include <fcntl.h>

ReCaptain::ReCaptain(QObject *parent): QObject(parent)
{
    ReState::last_cmd.type = RE_COMMAND_NULL;
}

ReCaptain::~ReCaptain()
{
}

void ReCaptain::execute(QVector<CCommand> commands)
{
    for( int i=0 ; i<commands.length() ; i++ )
    {
        if( ReState::sleep_state )
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
            ReState::last_cmd = commands[i];
            execCommand(commands[i]);
        }
    }
}

void ReCaptain::execCommand(CCommand command)
{
    if( command.type==RE_COMMAND_NATO ||
        command.type==RE_COMMAND_DIRS ||
        command.type==RE_COMMAND_DIGIT )
    {
        if( ReState::isEscape(command) )
        {
            if( ReState::stopFFScroll() )
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
        int count = command.val2;
        ReSuper::cast(command.val1, &command);
        for( int i=0 ; i<count ; i++ )
        {
            execCommand(command);
        }
    }
    else if( command.type==RE_COMMAND_CHESS )
    {
        execChess(command);
    }
    else if( command.type==RE_COMMAND_MOUSE )
    {
        execMouse(command);
    }
    else if( command.type==RE_COMMAND_QDIGIT )
    {
        re_getQtCmd(command);
    }
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

void ReCaptain::execMeta(CCommand command)
{
    CCommand translated;
    for( int j=0 ; j<command.val3 ; j++ )
    {
        translated = ReMeta::castMeta(command.val1,
                                    command.val2);
        execCommand(translated);
    }
}

void ReCaptain::execChess(CCommand command)
{
    CCommand translated;
    for( int j=0 ; j<command.val3 ; j++ )
    {
        ///SHOULD be written
//        translated = meta->castMeta(command.val1,
//                                    command.val2);

//        if( translated.type==RE_COMMAND_NATO ||
//            translated.type==RE_COMMAND_DIRS ||
//            translated.type==RE_COMMAND_DIGIT )
//        {
//            execKeyboard(translated);
//        }
    }
}

void ReCaptain::execMouse(CCommand command)
{
    CCommand translated;
    int count = command.val2 * command.val3;
    for( int j=0 ; j<count ; j++ )
    {
        if( command.val1==RE_MOUSE_LEFT )
        {
            re_mouseKey(1);
        }
        else if( command.val1==RE_MOUSE_MIDDLE )
        {
            re_mouseKey(2);
        }
        else if( command.val1==RE_MOUSE_RIGHT )
        {
            re_mouseKey(3);
        }
        else if( command.val1==RE_MOUSE_UP )
        {
            re_mouseKey(4);
            QThread::msleep(50);
        }
        else if( command.val1==RE_MOUSE_DOWN )
        {
            re_mouseKey(5);
            QThread::msleep(50);
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
            if( ReState::dictate_state )
            {
                wakeDictate();
            }
            else if( ReState::record_state )
            {
                wakeRecord();
            }
            else
            {
                ReState::wakeUp();
                execCommand(command);
                qDebug() << "Wake Up";
                return 1;
            }
        }
        else if( isSpeakerSw(command) )
        {
//            execCommand(command);
#ifdef WIN32
            RePipe::sendMom("super sound");
#else

#endif
            return 0;
        }
    }

    return 0;
}

bool ReCaptain::isLastRepeatable()
{
    int cmd_type = ReState::last_cmd.type;

    if( ReState::link->sc_dir )
    {
        return false;
    }

    if( cmd_type!=RE_COMMAND_NULL )
    {
        if( ReState::last_cmd.is_alt  || ReState::last_cmd.is_shift ||
            ReState::last_cmd.is_ctrl || ReState::last_cmd.is_super )
        {
            if( ReState::last_cmd.val1 )
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
        if( ReState::last_cmd.val2 )
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

void ReCaptain::wakeDictate()
{
    re_mouseKey(1);
    ReState::dictate_state = 0;
    QThread::msleep(50);

    // copy to clipboard
#ifdef WIN32
    SetCursorPos(1450, 880);
#endif
    re_mouseKey(1);
    QThread::msleep(1000);

//    // remove super+num from clipboard

    // quit
    re_hideSpeechNote();
    QThread::msleep(20);
    ReKeyboard::pressKey(KEY_LEFTALT);
    ReKeyboard::sendKey(KEY_TAB);
    ReKeyboard::releaseKey(KEY_LEFTALT);
    QThread::msleep(200);

    // paste
    ReKeyboard::pressKey(KEY_LEFTCTRL);
    ReKeyboard::sendKey(KEY_V);
    ReKeyboard::releaseKey(KEY_LEFTCTRL);

    ReState::wakeUp();
}

void ReCaptain::wakeRecord()
{
    ReState::record_state = 0;
    QThread::msleep(500);

    re_mouseMoveW_br(30, 30);
    QThread::msleep(100);
    re_mouseKey(1);

    ReState::wakeUp();
}
