#include "re_state.h"

ReState::ReState(QObject *parent) : QObject(parent)
{
    i_mode = RE_MODE_HIDDEN;
    ui_visible = false;
    fl = new ReFirefox;

#ifdef _WIN32
    api = new ReApi;
    hardware = new ReHardwareW;
    connectChessPipe();
#endif

    readStatusFile();
}

ReState::~ReState()
{
    delete fl;

#ifdef _WIN32
    delete api;
    delete hardware;
#endif
}

void ReState::readStatusFile()
{
    QString line = re_readStatus();
    if( line.length() )
    {
        if( line.contains("Sleep") )
        {
            sleep_state = 1;
        }
        else
        {
            re_rmStatus();
        }
    }
}

void ReState::toggleUi(QObject *item)
{
    i_mode = RE_MODE_MAIN;
    emit updateMode();

    QMetaObject::invokeMethod(item, "uiToggle");
    ui_visible = QQmlProperty::read(item, "visible").toInt();
    if( !ui_visible )
    {
        i_mode = RE_MODE_HIDDEN;
    }
}

void ReState::updateApp(ReWindow active_window)
{
    app = active_window;

    QString cmd;
#ifdef WIN32
    cmd  = "%{B#0067aa}%{F#ffffff}  ";
    cmd += app.pname;
    cmd += "  %{B- F1-}";
#else
    cmd = app.pname;
#endif
    re_writePStatus(cmd);
}

void ReState::goToSleep()
{
    sleep_state = 1;
#ifdef WIN32
    QString cmd;
    cmd = "%{B#0067aa}%{F#ffffff}%{A1:$HS_CMD:}";
    cmd += "  Sleep  %{A1}%{B- F1-}";
    re_writeStatus(cmd);
#else
    writeStatus("Sleep");
#endif
}

void ReState::goToDictate()
{
    sleep_state = 1;
    dictate_state = 1;
#ifdef WIN32
    QString cmd;
    cmd = "%{B#aa6700}%{F#ffffff}%{A1:$HS_CMD:}";
    cmd += "  Dictate  %{A1}%{B- F1-}";
    re_writeStatus(cmd);
#else
    writeStatus("Dictate");
#endif
}

void ReState::goToDrag()
{
    drag_state = 1;
#ifdef WIN32
    QString cmd;
    cmd = "%{B#67bb00}%{F#ffffff}%{A1:$HS_CMD:}";
    cmd += "  Drag  %{A1}%{B- F1-}";
    re_writeStatus(cmd);
#else
    writeStatus("Dictate");
#endif
}

void ReState::wakeUp()
{
    sleep_state = 0;
    if( fl->sc_dir )
    {
        enScroll(fl->sc_dir, fl->sc_speed);
    }
    else if( ch_count )
    {
        system("echo 'Chess' > ~/.config/polybar/awesomewm/ben_status");
    }
    else
    {
        re_rmStatus();
    }
}

// enable scroll
void ReState::enScroll(int dir, int speed)
{
    QString cmd;

    if( dir==RE_META_SKY )
    {
        cmd = "Sky ";
        cmd += QString::number(speed);
#ifdef WIN32
        cmd = "%{B#0067aa}%{F#ffffff}  " + cmd;
        cmd += "  %{B- F1-}";
#endif
        re_writeStatus(cmd);
        fl->scrollUp(speed, cmd);
    }
    else if( dir==RE_META_DIVE )
    {
        cmd = "Dive ";
        cmd += QString::number(speed);
#ifdef WIN32
        cmd = "%{B#0067aa}%{F#ffffff}  " + cmd;
        cmd += "  %{B- F1-}";
#endif
        re_writeStatus(cmd);
        fl->scrollDown(speed, cmd);
    }
}

// is escape command
bool ReState::isEscape(CCommand command)
{
    if( command.type!=RE_COMMAND_DIRS )
    {
        return 0;
    }

    if( command.val1!=KEY_ESC )
    {
        return 0;
    }

    return 1;
}

void ReState::resetState()
{
    if( fl->sc_dir )
    {
        fl->sc_dir = 0;
        fl->scrollEscape();
        re_rmStatus();
    }
}

bool ReState::isSleep()
{
    return sleep_state;
}

void ReState::connectChessPipe()
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

void ReState::sendPipe(const char *data)
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
