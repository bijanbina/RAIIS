#include "re_api_l.h"
#include <stdio.h>
#include <unistd.h>

ReApiL::ReApiL(QObject *parent) : QObject(parent)
{

}

long ReApiL::getPid()
{
    // get allegro pid of window handle
    return 0;
}

QString ReApiL::getPNameA()
{
    QString app_name;

    return app_name;
}

QString ReApiL::getPName(long pid)
{
    return QString("pname");
}

QString ReApiL::getElemName(int index)
{
    return "";
}

QString ReApiL::getWinTitle(int index)
{
    return "";
}

QString ReApiL::getAccName(long childId)
{
    return QString("accName");
}

void ReApiL::setActiveWindow(Window win)
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

void ReApiL::setDisplay(Display *display)
{
    disp = display;
}

void ResolveIt(char *target)
{

}

QString ReApiL::getLinkPath(QString path)
{
    QString lnk;

    return lnk;
}

void lunnchExe(QString name)
{

}

void ReApiL::openApp(int appid)
{
    QString link_path;

    if ( appid==RE_WIN_TELEGRAM )
    {
        link_path = getLinkPath("Telegram Desktop\\Telegram.lnk");
//        lunnchExe(link_path);
    }
}
