#include "re_meta_sys.h"
#ifdef WIN32
#include "re_keyboard_w.h"
#include "mm_api.h"
#include "re_mouse.h"
#else
#include "re_keyboard_l.h"
#endif

void re_getSysEnd(ReState *st)
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

    mm_launchLnk("Google Chrome",
                 arg);
    QThread::msleep(3000);
    st->goToDictate();
    SetCursorPos(1450, 280);
    re_mouseKey(1);
}
