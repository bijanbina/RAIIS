#include "re_xbox_win32.h"

//HINSTANCE hGetProcIDDLL;
//FARPROC lpfnGetProcessID;

ReXboxWin32::ReXboxWin32(QObject *parent) : QObject(parent)
{
    guide_last_val = 0;
    HINSTANCE hGetProcIDDLL = LoadLibraryA("C:/Windows/System32/xinput1_3.dll");  //In Visual Studio replace this

    if(hGetProcIDDLL == NULL)
    {
        qDebug() << "Could not load xinput1_3. Windows 10 detected trying xinput1_4.";

        hGetProcIDDLL = LoadLibraryA("C:/Windows/System32/xinput1_4.dll");

        if(hGetProcIDDLL == NULL)
        {
            qDebug() << "Could not load any xinput library";
            return;
        }
    }

//    FARPROC lpfnGetProcessID = GetProcAddress(HMODULE(hGetProcIDDLL), (LPCSTR)100);
//    getControllerData = pICFUNC(lpfnGetProcessID);

    XInputGetStateEx = (XInputGetStateExProc) GetProcAddress(HMODULE(hGetProcIDDLL), (LPCSTR) 100);

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
//    ReXboxController buttons;
//    getControllerData(0, buttons); //call the function with the controller number(zero based) and
//                                   //the pointer to the ControllerStruct.

//    int value = buttons.guideButton;
//    if (guide_last_val != value)
//    {
//        guide_last_val = value;
//        qDebug() << guide_last_val;
//        emit buttonGuideChanged(value);
//    }
    XINPUT_STATE state;
    XInputGetStateEx(0, &state);
    bool value = ((state.Gamepad.wButtons & XINPUT_GAMEPAD_GUIDE) != 0);
//    int value = buttons.guideButton;

    if (guide_last_val != value)
    {
        guide_last_val = value;
        emit buttonGuideChanged(value);
    }

}
