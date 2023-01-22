#include "re_keyboard_l.h"
#include <unistd.h>
#include <fcntl.h>

ReKeyEmulator::ReKeyEmulator()
{
    struct uinput_setup usetup;

    uinput_f = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    if( uinput_f==-1 )
    {
        qDebug() << "Try to set /dev/uinput permission";
        system("pkexec " RE_SCR_UINPUT);
        uinput_f = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
        if( uinput_f==-1 )
        {
            exit(1);
            qDebug() << "Failed to open /dev/uinput";
        }
    }

    // ioctls enable the device to pass key events
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

ReKeyEmulator::~ReKeyEmulator()
{
    ioctl(uinput_f, UI_DEV_DESTROY);
    close(uinput_f);
}

void ReKeyEmulator::setKey(int type, int code, int val)
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

void ReKeyEmulator::sendKey(int key_val)
{
    pressKey(key_val);
    releaseKey(key_val);
}

void ReKeyEmulator::pressKey(int key_val)
{
    /* Key press, report the event, send key release, and report again */
    setKey(EV_KEY, key_val, 1);
    setKey(EV_SYN, SYN_REPORT, 0);
}

void ReKeyEmulator::releaseKey(int key_val)
{
    setKey(EV_KEY, key_val, 0);
    setKey(EV_SYN, SYN_REPORT, 0);
}
