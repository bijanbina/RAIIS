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

void ReApiL::setActiveWindow(long hWnd)
{
    ;
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

    if ( appid==RE_PROC_TELEGRAM )
    {
        link_path = getLinkPath("Telegram Desktop\\Telegram.lnk");
//        lunnchExe(link_path);
    }
}
