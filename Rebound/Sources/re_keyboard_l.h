#ifndef RE_KEYBOARD_L_H
#define RE_KEYBOARD_L_H

#include <stdio.h>
#include <linux/uinput.h>
#include "backend.h"

class ReKeyboard
{
public:
    ReKeyboard();
    ~ReKeyboard();

    void sendKey(int key_val);
    void pressKey(int key_val);
    void releaseKey(int key_val);
    void setKey(int type, int code, int val);

private:
    int uinput_f;
};



#endif // RE_KEYBOARD_L_H
