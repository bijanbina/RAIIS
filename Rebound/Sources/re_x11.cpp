#include "re_x11.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <X11/extensions/XTest.h>

Display *display;
Window  *winfocus;

void reX11_init()
{
    winfocus = new Window;
    display = XOpenDisplay(0);
//    setbuf(stdout,NULL);
//    printf("hi\n");
}

void sendKeyEvent(int isPress, int keysym)
{
    XEvent event;
    int    revert;
    XGetInputFocus(display, winfocus, &revert);

    if( isPress )
    {
      event.type=KeyPress;
    }
    else
    {
      event.type=KeyRelease;
    }

    event.xkey.keycode=XKeysymToKeycode(display, keysym);
    event.xkey.display=display;
    event.xkey.window=*winfocus;

    XSendEvent(display, InputFocus,True,KeyPressMask,&event);
    XFlush(display);
}

void sendFakeEvent(int isPress, int keysym)
{
    int keycode = XKeysymToKeycode(display, keysym);

    XTestFakeKeyEvent(display, keycode, isPress, 0);
    XFlush(display);

    printf("bye\n");
}
