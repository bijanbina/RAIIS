#include "re_super.h"

ReSuper::ReSuper(ReState *st, QObject *parent): QObject(parent)
{
    state = st;
    virt = new ReWin32Virt;

    connectChessPipe();
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
        getCamelCmd();
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
    sendPipe("show" CH_NP_SEPARATOR);
#else
    system("dbus-send --dest=com.benjamin.chess"
           " / com.benjamin.chess.show string:\"\"");
#endif
}

void ReSuper::getSideCmd()
{
#ifdef WIN32
#else
    system("dbus-send --dest=com.benjamin.chess"
           " / com.benjamin.chess.show string:\"side\"");
#endif
}

void ReSuper::getCamelCmd()
{
    qDebug() << "CreateProcess 1";
#ifdef WIN32
#else
    system("./Scripts/camel");
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

void ReSuper::connectChessPipe()
{
    // 0: Default Wait Time
    int np_is_available = WaitNamedPipeA(CH_PIPE_PATH, 0);
    if( np_is_available )
    {
        hPipe = CreateFileA(CH_PIPE_PATH, GENERIC_WRITE, // dwDesiredAccess
                            0, nullptr,    // lpSecurityAttributes
                            OPEN_EXISTING,  // dwCreationDisposition
                            0, nullptr);    // hTemplateFile

        if( hPipe==INVALID_HANDLE_VALUE )
        {
            qDebug() << "Error 120: Cannot create " CH_PIPE_PATH;
        }
    }
    else
    {
        hPipe = INVALID_HANDLE_VALUE;
        qDebug() << "Error 121: Pipe " CH_PIPE_PATH
                    " not found";
    }
}

void ReSuper::sendPipe(const char *data)
{
    DWORD len = strlen(data);
    if( hPipe==INVALID_HANDLE_VALUE )
    {
        qDebug() << "Try to reconnect to"
                 << CH_PIPE_PATH;

        connectChessPipe();
        if( hPipe==INVALID_HANDLE_VALUE )
        {
            return;
        }
    }

    DWORD dwWritten;
    int success = WriteFile(hPipe, data, len, &dwWritten, NULL);
    if( !success )
    {
        qDebug() << "Error: NamedPipe writing failed," << GetLastError();
    }

    if( dwWritten!=len )
    {
        qDebug() << "Error: Wrong writing length."
                    "Try to revive channel";
        CloseHandle(hPipe);
        hPipe = INVALID_HANDLE_VALUE;
        sendPipe(data);
    }
}
