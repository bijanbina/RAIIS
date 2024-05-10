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
        console->startConsole("..\\..\\Bisper\\");
    }
    else
    {

    }
    qDebug() << "We are here in bisper";
#endif
}

void re_hideSpeechNote()
{
#ifdef WIN32
    qDebug() << "re_hideSpeechNote" << speech_app.hwnd;
    console->stopApp();
//    delete console;
    console = NULL;
#endif
}
