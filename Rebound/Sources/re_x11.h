#ifndef RE_X11_H
#define RE_X11_H

#include <QVector>
#include <QDebug>
#include <QFile>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <stdio.h>
#include <X11/Xlib.h>
//#include <X11/extensions/XTest.h>
#include <X11/Xutil.h>

typedef struct ReXWindow
{
    QString title;
    QString process_name;
    int desktop_id;
    int pid;
}ReXWindow;

Display *reX11_init();
void reX11_exit();
QVector<ReXWindow> re_getWindowList();
void re_listProperty(Window window);

int x11_currentDesktop();
Window x11_currentWindow();
QString x11_getPname(int pid);
int x11_getPid(Window window);
int x11_getDesktop(Window window);
Window *x11_getWinList (unsigned long *size);
char *x11_getProperty (Window win, Atom xa_prop_type,
                    char *prop_name, unsigned long *size);
void sendFakePress(int keysym, Display *display);
void sendFakeRelase(int keysym, Display *display);
void sendFakeEvent(int isPress, int keysym, Display *display);
void sendXFlush();

#endif // RE_X11_H
