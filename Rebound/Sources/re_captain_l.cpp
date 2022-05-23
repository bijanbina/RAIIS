#include "re_captain_l.h"
#include <unistd.h>
#include <fcntl.h>

ReCaptainL::ReCaptainL(ReState *st, QObject *parent): QObject(parent)
{
    state = st;
    meta = new ReMetaL(state);
    state->last_cmd.type = RE_COMMAND_NULL;

    struct uinput_setup usetup;

    uinput_f = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    if( uinput_f==-1 )
    {
        qDebug() << "Failed to open /dev/uinput";
        exit(1);
    }

    /*
     * The ioctls below will enable the device that is about to be
     * created, to pass key events, in this case the space key.
     */
    ioctl(uinput_f, UI_SET_EVBIT, EV_KEY);

    // enable all the keys
    // no better solution found :(
    for( int keycode=KEY_ESC ; keycode<KEY_COMPOSE ; keycode++)
    {
        ioctl(uinput_f, UI_SET_KEYBIT, keycode);
    }

    ioctl(uinput_f, UI_SET_KEYBIT, KEY_SPACE);

    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor  = 0x1234; /* sample vendor */
    usetup.id.product = 0x5678; /* sample product */
    strcpy(usetup.name, "Rebound Keyboard");

    ioctl(uinput_f, UI_DEV_SETUP, &usetup);
    ioctl(uinput_f, UI_DEV_CREATE);
}

ReCaptainL::~ReCaptainL()
{
    ioctl(uinput_f, UI_DEV_DESTROY);
    close(uinput_f);
}

void ReCaptainL::setKey(int type, int code, int val)
{
   struct input_event ie;

   ie.type = type;
   ie.code = code;
   ie.value = val;
   /* timestamp values below are ignored */
   ie.time.tv_sec = 0;
   ie.time.tv_usec = 0;

   write(uinput_f, &ie, sizeof(ie));
}

void ReCaptainL::sendKey(int key_val)
{
    pressKey(key_val);
    releaseKey(key_val);
}

void ReCaptainL::pressKey(int key_val)
{
    /* Key press, report the event, send key release, and report again */
    setKey(EV_KEY, key_val, 1);
    setKey(EV_SYN, SYN_REPORT, 0);
}

void ReCaptainL::releaseKey(int key_val)
{
    setKey(EV_KEY, key_val, 0);
    setKey(EV_SYN, SYN_REPORT, 0);
}

void ReCaptainL::execModifier(CCommand command)
{
    int len = command.mod_list.size();
    for( int i=0 ; i<len ; i++ )
    {
        pressKey(command.mod_list[i]);
    }

    for( int j=0 ; j<command.val2 ; j++ )
    {
        sendKey(command.val1);
        QThread::msleep(30); //little tweak
    }

    QThread::msleep(70); //little tweak
    for( int i=0 ; i<len ; i++ )
    {
        releaseKey(command.mod_list[len-i-1]);
    }
//    qDebug() << "pressModifier" << modifiers.count();
}

void ReCaptainL::releaseModifiers()
{
    int c = modifiers.count();
    for( int i=c ; i>0 ; i-- )
    {
//        qDebug() << "releaseModifiers" << modifiers[i-1].val1;
        releaseKey(modifiers[i-1].val1);
        QThread::msleep(100); //little tweak
    }
    modifiers.clear();
}

void ReCaptainL::execute(QVector<CCommand> commands)
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

void ReCaptainL::execCommand(CCommand command)
{
    state->last_cmd = command;
    if( command.type==RE_COMMAND_NATO ||
        command.type==RE_COMMAND_DIRS ||
        command.type==RE_COMMAND_DIGIT )
    {
        for( int j=0 ; j<command.val2 ; j++ )
        {
            sendKey(command.val1);
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
}
bool ReCaptainL::isLastRepeatable()
{
    int cmd_type = state->last_cmd.type;

    if( state->scroll_dir )
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
    else if( cmd_type==RE_COMMAND_MOD  )
    {
        if( state->last_cmd.val1 )
        {
            return true;
        }
    }

    return false;
}

bool ReCaptainL::isWakeUp(CCommand command)
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
