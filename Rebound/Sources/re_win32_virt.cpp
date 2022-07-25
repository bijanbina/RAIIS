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
                                        IID_IVirtualDesktopManagerInternal, (void **)&pDesktopManager);

//    hr = IServiceProvider_QueryService(pServiceProvider,CLSID_VirtualDesktopAPI_Unknown,
//                                        IID_IVirtualDesktopManagerInternal, (void **)&pDesktopManager);
    qDebug() << "S_OK" << S_OK << hr;
    pServiceProvider->Release();
}

ReWin32Virt::~ReWin32Virt()
{
    pDesktopManager->Release();
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
}
