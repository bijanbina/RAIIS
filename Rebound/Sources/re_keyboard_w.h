#ifndef RE_KEYBOARD_W_H
#define RE_KEYBOARD_W_H

#include <stdio.h>
#include <Windows.h>

#define KEY_B         'B'
#define KEY_ESC       VK_ESCAPE
#define KEY_LEFT      VK_LEFT
#define KEY_RIGHT     VK_RIGHT
#define KEY_BACKSPACE VK_BACK

// VK_LWIN

class ReKeyboard
{
public:
    ReKeyboard();
    ~ReKeyboard();

    void sendKey(int key_val);
    void pressKey(int key_val);
    void releaseKey(int key_val);

private:
    int uinput_f;
};



#endif // RE_KEYBOARD_W_H
