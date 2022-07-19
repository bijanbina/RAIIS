#include "re_keyboard_w.h"
#include <QDebug>

ReKeyboard::ReKeyboard()
{

}

ReKeyboard::~ReKeyboard()
{

}

void ReKeyboard::sendKey(int key_val)
{
    pressKey(key_val);
    releaseKey(key_val);
}

void ReKeyboard::pressKey(int key_val)
{
    INPUT input;
    ZeroMemory(&input, sizeof(input));

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key_val;

    SendInput(1, &input, sizeof(INPUT));
}

void ReKeyboard::releaseKey(int key_val)
{
    INPUT input;
    ZeroMemory(&input, sizeof(input));

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key_val;
    input.ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(1, &input, sizeof(INPUT));
}
