#ifndef RE_KEYBOARD_H
#define RE_KEYBOARD_H

#include <stdio.h>
#include <linux/uinput.h>

#include "backend.h"
#include "re_meta_l.h"
#include "re_super_l.h"
#include "re_qt.h"

class ReKeyboardL
{
public:
    ReKeyboardL();
    ~ReKeyboardL();

    void sendKey(int key_val);
    void pressKey(int key_val);
    void releaseKey(int key_val);
    void handleScroll(CCommand command);

    void execModifier(CCommand command);
    void releaseModifiers();
    void setKey(int type, int code, int val);

private:
    int uinput_f;
};



#endif // RE_KEYBOARD_H
