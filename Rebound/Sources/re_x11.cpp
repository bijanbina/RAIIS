#include "re_x11.h"
#include <string.h>
#include <stdlib.h>
#include <X11/Xatom.h>

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

void re_getWindowList()
{
    Window* children;
    unsigned long nchildren;

    children = x11_getWinList(&nchildren);
    int desktop_id = x11_currentDesktop();

    printf("Desktop: %d\n", desktop_id);
    char *name;

    if (!children)
        return;

    for ( unsigned long i=0 ; i<nchildren ; i++ )
    {
        XFetchName(display, children[i], &name);
        if ( name )
        {
            int win_desktop = x11_getDesktop(children[i]);

            if ( win_desktop==desktop_id)
            {
                printf("%d: <%s>\n", win_desktop, name);
                XFree(name);
            }
        }
    }

    XFree(children);
}

int x11_getDesktop(Window window)
{
    unsigned long *desktop_id;
    char propperty_name[40] = "_NET_WM_DESKTOP";

    desktop_id = (unsigned long *)x11_getProperty(window, XA_CARDINAL,
                              propperty_name, NULL);

    int ret = *desktop_id;
    return ret;

}

int x11_currentDesktop()
{
    unsigned long *desktop_id;
    Window root = DefaultRootWindow(display);
    char propperty_name[40] = "_NET_CURRENT_DESKTOP";

    desktop_id = (unsigned long *)x11_getProperty(root, XA_CARDINAL,
                              propperty_name, NULL);

    int ret = *desktop_id;
    return ret;
}

Window *x11_getWinList (unsigned long *size)
{
    Window *client_list;
    Window root = DefaultRootWindow(display);
//    char propperty_name[40] = "_NET_CLIENT_LIST";
    char propperty_name[40] = "_NET_CLIENT_LIST_STACKING";

    client_list = (Window *)x11_getProperty(root, XA_WINDOW,
                              propperty_name, size);

    return client_list;
}

char *x11_getProperty (Window win, Atom xa_prop_type,
                    char *prop_name, unsigned long *size)
{
    Atom xa_prop_name;
    Atom xa_ret_type;
    int ret_format;
    unsigned long ret_nitems;
    unsigned long ret_bytes_after;
    unsigned long tmp_size;
    unsigned char *ret_prop;
    char *ret_data;

    xa_prop_name = XInternAtom(display, prop_name, False);

    int ret = XGetWindowProperty(display, win, xa_prop_name, 0, 1024, False,
                                xa_prop_type, &xa_ret_type, &ret_format,
                                &ret_nitems, &ret_bytes_after, &ret_prop);
    if ( ret!=Success )
    {
        return NULL;
    }

    if (xa_ret_type != xa_prop_type)
    {
        XFree(ret_prop);
        return NULL;
    }

    /* null terminate the result to make string handling easier */
    tmp_size = (ret_format / (32 / sizeof(long))) * ret_nitems;
    ret_data = (char *)malloc(tmp_size + 1);
    memcpy(ret_data, ret_prop, tmp_size);
    ret_data[tmp_size] = '\0';

    if (size)
    {
        *size = tmp_size;
    }

    XFree(ret_prop);
    return ret_data;
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

void re_listProperty(Window window)
{
    int nprops;
    Atom *atoms = XListProperties(display, window, &nprops);
    printf("---------------- Properties of window 0x%lx: -------------------\n", window);

    for(int i = 0; i < nprops; i++)
    {
//        printf("  atom[%d] = %lu:", i, atoms[i]);
        char *name = XGetAtomName(display, atoms[i]);
        printf("name=%s", name);
        XFree(name);

        Atom actual_type;
        int actual_format;
        unsigned long nitems;
        unsigned long bytes;
        unsigned char *data;

        XGetWindowProperty(display, window, atoms[i], 0,
                           ~(0L), false, AnyPropertyType,
                           &actual_type, &actual_format,
                           &nitems, &bytes, &data);

        printf("    actual_type=%lu", actual_type);
//        printf("    actual_format=%d", actual_format);
//        printf("    nitems=%lu", nitems);
//        printf("    bytes=%lu\n", bytes);
        if((actual_format == 8) && (nitems < 64))
        {
            char buf[nitems + 1];
            memcpy(buf, data, nitems);
            buf[nitems] = 0;
            printf("    data='%s'\n", data);
        }
        else if((actual_format == 32) && (nitems == 1))
        {
            printf("    data=%d\n", *((int*)data));
        }
        else
        {
            printf(" \n");
        }

        XFree(data);
    }
}
