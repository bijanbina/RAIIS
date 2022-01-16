#include "re_channel_l.h"
#include <unistd.h>

ReChannelL::ReChannelL(ReCaptainL *cpt, QObject *ui, QObject *parent) : QObject(parent)
{
    ConnectDBus();
    root = ui;
    captain = cpt;
    special_c = 0;
    system("rm ~/.config/polybar/awesomewm/ben_spex");
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

    session.connect("", "/", COM_NAME, "dirs" , this, SLOT(dirs (const QString &)));
    session.connect("", "/", COM_NAME, "nato" , this, SLOT(nato (const QString &)));
    session.connect("", "/", COM_NAME, "meta" , this, SLOT(meta (const QString &)));
    session.connect("", "/", COM_NAME, "apps" , this, SLOT(apps (const QString &)));
    session.connect("", "/", COM_NAME, "spex" , this, SLOT(spex (const QString &)));
    session.connect("", "/", COM_NAME, "digit", this, SLOT(digit(const QString &)));
    session.connect("", "/", COM_NAME, "debug", this, SLOT(debug(const QString &)));
    session.connect("", "/", COM_NAME, "modifier", this, SLOT(modifier(const QString &)));
    session.connect("", "/", COM_NAME, "exec" , this, SLOT(execTimeOut()));

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
        qDebug() << QTime::currentTime().toString("mm:ss:zzz") <<
                    "exec" << commands_str << special_c;
        commands_str.clear();

        captain->execute(cmd_buf);
        cmd_buf.clear();
    }
}

void ReChannelL::execTimeOut()
{
    if( cmd_buf.length() )
    {
        qDebug() << QTime::currentTime().toString("mm:ss:zzz") << "Request Immediate Execution";
        execute();
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
            execute();
            return;
        }
    }

    CaptainCommand cmd;

    cmd.val1 = text.toInt();
    cmd.val2 = 0;
    cmd.type = RE_COMMAND_NATO;

    cmd_buf.append(cmd);
    if( special_c==0 )
    {
        execute();
    }
}

void ReChannelL::digit(const QString &text)
{
    if( captain->isLastCmdRepeatable(cmd_buf) && (special_c>0) )
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
        }
        special_c--;

        qDebug() << "digit" << cmd_buf[last_i].val2 << special_c;
        if( special_c==0 )
        {
            system("rm ~/.config/polybar/awesomewm/ben_spex");
            execute();
        }

    }
    else if( captain->isLastMeta(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index

        if( cmd_buf[last_i].val2==0 )
        {
            cmd_buf[last_i].val2 = captain->keyCode2Digit(text);
        }
        else if( cmd_buf[last_i].val3==0 )
        {
            cmd_buf[last_i].val3 = captain->keyCode2Digit(text);
        }
        else
        {
            cmd_buf[last_i].val3  = cmd_buf[last_i].val3*10;
            cmd_buf[last_i].val3 += captain->keyCode2Digit(text);
            qDebug() << cmd_buf[last_i].val3;
            execute();
        }

        if( special_c==0 )
        {
            execute();
        }
    }
    else if( captain->state->scroll_mode )
    {
        CaptainCommand cmd;
        cmd.val1 = captain->state->scroll_dir;
        cmd.val2 = captain->keyCode2Digit(text);
        cmd.type = RE_COMMAND_META;

        cmd_buf.append(cmd);

        if( special_c==0 )
        {
            execute();
        }
    }
    else
    {
        CaptainCommand cmd;
        cmd.val1 = text.toInt();
        cmd.val2 = 1;
        cmd.type = RE_COMMAND_DIGIT;

        cmd_buf.append(cmd);

        if( special_c==0 )
        {
            execute();
        }
    }
}

// direction keys
void ReChannelL::dirs(const QString &text) //speex
{
    if( captain->isLastMeta(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index

        if ( cmd_buf[last_i].val2==0 )
        {
            cmd_buf[last_i].val2 = text.toInt();
            execute();
            return;
        }
    }

    CaptainCommand cmd;
    cmd.val1 = text.toInt();
    cmd.val2 = 0; //press count
    cmd.type = RE_COMMAND_DIRS;

    cmd_buf.append(cmd);
    if( special_c==0 )
    {
        execute();
    }
}

void ReChannelL::modifier(const QString &text)
{
    CaptainCommand cmd;
    cmd.val1 = text.toInt();
    cmd.val2 = 1;
    cmd.type = RE_COMMAND_MOD;

    cmd_buf.append(cmd);

    execute();
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
            execute();
            return;
        }
    }
}

void ReChannelL::spex(const QString &text)
{
    special_c++;
    qDebug() << "special_c" << special_c;
    QString cmd = "echo ";
    cmd += QString::number(special_c);
    cmd += " > ~/.config/polybar/awesomewm/ben_spex";
    system(cmd.toStdString().c_str());
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
