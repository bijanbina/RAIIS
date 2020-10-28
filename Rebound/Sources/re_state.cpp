#include "re_state.h"

ReState::ReState(QObject *parent) : QObject(parent)
{
    i_mode = RE_MODE_APPLICATION;
    i_proc = RE_PROC_UNKNOWN;
    api = new ReApiW;
}

void ReState::setMode(int mode)
{
    i_mode = mode;
}

int ReState::getMode()
{
    return i_mode;
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

    name = api->reGetPNameA();
    setProcess(name);
}
