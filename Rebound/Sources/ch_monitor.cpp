#include "ch_monitor.h"
#include <QWindow>
#include <QDebug>

ChScreen ChMonitor::primary;
ChScreen ChMonitor::secondary;

#ifdef WIN32
static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdc,
                                    LPRECT lprcMonitor, LPARAM pData)
{
    (void)pData;        // to suppress unused warning
    (void)lprcMonitor;  // to suppress unused warning
    (void)hdc;          // to suppress unused warning
    MONITORINFOEXA mi;
    memset(&mi, 0, sizeof(mi));
    mi.cbSize = sizeof(mi);
    int success = GetMonitorInfoA(hMonitor, &mi);
    if( success==0 )
    {
        return TRUE;
    }

    int isPrimary = mi.dwFlags;
//    qDebug() << "is primary ="
//             << isPrimary
//             << mi.szDevice;
    if( isPrimary )
    {
        ChMonitor::primary.x = mi.rcWork.left;
        ChMonitor::primary.y = mi.rcWork.top;
        ChMonitor::primary.width  = mi.rcWork.right  - mi.rcWork.left;
        ChMonitor::primary.height = mi.rcWork.bottom - mi.rcWork.top;
    }
    else
    {
        ChMonitor::secondary.x = mi.rcWork.left;
        ChMonitor::secondary.y = mi.rcWork.top;
        ChMonitor::secondary.width  = mi.rcWork.right  - mi.rcWork.left;
        ChMonitor::secondary.height = mi.rcWork.bottom - mi.rcWork.top;
    }

    return TRUE;
}
#endif

ChMonitor::ChMonitor()
{
}

void ChMonitor::init()
{
#ifdef WIN32
    EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc, NULL);
#endif
}
