#include "re_state.h"

int  ReState::remote_id     = 0;
bool ReState::sleep_state   = 0;
bool ReState::dictate_state = 0;
bool ReState::record_state  = 0;
bool ReState::remote_state  = 0;
bool ReState::drag_state    = 0;
int  ReState::ch_count      = 0; //Chess Count
//ReFirefox  *ReState::fl         = NULL;
ReLink     *ReState::link       = NULL;
ReWindow    ReState::app; //Active Window
CCommand    ReState::last_cmd;

ReState::ReState()
{
}

ReState::~ReState()
{
}

void ReState::init()
{
//    fl = new ReFirefox;
    readStatusFile();
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
    // disable any current extra state(scroll, ...)
    stopFFScroll();

    sleep_state = 1;
    last_cmd.type = RE_COMMAND_NULL;
#ifdef WIN32
    QString cmd;
    cmd = "%{B#0067aa}%{F#ffffff}%{A1:$HS_CMD:}";
    cmd += "  Sleep  %{A1}%{B- F1-}";
    re_writeStatus(cmd);
#else
    re_writeStatus("Sleep");
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
    re_writeStatus("Dictate");
#endif
}

void ReState::goToRemote(int rid)
{
    if( rid )
    {
        remote_id = rid;
    }
    remote_state = 1;
    sleep_state = 0 ;
#ifdef WIN32
    QString cmd;
    cmd = "%{B#006700}%{F#ffffff}%{A1:$HS_CMD:}";
    cmd += "  Remote  %{A1}%{B- F1-}";
    re_writeStatus(cmd);
#else
    re_writeStatus("Remote");
#endif
}

void ReState::goToRecord()
{
    sleep_state = 1;
    record_state = 1;
#ifdef WIN32
    QString cmd;
    cmd = "%{B#aa1100}%{F#ffffff}%{A1:$HS_CMD:}";
    cmd += "  Record  %{A1}%{B- F1-}";
    re_writeStatus(cmd);
#else
    re_writeStatus("Record");
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
    re_writeStatus("Dictate");
#endif
}

void ReState::wakeUp()
{
    sleep_state = 0;
    if( link->sc_dir )
    {
        enScroll(link->sc_dir, link->sc_speed);
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
//        fl->scrollUp(speed, cmd);
        link->scrollUp(speed);
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
//        fl->scrollDown(speed, cmd);
        link->scrollDown(speed);
    }
}

// is escape command
bool ReState::isEscape(CCommand cmd)
{
    if( cmd.type!=RE_COMMAND_DIRS )
    {
        return 0;
    }

    if( cmd.val1!=KEY_ESC )
    {
        return 0;
    }

    if( cmd.is_alt  || cmd.is_shift ||
        cmd.is_ctrl || cmd.is_super )
    {
        return 0;
    }

    return 1;
}

int ReState::stopFFScroll()
{
    if( link->sc_dir )
    {
//        fl->sc_dir = 0;
//        fl->scrollEscape();
        link->scrollEscape();

        re_rmStatus();
        return 1;
    }
    return 0;
}
