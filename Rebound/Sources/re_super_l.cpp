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
        QString cmd;
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
}

QString ReSuperL::getGoCmd(int val)
{
    QString cmd;

    qDebug() << "GO" << state->app.pname;

    if( state->app.pname=="xed" )
    {
    }
    else if( state->app.pname=="qtcreator" ||
             state->app.pname=="code-oss" )
    {
//        cmd = re_getGoQt(val);
    }
    else if( state->app.pname=="gitkraken" )
    {
//        cmd = re_getGoGitKraken(val);
    }
    else if( state->app.pname=="GeckoMain" ||
             state->app.pname=="firefox" )
    {
//        cmd = re_getGoFirefox(val);
    }
    else if( state->app.pname=="nautilus" )
    {
//        cmd = re_getGoNautilus(val);
    }

    return cmd;
}
