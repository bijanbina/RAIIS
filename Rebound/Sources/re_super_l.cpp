#include "re_super_l.h"

ReSuperL::ReSuperL(ReState *st, QObject *parent): QObject(parent)
{
    state = st;
}

ReSuperL::~ReSuperL()
{
    ;
}

void ReSuperL::exec(CCommand command)
{
    if( command.val1==RE_SUPER_META )
    {
        QString cmd = getMetaCmd();
        system(cmd.toStdString().c_str());
    }
    else if( command.val1==RE_SUPER_CAMEL )
    {
        qDebug() << "CreateProcess 1";
        system("./Scripts/camel");
        qDebug() << "CreateProcess 2";
    }
    else if( command.val1==RE_SUPER_SWITCH )
    {
        system("xdotool key --delay 200 super+b");
    }
    else if( command.val1==RE_SUPER_KICK )
    {
#ifdef WIN32
        system("dbus-send --dest=com.benjamin.chess"
               " / com.benjamin.chess.show string:\"\"");
#else

#endif
    }
    else if( command.val1==RE_SUPER_COMMENT )
    {
        system("xdotool key --delay 200 ctrl+slash");
    }
    else if( command.val1==RE_SUPER_COPY )
    {
        system("xdotool key --delay 200 ctrl+c");
    }
    else if( command.val1==RE_SUPER_PASTE )
    {
        system("xdotool key --delay 200 ctrl+v");
    }
    else if( command.val1==RE_SUPER_SIDE )
    {
        system("dbus-send --dest=com.benjamin.chess"
               " / com.benjamin.chess.show string:\"side\"");
    }
    else if( command.val1==RE_SUPER_LOVE )
    {
        system("xdotool key --delay 40 ctrl+Left");
    }
    else if( command.val1==RE_SUPER_ROGER )
    {
        system("xdotool key --delay 40 ctrl+Right");
    }
}

QString ReSuperL::getMetaCmd()
{
    QString cmd;

    qDebug() << "Meta" << state->app.pname;

    if( state->app.pname=="Chess" )
    {
        cmd = "xdotool key F1";
    }
    else if( state->app.pname=="qtcreator" )
    {
        cmd = "xdotool key F1";
    }
    else if( state->app.pname=="code-oss" )
    {
        cmd = "xdotool key F5";
    }
    else if( state->app.pname=="gitkraken" )
    {
//        cmd = re_getGoGitKraken(val);
    }
    else if( state->app.pname=="GeckoMain" ||
             state->app.pname=="firefox" )
    {
        cmd = "xdotool key ctrl+w";
    }
    else if( state->app.pname=="nautilus" )
    {
        cmd = "xdotool key ctrl+w";
    }
    else if( state->app.pname=="Telegram" )
    {
        cmd = "./Scripts/telegram_voice.sh";
    }

    return cmd;
}
