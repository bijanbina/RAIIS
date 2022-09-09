#include "re_state.h"

ReState::ReState(QObject *parent) : QObject(parent)
{
    i_mode = RE_MODE_HIDDEN;
    ui_visible = false;
    fl = new ReFirefox;
    super = new ReSuper(&app);

#ifdef _WIN32
    api = new ReApi;
    hardware = new ReHardwareW;
#endif

    readStatusFile();
}

ReState::~ReState()
{
    delete super;
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
    QString status = re_readStatus();

    QRegExp go_reg("^go");
    QRegExp sky_reg("^Sky");
    QRegExp dive_reg("^Dive");
    QRegExp number_reg("\\d*");

    if( status.contains(go_reg) )
    {
        return;
    }
    else if( status.contains(sky_reg) )
    {
        return;
    }
    else if( status.contains(dive_reg) )
    {
        return;
    }
    else if( number_reg.exactMatch(status) )
    {
        if( status.length() )
        {
            return;
        }
    }
    else if( status=="Sleep" )
    {
        return;
    }
    else if( status=="Halt" )
    {
        return;
    }

    QString cmd;
#ifdef WIN32
    cmd = "%{B#0067aa}%{F#ffffff}%{A1:$HS_CMD:}  ";
    cmd += app.pname;
    cmd += "  %{A}%{B- F1-}";
#else
    cmd = app.pname;
#endif
    re_writeStatus(cmd);
}

void ReState::goToSleep()
{
    sleep_state = 1;
#ifdef WIN32
    QString cmd;
    cmd = "%{B#0067aa}%{F#ffffff}%{A1:$HS_CMD:}";
    cmd += "  Sleep  %{A}%{B- F1-}";
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

    if( chess_mode )
    {
        chess_mode = 0;
        re_rmStatus();
    }
}

bool ReState::isSleep()
{
    return sleep_state;
}
