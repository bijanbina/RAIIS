#ifndef RE_X11_H
#define RE_X11_H

#include <X11/keysym.h>
#include <X11/keysymdef.h>

void reX11_init();
void sendKeyEvent(int isPress, int keysym);
void sendFakeEvent(int isPress, int keysym);

#endif // RE_X11_H
