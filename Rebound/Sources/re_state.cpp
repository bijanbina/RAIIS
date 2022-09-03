#include "re_state.h"

ReState::ReState(QObject *parent) : QObject(parent)
{
    i_mode = RE_MODE_HIDDEN;
    i_proc = RE_WIN_UNKNOWN;
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
#ifdef WIN32
    ///POLYBAR INTEGRATION
    QString path = MOM_LABEL_DIR;
    path += MOM_LABEL_STATUS;
#else
    QString path = getenv("HOME");
    path += "/.config/polybar/awesomewm/ben_status";
#endif
    QFile file(path);
    if( file.open(QIODevice::ReadOnly) )
    {
        QString line = file.readLine();
        line.replace('\n', "");
        file.close();

        if( line.contains("Sleep") )
        {
            sleep_state = 1;
        }
        else
        {
            rmStatusFile();
        }
    }
}

void ReState::rmStatusFile()
{
#ifdef WIN32
    QString path = MOM_LABEL_DIR;
    path += MOM_LABEL_STATUS;
#else
    QString path = getenv("HOME");
    path += "/.config/polybar/awesomewm/ben_status";
#endif
    if( QFileInfo::exists(path) )
    {
#ifdef WIN32
        QString cmd = "del ";
#else
        QString cmd = "rm ";
#endif
        cmd += path;

        system(cmd.toStdString().c_str());
    }
}

void ReState::rmSpexFile()
{
#ifdef WIN32
    ///POLYBAR INTEGRATION
#else
    QString path = getenv("HOME");
    path += "/.config/polybar/awesomewm/ben_spex";
    if( QFileInfo::exists(path) )
    {
        QString cmd = "rm ";
        cmd += path;

        system(cmd.toStdString().c_str());
    }
#endif
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

#ifdef WIN32
    setProcess(app.pname);
#else
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

    QString cmd = "echo \"";
    cmd += app.pname + "\"";
    cmd += " > ~/.config/polybar/awesomewm/ben_status";
    system(cmd.toStdString().c_str());
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
#ifdef WIN32
    QString cmd;
    cmd = "%{B#0067aa}%{F#ffffff}%{A1:$HS_CMD:}";
    cmd += "  Sleep  %{A}%{B- F1-}";
    writeStatus(cmd);
#else
    writeStatus("Sleep");
#endif
}

void ReState::writeStatus(QString input)
{
#ifdef WIN32
    QString path = MOM_LABEL_DIR;
    path += MOM_LABEL_STATUS;
    QFile st_file(path);

    if( !st_file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Error creating" << MOM_LABEL_STATUS;
        qDebug() << "Trying to create" << MOM_LABEL_DIR;
        system("mkdir " MOM_LABEL_DIR);
        return;
    }
    QTextStream out(&st_file);
    out << input;
    st_file.close();
#else
    QString cmd = "echo '" + input;
    cmd += "' > ~/.config/polybar/awesomewm/ben_status";
    system(cmd.toStdString().c_str());
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
        rmStatusFile();
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
        writeStatus(cmd);
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
        writeStatus(cmd);
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
