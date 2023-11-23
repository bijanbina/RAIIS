#include "re_win32_virt.h"
#include <initguid.h>
#include <windows.h>
#include <inspectable.h> // IInspectable, HSTRING, TrustLevel
#include <shobjidl.h> // IObjectArray, ObjectArray, IVirtualDesktopManager, VirtualDesktopManager
#include <strsafe.h> // StringCbPrintf
#include <QDebug>
#include <QThread>
#include "mm_api.h"
#include "mm_win32_guid.h"

ReWin32Virt::ReWin32Virt(QObject *parent): QObject(parent)
{
    manager_int = NULL;
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    IServiceProvider* services = NULL;
    HRESULT hr = CoCreateInstance(
                        CLSID_ImmersiveShell, NULL, CLSCTX_LOCAL_SERVER,
                        __uuidof(IServiceProvider), (PVOID*)&services);

    win_ver = mm_getWinVer();
    if( win_ver==MM_WIN10 )
    {
        initInternal_Win10(services);
    }
    else if( win_ver==MM_WIN11_21H2 )
    {
        initInternal_Win11_21H2(services);
    }
    services->Release();
}

ReWin32Virt::~ReWin32Virt()
{
    if( win_ver==MM_WIN10 )
    {
        manager_int->Release();
    }
    else if( win_ver==MM_WIN11_21H2 )
    {
        manager_int_win11_21H2->Release();
    }
}

void ReWin32Virt::initInternal_Win10(IServiceProvider *service)
{
    IObjectArray *desktops = NULL;
    IVirtualDesktop *c_desktop;
    HRESULT hr;

    hr = service->QueryService(CLSID_VirtualDesktopAPI_Unknown,
                               IID_IVirtualDesktopManagerInternal_Win10,
                               (void **)&manager_int);
    if( hr )
    {
        qDebug() << "IVirtualDesktopManagerInternal Failed" << hr;
    }

    hr = manager_int->GetDesktops(&desktops);
    UINT count;
    desktops->GetCount(&count);

    GUID buffer;
    for( unsigned int i=0 ; i<count ; i++ )
    {
        desktops->GetAt(i, UUID_IVirtualDesktop_Win10,
                        (void**)&c_desktop);

        c_desktop->GetID(&buffer);
        vd_guids << buffer;
    }

    desktops->Release();
}

void ReWin32Virt::initInternal_Win11_21H2(IServiceProvider* service)
{
    IObjectArray *desktops = NULL;
    IVirtualDesktop_Win11_21H2 *c_desktop_win11_21H2;
    HRESULT hr;

    hr = service->QueryService(CLSID_VirtualDesktopAPI_Unknown,
                        IID_IVirtualDesktopManagerInternal_Win11_21H2,
                        (void **)&manager_int_win11_21H2);
    if( hr )
    {
        qDebug() << "IVirtualDesktopManagerInternal Failed" << hr;
    }

    hr = manager_int_win11_21H2->GetDesktops(NULL, &desktops);
    UINT count;
    desktops->GetCount(&count);

    GUID buffer;

    for( unsigned int i=0 ; i<count ; i++ )
    {
        desktops->GetAt(i, UUID_IVirtualDesktop_Win11_21H2,
                        (void**)&c_desktop_win11_21H2);


        c_desktop_win11_21H2->GetID(&buffer);
        vd_guids << buffer;
    }

    desktops->Release();
}

void ReWin32Virt::setDesktop(int id)
{
    IObjectArray *desktops = NULL;
    if( win_ver==MM_WIN10 )
    {
        IVirtualDesktop *next_desktop;
        manager_int->GetDesktops(&desktops);
        desktops->GetAt(id, UUID_IVirtualDesktop_Win10,
                        (void**)&next_desktop);
        manager_int->SwitchDesktop(next_desktop);
    }
    else if( win_ver==MM_WIN11_21H2 )
    {
        IVirtualDesktop_Win11_21H2 *next_desktop;
        manager_int_win11_21H2->GetDesktops(NULL, &desktops);
        desktops->GetAt(id, UUID_IVirtualDesktop_Win11_21H2,
                        (void**)&next_desktop);
        manager_int_win11_21H2->SwitchDesktop(NULL, next_desktop);
    }
}

void ReWin32Virt::setFocus()
{
    QThread::msleep(100);

    POINT P;
    GetCursorPos(&P);

    HWND hwnd = WindowFromPoint(P);
    mm_focus(hwnd);
}
