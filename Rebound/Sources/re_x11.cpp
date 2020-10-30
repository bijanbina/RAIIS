#include "re_x11.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <X11/extensions/XTest.h>

Display *display;
Window  *winfocus;

void reX11_init()
{
    winfocus = new Window;
//    display = XOpenDisplay(NULL);
    setbuf(stdout,NULL);
    printf("hi\n");
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
    printf("44\n");

    printf("45\n");
    display = XOpenDisplay(NULL);
    printf("46\n");
    int keycode = XKeysymToKeycode(display, keysym);
    XTestFakeKeyEvent(display, keycode, isPress, CurrentTime);
    printf("47\n");
//    XFlush(display);
    XCloseDisplay(display);
    printf("48\n");
}

void sendXFlush()
{
    XFlush(display);
}

