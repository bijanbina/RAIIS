#ifndef RE_MOUSE_H
#define RE_MOUSE_H

#include <stdio.h>
#include <QVector>

#ifdef WIN32
#include <Windows.h>
#endif

void re_mouseKey(int btn);
void re_mousePress(int btn);
void re_mouseRelease(int btn);

void re_mouseMoveR(int x, int y);
void re_mouseMoveW(int x_offset, int y_offset);
void re_mouseMoveW_tr(int x_offset, int y_offset);
void re_mouseMoveW_br(int x_offset, int y_offset);
void re_mouseMoveC(int x_offset, int y_offset);

#endif // RE_MOUSE_H
