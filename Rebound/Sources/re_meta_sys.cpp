#include "re_meta_sys.h"
#include "mm_api.h"
#ifdef WIN32
#include "re_keyboard_w.h"
#include "re_mouse.h"
#else
#include "re_keyboard_l.h"
#endif

MmApplication speech_app;

void re_getSysEnd()
{
#ifdef WIN32
    int win_found = 0;
    if( speech_app.hwnd==0 )
    {
        re_openSpeechNote();
        QThread::msleep(2000);
        win_found = mm_focus(&speech_app);
        QThread::msleep(2000);
    }
    else
    {
        ShowWindow(speech_app.hwnd, SW_NORMAL);
        win_found = mm_focus(&speech_app);
        QThread::msleep(100);

        // start new session
        SetCursorPos(50, 430);
        re_mouseKey(1);
        QThread::msleep(100);
    }

    if( win_found )
    {
        ReState::goToDictate();
        QThread::msleep(50);
        SetCursorPos(1450, 280);
        QThread::msleep(50);
        re_mouseKey(1);
    }
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

#ifdef WIN32
    speech_app = mm_launchLnk("Google Chrome", arg);
    speech_app.win_title = "Speechnotes";
#endif
}

void re_hideSpeechNote()
{
#ifdef WIN32
    qDebug() << "re_hideSpeechNote" << speech_app.hwnd;
    ShowWindow(speech_app.hwnd, SW_HIDE);
#endif
}
