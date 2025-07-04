#ifndef RE_KEYBOARD_W_H
#define RE_KEYBOARD_W_H

#include <stdio.h>
#include <Windows.h>
#include <QVector>

#define KEY_0          '0'
#define KEY_1          '1'
#define KEY_2          '2'
#define KEY_3          '3'
#define KEY_4          '4'
#define KEY_5          '5'
#define KEY_6          '6'
#define KEY_7          '7'
#define KEY_8          '8'
#define KEY_9          '9'
#define KEY_A          'A'
#define KEY_B          'B'
#define KEY_C          'C'
#define KEY_D          'D'
#define KEY_E          'E'
#define KEY_F          'F'
#define KEY_G          'G'
#define KEY_H          'H'
#define KEY_I          'I'
#define KEY_K          'K'
#define KEY_L          'L'
#define KEY_M          'M'
#define KEY_N          'N'
#define KEY_O          'O'
#define KEY_P          'P'
#define KEY_Q          'Q'
#define KEY_R          'R'
#define KEY_S          'S'
#define KEY_T          'T'
#define KEY_V          'V'
#define KEY_W          'W'
#define KEY_U          'U'
#define KEY_X          'X'
#define KEY_Z          'Z'
#define KEY_ESC        VK_ESCAPE
#define KEY_UP         VK_UP
#define KEY_END        VK_END
#define KEY_HOME       VK_HOME
#define KEY_ENTER      VK_RETURN
#define KEY_LEFT       VK_LEFT
#define KEY_DOWN       VK_DOWN
#define KEY_RIGHT      VK_RIGHT
#define KEY_BACKSPACE  VK_BACK
#define KEY_LEFTALT    VK_MENU
#define KEY_LEFTCTRL   VK_CONTROL
#define KEY_LEFTSHIFT  VK_SHIFT
#define KEY_RIGHTSHIFT VK_RSHIFT
#define KEY_LEFTMETA   VK_LWIN
#define KEY_TAB        VK_TAB
#define KEY_PAGEUP     VK_PRIOR //Page Up
#define KEY_NEXT       VK_NEXT  //Page Down
#define KEY_APOSTROPHE VK_OEM_7 //'
#define KEY_MINUS      VK_SUBTRACT
#define KEY_KPPLUS     VK_ADD

#define KEY_F1         VK_F1
#define KEY_F2         VK_F2
#define KEY_F3         VK_F3
#define KEY_F4         VK_F4
#define KEY_F5         VK_F5
#define KEY_F6         VK_F6
#define KEY_F7         VK_F7
#define KEY_F8         VK_F8
#define KEY_F9         VK_F9
#define KEY_F10        VK_F10
#define KEY_F11        VK_F11
#define KEY_F12        VK_F12

#define RE_KEY_FMIN    VK_F1    //0x6f
#define RE_KEY_FMAX    VK_F12+1 //0x7C

class ReKeyboard
{
public:
    ReKeyboard();
    ~ReKeyboard();

    static void init();
    static void sendKey(int key_val);
    static void pressKey(int key_val);
    static void releaseKey(int key_val);
    static void type(QString text);

private:
    static bool isExtended(int key_val);

    static QVector<int> extended_keys;
};



#endif // RE_KEYBOARD_W_H
