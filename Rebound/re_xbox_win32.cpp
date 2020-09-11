#include "re_xbox_win32.h"

//HINSTANCE hGetProcIDDLL;
//FARPROC lpfnGetProcessID;

ReXboxWin32::ReXboxWin32(QObject *parent) : QObject(parent)
{
    guide_last_val = 0;
    //First create an HINSTANCE of the xinput1_3.dll.  Probably should use system variables to find it
    //but whatever.
    HINSTANCE hGetProcIDDLL = LoadLibraryA("C:/Windows/System32/xinput1_3.dll");  //In Visual Studio replace this
    //HINSTANCE hGetProcIDDLL = LoadLibrary(L"C:/Windows/System32/xinput1_3.dll");  //With this

    //Get the address of ordinal 100.
    FARPROC lpfnGetProcessID = GetProcAddress(HMODULE(hGetProcIDDLL), (LPCSTR)100);
    getControllerData = pICFUNC(lpfnGetProcessID);

    guideTimer = new QTimer;
    guideTimer->start(RE_CHECK_BTN);
    connect(guideTimer, SIGNAL(timeout()), this, SLOT(ReXbox_getGuideBtn()));
}

ReXboxWin32::~ReXboxWin32()
{
    ;
}

int ReXboxWin32::ReXbox_getGuideBtn()
{
    ReXboxController buttons;
    getControllerData(0, buttons);  //call the function with the controller number(zero based) and
                    //the pointer to the ControllerStruct.

    int value = buttons.guideButton;
    if (guide_last_val != value)
    {
        guide_last_val = value;
        emit buttonGuideChanged(value);
    }
}
