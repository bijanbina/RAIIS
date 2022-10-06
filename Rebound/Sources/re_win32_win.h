#ifndef RE_WIN32_WIN_H
#define RE_WIN32_WIN_H

#include <Windows.h>
#include <psapi.h> // For access to GetModuleFileNameEx
#include <QDebug>

long reGetPid(HWND hWnd);
QString reGetPName(long pid);
int re_isVpnConnected();

#endif // RE_WIN32_WIN_H
