 #include "re_state.h"

ReState::ReState(QObject *parent) : QObject(parent)
{
    i_mode = RE_MODE_HIDDEN;
    i_proc = RE_WIN_UNKNOWN;
    ui_visible = false;

#ifdef _WIN32
    api = new ReApi;
    hardware = new ReHardwareW;
#endif
#ifdef __linux__
    fl = new ReFirefoxL;
    readStatusFile();
#endif
}

void ReState::readStatusFile()
{
    QString path = getenv("HOME");
    path += "/.config/polybar/awesomewm/ben_status";
    QFile file(path);
    if( file.open(QIODevice::ReadOnly) )
    {
        QString line = file.readLine();
        line.replace('\n', "");

        if( line=="Sleep" )
        {
            sleep_state = 1;
            file.close();
        }
        else
        {
            file.close();
            rmStatusFile();
        }
    }
}

void ReState::rmStatusFile()
{
    QString path = getenv("HOME");
    path += "/.config/polybar/awesomewm/ben_status";
    if( QFileInfo::exists(path) )
    {
        QString cmd = "rm ";
        cmd += path;

        system(cmd.toStdString().c_str());
    }
}

void ReState::rmSpexFile()
{
    QString path = getenv("HOME");
    path += "/.config/polybar/awesomewm/ben_spex";
    if( QFileInfo::exists(path) )
    {
        QString cmd = "rm ";
        cmd += path;

        system(cmd.toStdString().c_str());
    }
}

void ReState::setMode(int mode)
{
    i_mode = mode;
}

int ReState::getMode()
{
    return i_mode;
}

void ReState::toggleUi(QObject *item)
{
    propageteMode(RE_MODE_MAIN);

    QMetaObject::invokeMethod(item, "uiToggle");
    ui_visible = QQmlProperty::read(item, "visible").toInt();
    if( !ui_visible )
    {
        i_mode = RE_MODE_HIDDEN;
    }
}

void ReState::showSwither(QObject *item)
{
    setMode(RE_MODE_SWITCH);

    ///FIXME: UNCOMMENT THIS
//    updateTitles(item);
    QQmlProperty::write(item, "active_process", 1);
    QQmlProperty::write(item, "visible", 1);
}

void ReState::setProcess(QString name)
{
    if( name.contains("qtcreator.exe") )
    {
        setProcess(RE_WIN_QT);
    }
    else if( name.contains("firefox.exe") )
    {
        setProcess(RE_WIN_FIREFOX);
    }
    else if( name.contains("Spotify.exe") )
    {
        setProcess(RE_WIN_SPOTIFY);
    }
    else if( name.contains("FoxitPhantomPDF.exe") )
    {
        setProcess(RE_WIN_READING);
    }
    else if( name.contains("FoxitPhantomPDF.exe") )
    {
        setProcess(RE_WIN_READING);
    }
    else if( name.contains("atom.exe") )
    {
        setProcess(RE_WIN_TEXTEDITOR);
    }
    else if( name.contains("Clover.exe") )
    {
        setProcess(RE_WIN_EXPLORER);
    }
}

void ReState::setProcess(int proc)
{
    i_proc = proc;
}

int ReState::getProcess()
{
    return i_proc;
}

void ReState::updateApp(ReWindow active_window)
{
    app = active_window;

#ifdef _WIN32
    setProcess(app.pname);
#endif
}

void ReState::propageteMode(int mode)
{
    i_mode = mode;
    emit updateMode();
}

void ReState::updateTitles(QStringList wins_title, QObject *item)
{
    qDebug() << "updateTitles" << wins_title.size();

    for(int i=0; i<6; i++)
    {
        QQmlProperty::write(item, "process_id", i+1);
        if( i<wins_title.length() )
        {
            QQmlProperty::write(item, "process_title", wins_title[i]);
        }
        else
        {
            QQmlProperty::write(item, "process_title", "");
        }
        QMetaObject::invokeMethod(item, "updateProcessTitle");
    }
}

void ReState::goToSleep()
{
    sleep_state = 1;
    system("echo Sleep > ~/.config/polybar/awesomewm/ben_status");
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
        rmStatusFile();
    }
}

// enable scroll
void ReState::enScroll(int dir, int speed)
{
    QString cmd = "echo '";

    if( dir==RE_META_SKY )
    {
        cmd += "Sky ";
        cmd += QString::number(speed);
        cmd += "' > ~/.config/polybar/awesomewm/ben_status";
        fl->scrollUp(speed, cmd);
    }
    else if( dir==RE_META_DIVE )
    {
        cmd += "Dive ";
        cmd += QString::number(speed);
        cmd += "' > ~/.config/polybar/awesomewm/ben_status";
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

    if( command.val1!=1 ) //Escape
    {
        return 0;
    }


}

void ReState::resetState()
{
    if( fl->sc_dir )
    {
        fl->sc_dir = 0;
        fl->scrollEscape();
        rmStatusFile();
    }

    if( chess_mode )
    {
        chess_mode = 0;
        rmStatusFile();
    }
}

bool ReState::isSleep()
{
    return sleep_state;
}
