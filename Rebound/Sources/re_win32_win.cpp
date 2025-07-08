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

    if( !(style & WS_EX_LAYERED) )
    {
        // Add the layered window style if it's not already present
        style |= WS_EX_LAYERED;
        SetWindowLongPtr(hwnd, GWL_EXSTYLE, style);
    }

    SetLayeredWindowAttributes(hwnd, 0, opacity, LWA_ALPHA);
}

QString ch_getClass(HWND hwnd)
{
    QString ret;
    TCHAR className[256];

    // Retrieve the window class name
    if( GetClassName(hwnd, className,
                     sizeof(className)/sizeof(TCHAR)) )
    {
        ret = QString::fromWCharArray(className);
    }
    else
    {
        qDebug() << "Failed to get window class name!";
    }

    // Retrieve window style and extended style
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
//    qDebug() << "Window Style:" << Qt::hex << style;
//    qDebug() << "Extended Style:" << Qt::hex << exStyle;

    // Mapping some styles to their Qt equivalents
    if( (style&WS_MAXIMIZEBOX)==0 )
    {
        ret = "popup";
    }
    else if( exStyle&WS_EX_DLGMODALFRAME )
    {
        ret = "dialog";
    }
    else if( style&WS_CAPTION && style&WS_THICKFRAME )
    {
        ret = "full";
    }
//    if( style&WS_MINIMIZEBOX )
//    {
//        qDebug() << "Qt::WindowFlags -> Qt::WindowMinimizeButtonHint";
//    }
//    if( style&WS_MAXIMIZEBOX )
//    {
//        qDebug() << "Qt::WindowFlags -> Qt::WindowMaximizeButtonHint";
//    }
//    if( exStyle&WS_EX_TOOLWINDOW )
//    {
//        qDebug() << "Qt::WindowFlags -> Qt::Tool";
//    }

    return ret;
}
