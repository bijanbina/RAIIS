#include "re_xbox_win32.h"

//HINSTANCE hGetProcIDDLL;
//FARPROC lpfnGetProcessID;

ReXboxWin32::ReXboxWin32(QObject *parent) : QObject(parent)
{
    guide_last_val = 0;
    HINSTANCE hXboxDll = LoadLibraryA("C:/Windows/System32/xinput1_3.dll");  //In Visual Studio replace this

    if(hXboxDll == NULL)
    {
//        qDebug() << "Could not load xinput1_3."
//                 << "Windows 10 detected trying xinput1_4.";

        hXboxDll = LoadLibraryA("C:/Windows/System32/xinput1_4.dll");

        if(hXboxDll == NULL)
        {
            qDebug() << "Could not load any xinput library";
            return;
        }
    }

//    FARPROC lpfnGetProcessID = GetProcAddress(HMODULE(hGetProcIDDLL), (LPCSTR)100);
//    getControllerData = pICFUNC(lpfnGetProcessID);

    XInputGetStateEx = (XInputGetStateExProc) GetProcAddress(HMODULE(hXboxDll), (LPCSTR) 100);
    XInputPowerOff = (XInputPowerOffProc) GetProcAddress(HMODULE(hXboxDll), (LPCSTR) 103);

    guideTimer = new QTimer;
    guideTimer->start(RE_CHECK_BTN);
    connect(guideTimer, SIGNAL(timeout()), this, SLOT(ReXbox_getGuideBtn()));
}

ReXboxWin32::~ReXboxWin32()
{
    ;
}

void ReXboxWin32::ReXbox_getGuideBtn()
{
    XINPUT_STATE state;
    DWORD res = XInputGetStateEx(0, &state);

    if( res==ERROR_DEVICE_NOT_CONNECTED )
    {
        return;
    }

    bool value = ((state.Gamepad.wButtons & XINPUT_GAMEPAD_GUIDE) != 0);
//    int value = buttons.guideButton;

    if (guide_last_val != value)
    {
        guide_last_val = value;
        qDebug() << guide_last_val;
        emit buttonGuideChanged(value);
    }
}
