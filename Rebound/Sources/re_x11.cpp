#include "re_x11.h"

Display *display;
Window  *winfocus;

Display *reX11_init()
{
//    winfocus = new Window;
    display = XOpenDisplay(NULL);
//    XInitThreads();
//    Display *display = XOpenDisplay(NULL);

    setbuf(stdout,NULL);
    printf("hi\n");

    return display;
}

void reX11_exit()
{
//    XFlush(display);
    XCloseDisplay(display);
    printf("48\n");
}


QStringList re_getWindowList()
{
    Window root = DefaultRootWindow(display);

    Window* root_return;
    Window* parent_return;
    Window* children;
    unsigned int nchildren;

    XQueryTree(dpy, root, root_return, parent_return,
               &children, &nchildren);

    XWindowAttributes attributes;
    char *name;

    if (!children)
        return 0;

    while (nchildren--)
    {
        XGetWindowAttributes(display, children[nchildren],
                          &attributes);
        if (attributes.map_state == IsViewable)
        {
            if (names)
            {
                if (XFetchName(display, children[nchildren], &name) && name)
                {
                    printf("%s ", name);
                    XFree(name);
                }
                else
                {
                    printf("Unknown ");
                }
            }
        }
    }

    XFree(children);
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

