#ifndef RE_KEYBOARD_W_H
#define RE_KEYBOARD_W_H

#include <stdio.h>
#include <Windows.h>
#include <QVector>

#define KEY_1         '1'
#define KEY_2         '2'
#define KEY_3         '3'
#define KEY_4         '4'
#define KEY_5         '5'
#define KEY_6         '6'
#define KEY_7         '7'
#define KEY_8         '8'
#define KEY_9         '9'
#define KEY_A         'A'
#define KEY_B         'B'
#define KEY_C         'C'
#define KEY_D         'D'
#define KEY_E         'E'
#define KEY_F         'F'
#define KEY_M         'M'
#define KEY_N         'N'
#define KEY_P         'P'
#define KEY_R         'R'
#define KEY_T         'T'
#define KEY_V         'V'
#define KEY_ESC       VK_ESCAPE
#define KEY_UP        VK_UP
#define KEY_ENTER     VK_RETURN
#define KEY_LEFT      VK_LEFT
#define KEY_DOWN      VK_DOWN
#define KEY_RIGHT     VK_RIGHT
#define KEY_BACKSPACE VK_BACK

class ReKeyboard
{
public:
    ReKeyboard();
    ~ReKeyboard();

    void sendKey(int key_val);
    void pressKey(int key_val);
    void releaseKey(int key_val);

private:
    bool isExtended(int key_val);

    QVector<int> extended_keys;
    int uinput_f;
};



#endif // RE_KEYBOARD_W_H
