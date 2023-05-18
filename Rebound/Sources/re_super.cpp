#include "re_super.h"
#include <QThread>

ReSuper::ReSuper(ReState *st, QObject *parent): QObject(parent)
{
    state = st;

#ifdef WIN32
    virt = new ReWin32Virt;
    connectChessPipe();
#endif
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
        getCamelCmd(ret);
    }
    else if( cmd==RE_SUPER_SWITCH )
    {
        getSwitchCmd(ret);
    }
    else if( cmd==RE_SUPER_SPOTIFY )
    {
        getLSwitchCmd(ret);
    }
    else if( cmd==RE_SUPER_KICK )
    {
        getChessCmd(ret, "show");
    }
    else if( cmd==RE_SUPER_COMMENT )
    {
        getCommentCmd(ret);
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
        getChessCmd(ret, "side");
    }
    else if( cmd==RE_SUPER_DOUBLE )
    {
        getChessCmd(ret, "double");
    }
    else if( cmd==RE_SUPER_SELECT )
    {
        getSelectCmd(ret);
    }
    else if( cmd==RE_SUPER_LOVE )
    {
        getLoveCmd(ret);
    }
    else if( cmd==RE_SUPER_ROGER )
    {
        getRogerCmd(ret);
    }
    else if( cmd==RE_SUPER_RESIST )
    {
        getChessCmd(ret, "persist");
    }
    else if( cmd==RE_SUPER_DRAG )
    {
        getChessCmd(ret, "drag");
    }
}

void ReSuper::getMetaCmd(CCommand *ret)
{
    ret->val2 = 1;
    ret->val3 = 1;
    ret->type = RE_COMMAND_SUPER;

    qDebug() << "Meta" << state->app.pname;

    if( state->app.pname==RE_PROC_CHESS )
    {
        ret->val1 = KEY_F1;
        ret->type = RE_COMMAND_DIRS;
    }
    else if( state->app.pname==RE_PROC_QT )
    {
        ret->val1 = KEY_F1;
        ret->type = RE_COMMAND_DIRS;
    }
    else if( state->app.pname==RE_PROC_VSCODE )
    {
        ret->val1 = KEY_F5;
        ret->type = RE_COMMAND_DIRS;
    }
    else if( state->app.pname==RE_PROC_GIT )
    {
        re_mouseKey(3);
//        ret->val1 = KEY_UP;

//        ret->val2 = 5;
//        ret->val3 = 1;
//        ret->type  = RE_COMMAND_DIRS;
//        ret->state = RE_CSTATE_0;
        qDebug() << "super";
//        cmd = re_getGoGitKraken(val);
    }
    else if( state->app.pname==RE_PROC_FIREFOX ||
             state->app.pname==RE_PROC_GEKO )
    {
        ret->mod_list.append(KEY_LEFTCTRL);
        ret->val1 = KEY_W;

        ret->val2 = 1;
        ret->val3 = 1;
        ret->type  = RE_COMMAND_MOD;
        ret->state = RE_CSTATE_0;
    }
    else if( state->app.pname==RE_PROC_EXPLORER )
    {
        ret->mod_list.append(KEY_LEFTCTRL);
        ret->val1 = KEY_W;

        ret->val2 = 1;
        ret->val3 = 1;
        ret->type  = RE_COMMAND_MOD;
        ret->state = RE_CSTATE_0;
    }
    else if( state->app.pname==RE_PROC_TELEGRAM )
    {
#ifdef WIN32
        recordTelegram();
        ret->val3 = -1;
#else
        system("./Scripts/telegram_voice.sh");
#endif
    }
    else if( state->app.pname==RE_PROC_ALTIUM )
    {
#ifdef WIN32
        ret->mod_list.append(KEY_LEFTCTRL);
        ret->val1 = KEY_F4;

        ret->val2 = 1;
        ret->val3 = 1;
        ret->type  = RE_COMMAND_MOD;
        ret->state = RE_CSTATE_0;
#endif
    }
}

void ReSuper::getCopyCmd(CCommand *ret)
{
    ret->val2 = 1;
    ret->val3 = 1;
    ret->type  = RE_COMMAND_MOD;
    ret->state = RE_CSTATE_0;

    ret->mod_list.append(KEY_LEFTCTRL);
    ret->val1 = KEY_C;
}

void ReSuper::getPasteCmd(CCommand *ret)
{
    ret->val2 = 1;
    ret->val3 = 1;
    ret->type  = RE_COMMAND_MOD;
    ret->state = RE_CSTATE_0;

    ret->mod_list.append(KEY_LEFTCTRL);
    ret->val1 = KEY_V;
}

// Language switch
void ReSuper::getLSwitchCmd(CCommand *ret)
{
#ifdef WIN32
    // Switch to next language
    // Need an hwnd to work for console
    // applications
    HWND handle = GetForegroundWindow();
    PostMessage(handle, WM_INPUTLANGCHANGEREQUEST,
                0, (LPARAM)HKL_NEXT);
    makeNull(ret);
#else
    ///FIXME
#endif
}

void ReSuper::getChessCmd(CCommand *ret, QString cmd)
{
#ifdef WIN32
    QString pipe_data = cmd + CH_NP_SEPARATOR;
    sendPipe(pipe_data.toStdString().c_str());
#else
    QString pipe_data = "dbus-send --dest=com.benjamin.chess";
    pipe_data += "dbus-send --dest=com.benjamin.chess";
    pipe_data += " / com.benjamin.chess.show string:\"";
    pipe_data += cmd + "\"";
    system(pipe_data.toStdString().c_str());
#endif
    makeNull(ret);
}

void ReSuper::getCommentCmd(CCommand *ret)
{
#ifdef WIN32
    sendPipe("comment" CH_NP_SEPARATOR);
#else
    system("dbus-send --dest=com.benjamin.chess"
           " / com.benjamin.chess.show string:\"comment\"");
#endif
    makeNull(ret);
}

void ReSuper::getCamelCmd(CCommand *ret)
{
    qDebug() << "CreateProcess 1";
#ifdef WIN32
#else
    system("./Scripts/camel");
#endif
    makeNull(ret);
}

void ReSuper::getSelectCmd(CCommand *ret)
{
    key.sendKey(VK_END);
    ret->val2 = 1;
    ret->val3 = 1;
    ret->type  = RE_COMMAND_MOD;
    ret->state = RE_CSTATE_0;

    ret->mod_list.append(KEY_LEFTSHIFT);

    ret->val1 = VK_HOME;
    qDebug() << "select";
}

void ReSuper::getLoveCmd(CCommand *ret)
{
    ret->val2 = 1;
    ret->val3 = 1;
    ret->type  = RE_COMMAND_MOD;
    ret->state = RE_CSTATE_0;

    ret->mod_list.append(KEY_LEFTCTRL);
    ret->val1 = KEY_LEFT;
}

void ReSuper::getRogerCmd(CCommand *ret)
{
    ret->val2 = 1;
    ret->val3 = 1;
    ret->type  = RE_COMMAND_MOD;
    ret->state = RE_CSTATE_0;

    ret->mod_list.append(KEY_LEFTCTRL);
    ret->val1 = KEY_RIGHT;
}

void ReSuper::getSwitchCmd(CCommand *ret)
{
    ret->val2 = 1;
    ret->val3 = 1;
    ret->type  = RE_COMMAND_MOD;
    ret->state = RE_CSTATE_0;

#ifdef WIN32
    ret->mod_list.append(KEY_LEFTALT);
    ret->val1 = KEY_TAB;
#else
    ret->mod_list.append(KEY_META); ///FIXME KEYS
    ret->val1 = KEY_B;
#endif
}

void ReSuper::makeNull(CCommand *ret)
{
    ret->val1 = 0;
    ret->val2 = 0;
    ret->val3 = 1;
    ret->type  = RE_COMMAND_NULL;
    ret->state = RE_CSTATE_0;
    ret->mod_list.clear();
}

#ifdef WIN32
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

void ReSuper::recordTelegram()
{
    qDebug() << "recordTelegram";
    re_mouseMoveW(-30, -30);
    QThread::msleep(100);
    re_mousePress(1);
    QThread::msleep(1000);
    re_mouseMoveW(-30, -400);
    QThread::msleep(1000);
    re_mouseRelease(1);
}
#endif
