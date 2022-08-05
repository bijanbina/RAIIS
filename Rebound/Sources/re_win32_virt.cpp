#include "re_win32_virt.h"
#include <initguid.h>
#include <windows.h>
#include <inspectable.h> // IInspectable, HSTRING, TrustLevel
#include <shobjidl.h> // IObjectArray, ObjectArray, IVirtualDesktopManager, VirtualDesktopManager
#include <strsafe.h> // StringCbPrintf
#include <QDebug>

ReWin32Virt::ReWin32Virt()
{
    pDesktopManager = NULL;
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    IServiceProvider* pServiceProvider = NULL;
    HRESULT hr = CoCreateInstance(
                        CLSID_ImmersiveShell, NULL, CLSCTX_LOCAL_SERVER,
                        __uuidof(IServiceProvider), (PVOID*)&pServiceProvider);

    qDebug() << "S_OK" << S_OK << hr;
    hr = pServiceProvider->QueryService(CLSID_VirtualDesktopAPI_Unknown,
                                        IID_IVirtualDesktopManagerInternal,
                                        (void **)&pDesktopManager);

    qDebug() << "S_OK" << S_OK << hr;
    pServiceProvider->Release();

    updateGUID();
}

ReWin32Virt::~ReWin32Virt()
{
    pDesktopManager->Release();
}

void ReWin32Virt::updateGUID()
{
    IObjectArray *desktops;
    IVirtualDesktop *nextDesktop;

    pDesktopManager->GetDesktops(&desktops);
    UINT count;
    desktops->GetCount(&count);

    for( unsigned int i=0 ; i<count ; i++ )
    {
        desktops->GetAt(i, UUID_IVirtualDesktop, (void**)&nextDesktop);

        GUID buffer;
        nextDesktop->GetID(&buffer);
        vd_guids << buffer;

        nextDesktop->Release();
    }

    desktops->Release();
}

void ReWin32Virt::setDesktop(int id)
{
    IObjectArray *desktops;
    IVirtualDesktop *nextDesktop;

    HRESULT hr = pDesktopManager->GetDesktops(&desktops);

    desktops->GetAt(id, UUID_IVirtualDesktop, (void**)&nextDesktop);
    desktops->Release();

    hr = pDesktopManager->SwitchDesktop(nextDesktop);
    nextDesktop->Release();

    qDebug() << "getCurrDesktop()" << getCurrDesktop();
}

int ReWin32Virt::getCurrDesktop()
{
    IVirtualDesktop *currDesktop;

    pDesktopManager->GetCurrentDesktop(&currDesktop);
    GUID curr_DesktopGUID;
    currDesktop->GetID(&curr_DesktopGUID);
    currDesktop->Release();

    for( int i=0 ; i<vd_guids.length() ; i++ )
    {
        if( curr_DesktopGUID==vd_guids[i] )
        {
            return i;
        }
    }

    return -1;
}
