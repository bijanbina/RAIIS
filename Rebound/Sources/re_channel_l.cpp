#include "re_channel_l.h"
#include <unistd.h>

ReChannelL::ReChannelL(ReCaptain *cpt, QObject *parent) : QObject(parent)
{
    pre = new RePreProcessor(cpt);
    ConnectDBus();
}

ReChannelL::~ReChannelL()
{
    ;
}

void ReChannelL::ConnectDBus()
{
    QDBusConnection session = QDBusConnection::sessionBus();

    if( !session.isConnected() )
    {
        qFatal("Cannot connect to the D-Bus session bus.");
        return;
    }

    session.connect("", "/", COM_NAME, "dirs" , pre, SLOT(dirs (const QString &)));
    session.connect("", "/", COM_NAME, "nato" , pre, SLOT(nato (const QString &)));
    session.connect("", "/", COM_NAME, "meta" , pre, SLOT(meta (const QString &)));
    session.connect("", "/", COM_NAME, "apps" , pre, SLOT(apps (const QString &)));
    session.connect("", "/", COM_NAME, "spex" , pre, SLOT(spex (const QString &)));
    session.connect("", "/", COM_NAME, "type" , pre, SLOT(type (const QString &)));
    session.connect("", "/", COM_NAME, "super", pre, SLOT(super(const QString &)));
    session.connect("", "/", COM_NAME, "digit", pre, SLOT(digit(const QString &)));
    session.connect("", "/", COM_NAME, "debug", pre, SLOT(debug(const QString &)));
    session.connect("", "/", COM_NAME, "modifier", pre, SLOT(modifier(const QString &)));
    session.connect("", "/", COM_NAME, "exec" , pre, SLOT(execTimeOut()));

    if( !session.registerService(COM_NAME) )
    {
        qFatal("Another session is on DBus.");
        // This cannot be automatic because killing assistant also kill
        // this instant too
        return;
    }
}
