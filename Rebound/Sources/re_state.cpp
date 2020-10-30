#include "re_state.h"

ReState::ReState(QObject *parent) : QObject(parent)
{
    i_mode = RE_MODE_HIDDEN;
    i_proc = RE_PROC_UNKNOWN;
    ui_visible = false;

#ifdef _WIN32
    api = new ReApiW;
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
    setMode(RE_MODE_MAIN);
    updateProcess();

    QMetaObject::invokeMethod(item, "uiToggle");
    ui_visible = QQmlProperty::read(item, "visible").toInt();
    if(!ui_visible)
    {
        i_mode = RE_MODE_HIDDEN;
    }
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

void ReState::updateProcess()
{
    QString name;

#ifdef _WIN32
    name = api->getPNameA();
    setProcess(name);
    emit updateMode();
#endif
}

void ReState::propageteMode(int mode)
{
    i_mode = mode;
    emit updateMode();
}
