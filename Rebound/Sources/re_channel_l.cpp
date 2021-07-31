#include "re_channel_l.h"
#include <unistd.h>

ReChannelL::ReChannelL(ReCaptainL *cpt, QObject *ui, QObject *parent) : QObject(parent)
{
    ConnectDBus();
    root = ui;
    captain = cpt;
}

ReChannelL::~ReChannelL()
{
    ;
}

void ReChannelL::ConnectDBus()
{
    QDBusConnection session = QDBusConnection::sessionBus();

    if (!session.isConnected())
    {
        qFatal("Cannot connect to the D-Bus session bus.");
        return;
    }

    session.connect("", "/", COM_NAME, "speex", this, SLOT(speex(const QString &)));
    session.connect("", "/", COM_NAME, "nato" , this, SLOT(nato (const QString &)));
    session.connect("", "/", COM_NAME, "meta" , this, SLOT(meta (const QString &)));
    session.connect("", "/", COM_NAME, "apps" , this, SLOT(apps (const QString &)));
    session.connect("", "/", COM_NAME, "digit", this, SLOT(digit(const QString &)));
    session.connect("", "/", COM_NAME, "debug", this, SLOT(debug(const QString &)));
    session.connect("", "/", COM_NAME, "modifier", this, SLOT(modifier(const QString &)));
    session.connect("", "/", COM_NAME, "exec"  , this, SLOT(execute()));

    /*if(!session.registerObject("/", this, QDBusConnection::ExportScriptableContents)) {
        qFatal("Another session is on DBus.");
        return;
    }*/

    if(!session.registerService(COM_NAME))
    {
        qFatal("Another session is on DBus.");
        // This cannot be automatic because killing assistant also kill
        // this instant too
        return;
    }
}

void ReChannelL::execute()
{
    if( cmd_buf.length() )
    {
        qDebug() << commands_str;
        commands_str.clear();

        captain->execute(cmd_buf);
        cmd_buf.clear();
    }
}

void ReChannelL::nato(const QString &text)
{
    if( captain->isLastMeta(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index

        if ( cmd_buf[last_i].val2==0 )
        {
            cmd_buf[last_i].val2 = text.toInt();
            return;
        }
    }

    CaptainCommand cmd;

    cmd.val1 = text.toInt();
    cmd.val2 = 1;
    cmd.type = RE_COMMAND_NATO;

    cmd_buf.append(cmd);
}

void ReChannelL::digit(const QString &text)
{
    if( captain->isLastCmdRepeatable(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index

        if ( cmd_buf[last_i].val2==0 )
        {
            cmd_buf[last_i].val2 = captain->keyCode2Digit(text);
        }
        else
        {
            cmd_buf[last_i].val2  = cmd_buf[last_i].val2*10;
            cmd_buf[last_i].val2 += captain->keyCode2Digit(text);
            qDebug() << cmd_buf[last_i].val2;
        }
    }
    else if( captain->isLastMeta(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index

        if ( cmd_buf[last_i].val2==0 )
        {
            cmd_buf[last_i].val2 = captain->keyCode2Digit(text);
        }
        else if ( cmd_buf[last_i].val3==0 )
        {
            cmd_buf[last_i].val3 = captain->keyCode2Digit(text);
        }
        else
        {
            cmd_buf[last_i].val3  = cmd_buf[last_i].val3*10;
            cmd_buf[last_i].val3 += captain->keyCode2Digit(text);
            qDebug() << cmd_buf[last_i].val3;
        }
    }
    else
    {
        CaptainCommand cmd;
        cmd.val1 = text.toInt();
        cmd.val2 = 1;
        cmd.type = RE_COMMAND_DIGIT;

        cmd_buf.append(cmd);
    }
}

void ReChannelL::speex(const QString &text)
{
    if( captain->isLastMeta(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index

        if ( cmd_buf[last_i].val2==0 )
        {
            cmd_buf[last_i].val2 = text.toInt();
            return;
        }
    }

    CaptainCommand cmd;
    cmd.val1 = text.toInt();
    cmd.val2 = 0;
    cmd.type = RE_COMMAND_KEY;

    cmd_buf.append(cmd);
}

void ReChannelL::modifier(const QString &text)
{
    CaptainCommand cmd;
    cmd.val1 = text.toInt();
    cmd.val2 = 1;
    cmd.type = RE_COMMAND_MOD;

    cmd_buf.append(cmd);
}

void ReChannelL::meta(const QString &text)
{
    if( captain->isLastMeta(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index

        if ( cmd_buf[last_i].val2==0 )
        {
            if( text.toInt()==RE_META_CLOSE )
            {
                cmd_buf[last_i].val2 = KEY_CLOSE;
                return;
            }
        }
    }

    CaptainCommand cmd;
    cmd.val1 = text.toInt();
    cmd.val2 = 0;
    cmd.val3 = 0;
    cmd.type = RE_COMMAND_META;

    cmd_buf.append(cmd);
}

void ReChannelL::apps(const QString &text)
{
    if( captain->isLastMeta(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index

        if ( cmd_buf[last_i].val2==0 )
        {
            cmd_buf[last_i].val2 = 300 + text.toInt();
            return;
        }
    }
}

void ReChannelL::debug(const QString &text)
{
    if( commands_str.length() )
    {
        commands_str += " ";
    }
    commands_str += text;
}

void ReChannelL::startServer()
{

}
