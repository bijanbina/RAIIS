#ifndef RE_X11_H
#define RE_X11_H

#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <X11/extensions/XTest.h>

Display *reX11_init();
void reX11_exit(Display *display);
void sendKeyEvent(int isPress, int keysym);
void sendFakePress(int keysym, Display *display);
void sendFakeRelase(int keysym, Display *display);
void sendFakeEvent(int isPress, int keysym, Display *display);
void sendXFlush();

#endif // RE_X11_H
