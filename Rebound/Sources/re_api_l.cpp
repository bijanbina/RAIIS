#include "re_api_l.h"
#include <stdio.h>
#include <unistd.h>

ReApi::ReApi(QObject *parent) : QObject(parent)
{

}

long ReApi::getPid()
{
    // get allegro pid of window handle
    return 0;
}

QString ReApi::getPNameA()
{
    QString app_name;

    return app_name;
}

QString ReApi::getPName(long pid)
{
    return QString("pname");
}

QString ReApi::getElemName(int index)
{
    return "";
}

QString ReApi::getWinTitle(int index)
{
    return "";
}

QString ReApi::getAccName(long childId)
{
    return QString("accName");
}

void ReApi::setActiveWindow(Window win)
{
    XEvent event;
    long mask = SubstructureRedirectMask | SubstructureNotifyMask;

    event.xclient.type = ClientMessage;
    event.xclient.serial = 0;
    event.xclient.send_event = True;
    event.xclient.message_type = XInternAtom(disp, "_NET_ACTIVE_WINDOW", False);
    event.xclient.window = win;
    event.xclient.format = 32;
    event.xclient.data.l[0] = 0;
    event.xclient.data.l[1] = 0;
    event.xclient.data.l[2] = 0;
    event.xclient.data.l[3] = 0;
    event.xclient.data.l[4] = 0;

    XSendEvent(disp, DefaultRootWindow(disp), False, mask, &event);

    XMapRaised(disp, win);
}

void ReApi::setDisplay(Display *display)
{
    disp = display;
}

void ResolveIt(char *target)
{

}

QString ReApi::getLinkPath(QString path)
{
    QString lnk;

    return lnk;
}

void lunchExe(QString name)
{

}

void ReApi::openApp(int appid)
{
    QString link_path;

    if ( appid==RE_WIN_TELEGRAM )
    {
        link_path = getLinkPath("Telegram Desktop\\Telegram.lnk");
//        lunchExe(link_path);
    }
}
