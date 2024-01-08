#include "re_meta_sys.h"
#ifdef WIN32
#include "re_keyboard_w.h"
#include "mm_api.h"
#include "re_mouse.h"
#else
#include "re_keyboard_l.h"
#endif

MmApplication speech_app;

void re_getSysEnd()
{
#ifdef WIN32
    if( speech_app.hwnd==0 )
    {
        re_openSpeechNote();
        QThread::msleep(3000);
    }
    else
    {
        ShowWindow(speech_app.hwnd, SW_NORMAL);
        QThread::msleep(200);

        // start new session
        SetCursorPos(50, 430);
        re_mouseKey(1);
        QThread::msleep(100);
    }
    mm_focus(&speech_app);

    ReState::goToDictate();
    SetCursorPos(1450, 280);
    re_mouseKey(1);
#endif
}

void re_openSpeechNote()
{
    int x = 0;
    int y = 30;
    int w = 1920;
    int h = 1000;
    QString arg = "--app=\"data:text/html,<html><body><script>"
                  "window.moveTo(";
    QString url = "https://speechnotes.co/dictate/";
    arg += QString::number(x) + ",";
    arg += QString::number(y) + ");window.resizeTo(";
    arg += QString::number(w) + ",";
    arg += QString::number(h) + ");window.location='";
    arg += url + "';</script></body></html>\"";
    arg += " --enable-extensions";

    speech_app = mm_launchLnk("Google Chrome", arg);
    speech_app.win_title = "Speechnotes";
}

void re_hideSpeechNote()
{
    qDebug() << "re_hideSpeechNote" << speech_app.hwnd;
    ShowWindow(speech_app.hwnd, SW_HIDE);
}
