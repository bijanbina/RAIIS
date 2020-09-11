#include "re_xbox_win32.h"

//HINSTANCE hGetProcIDDLL;
//FARPROC lpfnGetProcessID;
typedef int(__stdcall * pICFUNC)(int, ReXboxController &);
pICFUNC getControllerData;

void ReXbox_init()
{

    //First create an HINSTANCE of the xinput1_3.dll.  Probably should use system variables to find it
    //but whatever.
    HINSTANCE hGetProcIDDLL = LoadLibraryA("C:/Windows/System32/xinput1_3.dll");  //In Visual Studio replace this
    //HINSTANCE hGetProcIDDLL = LoadLibrary(L"C:/Windows/System32/xinput1_3.dll");  //With this

    //Get the address of ordinal 100.
    FARPROC lpfnGetProcessID = GetProcAddress(HMODULE(hGetProcIDDLL), (LPCSTR)100);
    getControllerData = pICFUNC(lpfnGetProcessID);
}

int ReXbox_getGuideBtn()
{
    ReXboxController buttons;
    getControllerData(0, buttons);  //call the function with the controller number(zero based) and
                    //the pointer to the ControllerStruct.
    return buttons.guideButton;  //simply access the variable like normal.  Easy peasy.
}
