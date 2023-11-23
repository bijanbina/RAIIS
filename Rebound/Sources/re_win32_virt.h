#ifndef RE_WIN32_VIRT_H
#define RE_WIN32_VIRT_H

#include "re_config.h"
#include <windows.h>
#include <Hstring.h>
#include <objbase.h>
#include <ObjectArray.h>
#include <QVector>
#include <QObject>
#include <QTimer>
// https://github.com/senfiron/win10-virtual-desktop-switcher/tree/master/VirtualDesktopSwitcher/VirtualDesktopSwitcher
// https://github.com/chuckrector/virtual_desktopper/blob/main/virtual_desktopper.h

const CLSID CLSID_ImmersiveShell = {
    0xC2F03A33, 0x21F5, 0x47FA, {0xB4, 0xBB, 0x15, 0x63, 0x62, 0xA2, 0xF2, 0x39} };

const CLSID CLSID_VirtualDesktopAPI_Unknown = {
    0xC5E0CDCA, 0x7B6E, 0x41B2, {0x9F, 0xC4, 0xD9, 0x39, 0x75, 0xCC, 0x46, 0x7B} };

const IID IID_IVirtualDesktopManagerInternal = {
    0xf31574d6,0xb682,0x4cdc,{0xbd,0x56,0x18,0x27,0x86,0x0a,0xbe,0xc6}};

struct IApplicationView : public IUnknown
{ };

struct IVirtualDesktop : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE IsViewVisible(
        IApplicationView *pView, int *pfVisible) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetID(
        GUID *pGuid) = 0;
};

struct IVirtualDesktop_Win11_21H2 : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE IsViewVisible(
        IApplicationView *pView, int *pfVisible) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetID(
        GUID *pGuid) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetMonitor(
        HMONITOR hMonitor) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetName(
        HSTRING* pName) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetWallpaper(
        HSTRING* pName) = 0;
};

struct IVirtualDesktopManagerInternal : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE GetCount(
        UINT *pCount) = 0;

    virtual HRESULT STDMETHODCALLTYPE MoveViewToDesktop(
        IApplicationView *pView,
        IVirtualDesktop *pDesktop) = 0;

    // 10240
    virtual HRESULT STDMETHODCALLTYPE CanViewMoveDesktops(
        IApplicationView *pView,
        int *pfCanViewMoveDesktops) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetCurrentDesktop(
        IVirtualDesktop** desktop) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetDesktops(
        IObjectArray **ppDesktops) = 0;

    // Получение соседнего рабочего стола относительно указанного, с учетом направления
    virtual HRESULT STDMETHODCALLTYPE GetAdjacentDesktop(
        IVirtualDesktop *pDesktopReference,
        int uDirection,
        IVirtualDesktop **ppAdjacentDesktop) = 0;

    virtual HRESULT STDMETHODCALLTYPE SwitchDesktop(
        IVirtualDesktop *pDesktop) = 0;

    virtual HRESULT STDMETHODCALLTYPE CreateDesktopW(
        IVirtualDesktop **ppNewDesktop) = 0;

    // pFallbackDesktop - рабочий стол на который будет совершен переход после удаления указанного
    virtual HRESULT STDMETHODCALLTYPE RemoveDesktop(
        IVirtualDesktop *pRemove,
        IVirtualDesktop *pFallbackDesktop) = 0;

    // 10240
    virtual HRESULT STDMETHODCALLTYPE FindDesktop(
        GUID *desktopId,
        IVirtualDesktop **ppDesktop) = 0;
};

struct IVirtualDesktopManagerInternal_WIN11_21H2 : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE GetCount(HMONITOR hMonitor,
        UINT *pCount) = 0;

    virtual HRESULT STDMETHODCALLTYPE MoveViewToDesktop(
        IApplicationView *pView,
        IVirtualDesktop_Win11_21H2 *pDesktop) = 0;

    // 10240
    virtual HRESULT STDMETHODCALLTYPE CanViewMoveDesktops(
        IApplicationView *pView,
        BOOL *pfCanViewMoveDesktops) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetCurrentDesktop(
        HMONITOR hMonitor,
        IVirtualDesktop_Win11_21H2** desktop) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetDesktops(
        HMONITOR hMonitor,
        IObjectArray **ppDesktops) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetAdjacentDesktop(
        IVirtualDesktop_Win11_21H2 *pDesktopReference,
        int uDirection,
        IVirtualDesktop_Win11_21H2 **ppAdjacentDesktop) = 0;

    virtual HRESULT STDMETHODCALLTYPE SwitchDesktop(
        HMONITOR hMonitor,
        IVirtualDesktop_Win11_21H2 *pDesktop) = 0;

    virtual HRESULT STDMETHODCALLTYPE CreateDesktopW(
        IVirtualDesktop_Win11_21H2 **ppNewDesktop) = 0;

    // 21313
    virtual HRESULT STDMETHODCALLTYPE MoveDesktop(
            IVirtualDesktop_Win11_21H2* pMoveDesktop, HMONITOR hMonitor, int nIndex) = 0;

    virtual HRESULT STDMETHODCALLTYPE RemoveDesktop(
        IVirtualDesktop_Win11_21H2 *pRemove,
        IVirtualDesktop_Win11_21H2 *pFallbackDesktop) = 0;

    // 10240
    virtual HRESULT STDMETHODCALLTYPE FindDesktop(
        GUID *desktopId,
        IVirtualDesktop_Win11_21H2 **ppDesktop) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetDesktopSwitchIncludeExcludeViews(
            IVirtualDesktop_Win11_21H2* pDesktop, IObjectArray** ppLeftDesktops,
            IObjectArray** ppRightDesktops) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetDesktopName(
            IVirtualDesktop_Win11_21H2* pDesktop, HSTRING name) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetDesktopWallpaper(
            IVirtualDesktop_Win11_21H2* pDesktop, HSTRING path) = 0;

    virtual HRESULT STDMETHODCALLTYPE UpdateWallpaperPathForAllDesktops(
            HSTRING text) = 0;

    virtual HRESULT STDMETHODCALLTYPE CopyDesktopState(
            /*IApplicationView*/ IUnknown* pView0,
            /*IApplicationView*/ IUnknown* pView1) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetDesktopIsPerMonitor(
            BOOL* bPerMonitor) = 0;

    // 21359
    virtual HRESULT STDMETHODCALLTYPE SetDesktopIsPerMonitor(BOOL state) = 0;
};

MIDL_INTERFACE("a5cd92ff-29be-454c-8d04-d82879fb3f1b")
IVirtualDesktopManager : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE IsWindowOnCurrentVirtualDesktop(
        /* [in] */ __RPC__in HWND topLevelWindow,
        /* [out] */ __RPC__out BOOL *onCurrentDesktop) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetWindowDesktopId(
        /* [in] */ __RPC__in HWND topLevelWindow,
        /* [out] */ __RPC__out GUID *desktopId) = 0;

    virtual HRESULT STDMETHODCALLTYPE MoveWindowToDesktop(
        /* [in] */ __RPC__in HWND topLevelWindow,
        /* [in] */ __RPC__in REFGUID desktopId) = 0;
};

class ReWin32Virt: public QObject
{
    Q_OBJECT
public:
    explicit ReWin32Virt(QObject *parent = nullptr);
    ~ReWin32Virt();

    void setDesktop(int id);
    void setFocus();
    int  current_workspace;

private slots:

private:
    void initInternal_Win10(IServiceProvider *service);
    void initInternal_Win11_21H2(IServiceProvider *service);

    QVector<GUID> vd_guids;
    IVirtualDesktopManagerInternal* manager_int;
    IVirtualDesktopManagerInternal_WIN11_21H2* manager_int_win11_21H2;
    int win_ver;
};

#endif // RE_WIN32_VIRT_H
