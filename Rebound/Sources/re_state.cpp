#include "re_state.h"

ReState::ReState(QObject *parent) : QObject(parent)
{
    i_mode = RE_MODE_HIDDEN;
    i_proc = RE_PROC_UNKNOWN;
    ui_visible = false;

#ifdef _WIN32
    api = new ReApiW;
    hardware = new ReHardwareW;
#endif
#ifdef __linux__
    api = new ReApiL;
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

    updateTitles(item);
    QQmlProperty::write(item, "active_process", 1);
    QQmlProperty::write(item, "visible", 1);
}

void ReState::setProcess(QString name)
{
    if( name.contains("qtcreator.exe") )
    {
        setProcess(RE_PROC_QT);
    }
    else if( name.contains("firefox.exe") )
    {
        setProcess(RE_PROC_FIREFOX);
    }
    else if( name.contains("Spotify.exe") )
    {
        setProcess(RE_PROC_SPOTIFY);
    }
    else if( name.contains("FoxitPhantomPDF.exe") )
    {
        setProcess(RE_PROC_READING);
    }
    else if( name.contains("FoxitPhantomPDF.exe") )
    {
        setProcess(RE_PROC_READING);
    }
    else if( name.contains("atom.exe") )
    {
        setProcess(RE_PROC_GEDIT);
    }
    else if( name.contains("Clover.exe") )
    {
        setProcess(RE_PROC_NAUTILUS);
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

void ReState::updateTitles(QObject *item)
{
    qDebug() << "updateTitles" << api->wins_title.size();

    for(int i=0; i<6; i++)
    {
        QQmlProperty::write(item, "process_id", i+1);
        if(i<api->wins_title.length())
        {
            QQmlProperty::write(item, "process_title", api->wins_title[i]);
        }
        else
        {
            QQmlProperty::write(item, "process_title", "");
        }
        QMetaObject::invokeMethod(item, "updateProcessTitle");
    }
}
