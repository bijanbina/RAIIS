#include "re_bisper.h"
#include "mm_api.h"
#ifdef WIN32
#include "re_console.h"
#include "re_keyboard_w.h"
#include "re_mouse.h"
#else
#include "re_keyboard_l.h"
#endif

MmApplication  speech_app;
#ifdef WIN32
ReConsole     *console = NULL;
#endif

void re_execSpeech()
{
#ifdef WIN32
    if( console==NULL )
    {
        console = new ReConsole;
    }
    console->startConsole("..\\..\\Bisper\\");
    qDebug() << "We are here in bisper";
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
    console->stopApp();
#endif
}
