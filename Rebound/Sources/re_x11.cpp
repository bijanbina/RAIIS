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


//QStringList re_getWindowList()
void re_getWindowList()
{
    Window root = DefaultRootWindow(display);
    Window root_return;
    Window parent_return;
    Window* children;
    unsigned int nchildren;
    Atom *atoms;

    XQueryTree(display, root, &root_return, &parent_return,
               &children, &nchildren);
    XWindowAttributes attributes;
    char *name;

    if (!children)
        return;

    for (int i=0 ; i<nchildren ; i++ )
    {
        XGetWindowAttributes(display, children[i],
                          &attributes);
        atoms=NULL;


        if (attributes.map_state == IsViewable)
        {
            //Filter out fake windows of gnome
            if ( attributes.width!=1 && attributes.c_class==1 )
            {
                XFetchName(display, children[i], &name);
                if ( name )
                {
                    printf("<%s> %lx w:%d h:%d\n", name,
                           children[i], attributes.width,
                           attributes.height);
                    XFree(name);
                }
                else
                {
                    printf("Unknown 0x%lx\n", children[i]);
                    re_listProperty(children[i]);
                }
            }
            else
            {
                printf("Unknown 0x%lx\n", children[i]);
            }
        }
        else
        {
            printf("Not Viewable 0x%lx\n", children[i]);
        }
    }

    XFree(children);
}

Window *x11_getWinList (unsigned long *size)
{
    Window *client_list;
    Window root = DefaultRootWindow(display);
    char propperty_name[30] = "_NET_CLIENT_LIST";

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
    char *ret;

    xa_prop_name = XInternAtom(display, prop_name, False);

    if (XGetWindowProperty(display, win, xa_prop_name, 0, 1024, False,
            xa_prop_type, &xa_ret_type, &ret_format,
            &ret_nitems, &ret_bytes_after, &ret_prop) != Success)
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
    ret = (char *)malloc(tmp_size + 1);
    memcpy(ret, ret_prop, tmp_size);
    ret[tmp_size] = '\0';

    if (size)
    {
        *size = tmp_size;
    }

    XFree(ret_prop);
    return ret;
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
