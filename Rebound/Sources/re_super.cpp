#include "re_super.h"
#include <QThread>

ReSuper::ReSuper(ReWindow *current_w, QObject *parent): QObject(parent)
{
    app = current_w;

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
        getKickCmd(ret);
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
        getSideCmd(ret);
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
        getResistCmd(ret);
    }
}

void ReSuper::getMetaCmd(CCommand *ret)
{
    ret->val2 = 1;
    ret->val3 = 1;
    ret->type = RE_COMMAND_SUPER;

    qDebug() << "Meta" << app->pname;

    if( app->pname==RE_PROC_CHESS )
    {
        ret->val1 = KEY_F1;
        ret->type = RE_COMMAND_DIRS;
    }
    else if( app->pname==RE_PROC_QT )
    {
        ret->val1 = KEY_F1;
        ret->type = RE_COMMAND_DIRS;
    }
    else if( app->pname==RE_PROC_VSCODE )
    {
        ret->val1 = KEY_F5;
        ret->type = RE_COMMAND_DIRS;
    }
    else if( app->pname==RE_PROC_GIT )
    {
//        cmd = re_getGoGitKraken(val);
    }
    else if( app->pname==RE_PROC_FIREFOX ||
             app->pname==RE_PROC_GEKO )
    {
        ret->mod_list.append(KEY_LEFTCTRL);
        ret->val1 = KEY_W;

        ret->val2 = 1;
        ret->val3 = 1;
        ret->type  = RE_COMMAND_MOD;
        ret->state = RE_CSTATE_0;
    }
    else if( app->pname==RE_PROC_EXPLORER )
    {
        ret->mod_list.append(KEY_LEFTCTRL);
        ret->val1 = KEY_W;

        ret->val2 = 1;
        ret->val3 = 1;
        ret->type  = RE_COMMAND_MOD;
        ret->state = RE_CSTATE_0;
    }
    else if( app->pname==RE_PROC_TELEGRAM )
    {
#ifdef WIN32
        ret->val2 = 0;
        recordTelegram();
        ret->val1 = VK_SCROLL;

        ret->val2 = 1;
        ret->val3 = 1;
        ret->type  = RE_COMMAND_NATO;
        ret->state = RE_CSTATE_0;
#else
        system("./Scripts/telegram_voice.sh");
#endif
    }
    else if( app->pname==RE_PROC_ALTIUM )
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

void ReSuper::getKickCmd(CCommand *ret)
{
#ifdef WIN32
    sendPipe("show" CH_NP_SEPARATOR);
#else
    system("dbus-send --dest=com.benjamin.chess"
           " / com.benjamin.chess.show string:\"\"");
#endif
    makeNull(ret);
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

void ReSuper::getSideCmd(CCommand *ret)
{
#ifdef WIN32
    sendPipe("side" CH_NP_SEPARATOR);
#else
    system("dbus-send --dest=com.benjamin.chess"
           " / com.benjamin.chess.show string:\"side\"");
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

void ReSuper::getResistCmd(CCommand *ret)
{
#ifdef WIN32
    sendPipe("persist" CH_NP_SEPARATOR);
#else
    system("dbus-send --dest=com.benjamin.chess"
           " / com.benjamin.chess.show string:\"\"");
#endif
    makeNull(ret);
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
