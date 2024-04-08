#include "re_keyboard_w.h"
#include <QDebug>
#include <QThread>

QVector<int> ReKeyboard::extended_keys  = QVector<int>();

ReKeyboard::ReKeyboard()
{

}

ReKeyboard::~ReKeyboard()
{

}

void ReKeyboard::init()
{
    extended_keys << VK_INSERT;
    extended_keys << VK_DELETE;
    extended_keys << VK_HOME;
    extended_keys << VK_END;
    extended_keys << VK_PRIOR;
    extended_keys << VK_NEXT;
    extended_keys << VK_LEFT;
    extended_keys << VK_UP;
    extended_keys << VK_DOWN;
    extended_keys << VK_RIGHT;
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
    if( isExtended(key_val) )
    {
        input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
    }

    SendInput(1, &input, sizeof(INPUT));
}

void ReKeyboard::releaseKey(int key_val)
{
    INPUT input;
    ZeroMemory(&input, sizeof(input));

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key_val;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    if( isExtended(key_val) )
    {
        input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
    }

    SendInput(1, &input, sizeof(INPUT));
}

bool ReKeyboard::isExtended(int key_val)
{
    if( extended_keys.contains(key_val) )
    {
        return true;
    }
    return false;
}

void ReKeyboard::type(QString text)
{
#ifdef WIN32
    int len = text.length() + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), text.toStdString().c_str(), len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
    QThread::msleep(50);

    // paste
    ReKeyboard::pressKey(KEY_LEFTCTRL);
    ReKeyboard::sendKey(KEY_V);
    ReKeyboard::releaseKey(KEY_LEFTCTRL);
#else
    QString cmd = "xdotool type '";
    cmd += text + "'";
    system(cmd.toStdString().c_str());
#endif
}
