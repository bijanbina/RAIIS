#include "re_x11.h"

//Display *display;
Window  *winfocus;

Display *reX11_init()
{
//    winfocus = new Window;
//    display = XOpenDisplay(NULL);
    XInitThreads();
    Display *display = XOpenDisplay(NULL);

    setbuf(stdout,NULL);
    printf("hi\n");

    return display;
}

void reX11_exit(Display *display)
{
//    XFlush(display);
    XCloseDisplay(display);
    printf("48\n");
}

void sendKeyEvent(int isPress, int keysym)
{
    XEvent event;
    int    revert;
//    XGetInputFocus(display, winfocus, &revert);

//    if( isPress )
//    {
//      event.type=KeyPress;
//    }
//    else
//    {
//      event.type=KeyRelease;
//    }

//    event.xkey.keycode=XKeysymToKeycode(display, keysym);
//    event.xkey.display=display;
//    event.xkey.window=*winfocus;

//    XSendEvent(display, InputFocus,True,KeyPressMask,&event);
//    XFlush(display);
}

void sendFakePress(int keysym, Display *display)
{
    sendFakeEvent(0, keysym, display);
}

void sendFakeRelase(int keysym, Display *display)
{
    sendFakeEvent(0, keysym, display);
}

void sendFakeEvent(int isPress, int keysym, Display *display)
{
    printf("45\n");
    XInitThreads();
    printf("46\n");
    int keycode = XKeysymToKeycode(display, keysym);
    XTestFakeKeyEvent(display, keycode, isPress, CurrentTime);
    XFlush(display);
    printf("47\n");
}

void sendXFlush(Display *display)
{
    XFlush(display);
}

