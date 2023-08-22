#include "ch_monitor.h"
#include <QWindow>
#include <QDebug>

#ifdef WIN32
static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdc, LPRECT lprcMonitor, LPARAM pData)
{
    ChMonitor *mon = (ChMonitor *)pData;
    MONITORINFOEXA mi;
    memset(&mi, 0, sizeof(mi));
    mi.cbSize = sizeof(mi);
    int success = GetMonitorInfoA(hMonitor, &mi);
    if( success==0 )
    {
        return TRUE;
    }

    int isPrimary = mi.dwFlags;
    qDebug() << "is primary ="
             << isPrimary
             << mi.szDevice;
    if( isPrimary )
    {
        mon->primary.x = mi.rcWork.left;
        mon->primary.y = mi.rcWork.top;
        mon->primary.width  = mi.rcWork.right  - mi.rcWork.left;
        mon->primary.height = mi.rcWork.bottom - mi.rcWork.top;
    }
    else
    {
        mon->secondary.x = mi.rcWork.left;
        mon->secondary.y = mi.rcWork.top;
        mon->secondary.width  = mi.rcWork.right  - mi.rcWork.left;
        mon->secondary.height = mi.rcWork.bottom - mi.rcWork.top;
    }

    return TRUE;
}
#endif

ChMonitor::ChMonitor(QObject *parent) : QObject(parent)
{
#ifdef WIN32
    EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc, (LPARAM)this);
#endif
}

ChMonitor::~ChMonitor()
{
}
