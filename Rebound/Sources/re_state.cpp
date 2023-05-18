#include "re_state.h"

ReState::ReState(QObject *parent) : QObject(parent)
{
    i_mode = RE_MODE_HIDDEN;
    ui_visible = false;
    fl = new ReFirefox;

#ifdef _WIN32
    api = new ReApi;
    hardware = new ReHardwareW;
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

void ReState::wakeUp()
{
    sleep_state = 0;
    if( fl->sc_dir )
    {
        enScroll(fl->sc_dir, fl->sc_speed);
    }
    else if( chess_mode )
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
