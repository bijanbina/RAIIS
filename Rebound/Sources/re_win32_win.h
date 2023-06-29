#ifndef RE_WIN32_WIN_H
#define RE_WIN32_WIN_H

#include <Windows.h>
#include <psapi.h> // For access to GetModuleFileNameEx
#include <QDebug>

long reGetPid(HWND hWnd);
int  re_isVpnConnected();
void re_setWindowOpacity(HWND hwnd, BYTE opacity);
int  re_getWindowOpacity(HWND hwnd);
QString reGetPName(long pid);

#endif // RE_WIN32_WIN_H
