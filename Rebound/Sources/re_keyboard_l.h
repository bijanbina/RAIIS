#ifndef RE_KEYBOARD_L_H
#define RE_KEYBOARD_L_H

#include <stdio.h>
#include <linux/uinput.h>
#include "backend.h"

#define RE_KEY_FMIN    59 //F1
#define RE_KEY_FMAX    68 //F10

class ReKeyboard
{
public:
    ReKeyboard();
    ~ReKeyboard();

    static void init();
    static void sendKey(int key_val);
    static void pressKey(int key_val);
    static void releaseKey(int key_val);
    static void setKey(int type, int code, int val);
    static void type(QString text);

private:
    static int uinput_f;
};



#endif // RE_KEYBOARD_L_H
