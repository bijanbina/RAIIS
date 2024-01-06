#ifndef RE_CALLBACK_W_H
#define RE_CALLBACK_W_H

#include <QString>
#include <QTimer>
#include <dwmapi.h>
#include <tlhelp32.h> // to get pid
#include <tchar.h> // to get file path
#include <psapi.h> // For access to GetModuleFileNameEx
#include "backend.h"
#include "re_commands.h"

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
BOOL CALLBACK EnumChildProc  (HWND hwnd, LPARAM lParam);
ReWindow re_readWindow(HWND hwnd);
int      re_cleanRemoteId(QString title);
int      re_isNormalHwnd(HWND hwnd);

#endif // RE_CALLBACK_W_H
