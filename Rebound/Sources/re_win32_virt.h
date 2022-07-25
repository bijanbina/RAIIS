#ifndef RE_WIN32_VIRT_H
#define RE_WIN32_VIRT_H

#include "re_config.h"
#include <windows.h>
#include <objbase.h>
#include <ObjectArray.h>

const CLSID CLSID_ImmersiveShell = {
    0xC2F03A33, 0x21F5, 0x47FA, {0xB4, 0xBB, 0x15, 0x63, 0x62, 0xA2, 0xF2, 0x39} };

const CLSID CLSID_VirtualDesktopAPI_Unknown = {
    0xC5E0CDCA, 0x7B6E, 0x41B2, {0x9F, 0xC4, 0xD9, 0x39, 0x75, 0xCC, 0x46, 0x7B} };

const IID IID_IVirtualDesktopManagerInternal = {
    0xf31574d6,0xb682,0x4cdc,{0xbd,0x56,0x18,0x27,0x86,0x0a,0xbe,0xc6}};

const GUID UUID_IVirtualDesktop = {
    0xFF72FFDD, 0xBE7E, 0x43FC, {0x9C, 0x03, 0xAD, 0x81, 0x68, 0x1E, 0x88, 0xE4} };

// см. IApplicationView из Windows Runtime
struct IApplicationView : public IUnknown
{
public:

};

EXTERN_C const IID IID_IVirtualDesktop;

MIDL_INTERFACE("FF72FFDD-BE7E-43FC-9C03-AD81681E88E4")
IVirtualDesktop : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE IsViewVisible(
        IApplicationView *pView,
        int *pfVisible) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetID(
        GUID *pGuid) = 0;
};

enum AdjacentDesktop
{
    // Соседний рабочий стол слева
    LeftDirection = 3,
    // Соседний рабочий стол справа
    RightDirection = 4
};

MIDL_INTERFACE("AF8DA486-95BB-4460-B3B7-6E7A6B2962B5")
IVirtualDesktopManagerInternal : public IUnknown
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
        AdjacentDesktop uDirection,
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


class ReWin32Virt
{
public:
    explicit ReWin32Virt();
    ~ReWin32Virt();

    void setDesktop(int id);

private:
    IVirtualDesktopManagerInternal* pDesktopManager;

};

#endif // RE_WIN32_VIRT_H
