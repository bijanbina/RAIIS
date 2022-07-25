#include "re_super_l.h"

ReSuper::ReSuper(ReState *st, QObject *parent): QObject(parent)
{
    state = st;
    virt = new ReWin32Virt;
}

ReSuper::~ReSuper()
{
    ;
}

void ReSuper::castCmd(int cmd, CCommand *ret)
{
    if( cmd==RE_SUPER_META )
    {
        getMetaCmd(ret);
    }
    else if( cmd==RE_SUPER_CAMEL )
    {
        qDebug() << "CreateProcess 1";
#ifdef WIN32
#else
        system("./Scripts/camel");
#endif
    }
    else if( cmd==RE_SUPER_SWITCH )
    {
        getSwitchCmd(ret);
    }
    else if( cmd==RE_SUPER_KICK )
    {
        getKickCmd();
    }
    else if( cmd==RE_SUPER_COMMENT )
    {
        system("xdotool key --delay 200 ctrl+slash");
    }
    else if( cmd==RE_SUPER_COPY )
    {
        getCopyCmd(ret);
    }
    else if( cmd==RE_SUPER_PASTE )
    {
        getPasteCmd(ret);
    }
    else if( cmd==RE_SUPER_SIDE )
    {
        getSideCmd();
    }
    else if( cmd==RE_SUPER_LOVE )
    {
        getLoveCmd(ret);
    }
    else if( cmd==RE_SUPER_ROGER )
    {
        getRogerCmd(ret);
    }
}

void ReSuper::getMetaCmd(CCommand *ret)
{
    ret->val2 = 1;
    ret->val3 = 1;
    ret->type = RE_COMMAND_SUPER;

    qDebug() << "Meta" << state->app.pname;
    virt->setDesktop(2);

//    if( state->app.pname==RE_PROC_CHESS )
//    {
//        cmd = "xdotool key F1";
//    }
//    else if( state->app.pname==RE_PROC_QT )
//    {
//        cmd = "xdotool key F1";
//    }
//    else if( state->app.pname==RE_PROC_VSCODE )
//    {
//        cmd = "xdotool key F5";
//    }
//    else if( state->app.pname==RE_PROC_GIT )
//    {
////        cmd = re_getGoGitKraken(val);
//    }
//    else if( state->app.pname==RE_PROC_FIREFOX ||
//             state->app.pname==RE_PROC_GEKO )
//    {
//        cmd = "xdotool key ctrl+w";
//    }
//    else if( state->app.pname==RE_PROC_EXPLORER )
//    {
//        cmd = "xdotool key ctrl+w";
//    }
//    else if( state->app.pname==RE_PROC_TELEGRAM )
//    {
//        system("./Scripts/telegram_voice.sh");
//    }
}

void ReSuper::getCopyCmd(CCommand *ret)
{
    ret->val2 = 1;
    ret->val3 = 1;
    ret->type  = RE_COMMAND_MOD;
    ret->state = RE_CSTATE_0;

    ret->mod_list.append(KEY_CTRL);
    ret->val1 = KEY_C;
}

void ReSuper::getPasteCmd(CCommand *ret)
{
    ret->val2 = 1;
    ret->val3 = 1;
    ret->type  = RE_COMMAND_MOD;
    ret->state = RE_CSTATE_0;

    ret->mod_list.append(KEY_CTRL);
    ret->val1 = KEY_V;
}

void ReSuper::getKickCmd()
{
#ifdef WIN32
        system("dbus-send --dest=com.benjamin.chess"
               " / com.benjamin.chess.show string:\"\"");
#else

#endif
}

void ReSuper::getSideCmd()
{
#ifdef WIN32
    system("dbus-send --dest=com.benjamin.chess"
           " / com.benjamin.chess.show string:\"side\"");
#else

#endif
}

void ReSuper::getLoveCmd(CCommand *ret)
{
    ret->val2 = 1;
    ret->val3 = 1;
    ret->type  = RE_COMMAND_MOD;
    ret->state = RE_CSTATE_0;

    ret->mod_list.append(KEY_CTRL);
    ret->val1 = KEY_LEFT;
}

void ReSuper::getRogerCmd(CCommand *ret)
{
    ret->val2 = 1;
    ret->val3 = 1;
    ret->type  = RE_COMMAND_MOD;
    ret->state = RE_CSTATE_0;

    ret->mod_list.append(KEY_CTRL);
    ret->val1 = KEY_RIGHT;
}

void ReSuper::getSwitchCmd(CCommand *ret)
{
    ret->val2 = 1;
    ret->val3 = 1;
    ret->type  = RE_COMMAND_MOD;
    ret->state = RE_CSTATE_0;

    ret->mod_list.append(KEY_META);
    ret->val1 = KEY_B;
}
