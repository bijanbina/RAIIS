#include "re_win32_win.h"
#include "backend.h"

int re_isVpnConnected()
{
    QString output = getStrCommand("netsh interface ipv4 show config | find \"MK2\"");

    if ( output.length() )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Function to get the window opacity
int  re_getWindowOpacity(HWND hwnd)
{
    BYTE opacity = 0;
    DWORD flags = 0;

    if (GetLayeredWindowAttributes(hwnd, NULL, &opacity, &flags))
    {
        if (flags & LWA_ALPHA)
        {
            return opacity;
        }
    }

    return 255;  // Default opacity if unable to retrieve
}

void re_setWindowOpacity(HWND hwnd, BYTE opacity)
{
    LONG_PTR style = GetWindowLongPtr(hwnd, GWL_EXSTYLE);

    if (!(style & WS_EX_LAYERED))
    {
        // Add the layered window style if it's not already present
        style |= WS_EX_LAYERED;
        SetWindowLongPtr(hwnd, GWL_EXSTYLE, style);
    }

    SetLayeredWindowAttributes(hwnd, 0, opacity, LWA_ALPHA);
}
