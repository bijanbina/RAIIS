#ifndef RE_XBOX_WIN32_H
#define RE_XBOX_WIN32_H

#include <windows.h>
#include <iostream>

struct ReXboxController
{
    unsigned long eventCount; //event counter, increases with every controller event,
                  //but for some reason not by one.
    unsigned short up:1, down:1, left:1, right:1, start:1, back:1, l3:1, r3:1,
                   lButton:1, rButton:1, guideButton:1, unknown:1, aButton:1,
                   bButton:1, xButton:1, yButton:1; // button state bitfield
    unsigned char lTrigger;  //Left Trigger
    unsigned char rTrigger;  //Right Trigger
    short lJoyY;  //Left Joystick Y
    short lJoyx;  //Left Joystick X
    short rJoyY;  //Right Joystick Y
    short rJoyX;  //Right Joystick X
};

void ReXbox_init();
int ReXbox_getGuideBtn();

#endif // RE_XBOX_WIN32_H
