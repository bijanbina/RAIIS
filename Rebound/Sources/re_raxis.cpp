#include "re_raxis.h"
#include <QThread>

ReRAxis::ReRAxis(QObject *item, ReState *st, QObject *parent) : QObject(parent)
{
    ui = item;
    state = st;
}

#ifdef _WIN32
void ReRAxis::buttonRightPressed()
{
    if( state->ui_visible )
    {
        if ( state->getMode()==RE_MODE_SPOTIFY )
        {
            executScript("raxis_right", RE_SCR_SPOTIFY);
        }
        else
        {
            state->toggleUi(ui);
            QThread::msleep(20);
            executScript("raxis_right", RE_SCR_UI);
        }
    }
    else
    {
        executeAhk("raxis_right");
    }
}

void ReRAxis::buttonLeftPressed()
{
    if( state->ui_visible )
    {
        if ( state->getMode()==RE_MODE_SPOTIFY )
        {
            executScript("raxis_left", RE_SCR_SPOTIFY);
        }
        else
        {
            state->toggleUi(ui);
            QThread::msleep(20);
            executScript("raxis_left", RE_SCR_UI);
        }
    }
    else
    {
        executeAhk("raxis_left");
    }
}

void ReRAxis::buttonUpPressed()
{
    if( state->ui_visible )
    {
        if ( state->getMode()==RE_MODE_SPOTIFY )
        {
            executScript("raxis_up", RE_SCR_SPOTIFY);
        }
        else
        {
            state->toggleUi(ui);
            QThread::msleep(20);
            executScript("raxis_up", RE_SCR_UI);
        }
    }
    else
    {
        executeAhk("raxis_up");
    }
}

void ReRAxis::buttonDownPressed()
{
    if( state->ui_visible )
    {
        if ( state->getMode()==RE_MODE_SPOTIFY )
        {
            executScript("raxis_down", RE_SCR_SPOTIFY);
        }
        else
        {
            state->toggleUi(ui);
            QThread::msleep(20);
            executScript("raxis_down", RE_SCR_UI);
        }
    }
    else
    {
        executeAhk("raxis_down");
    }
}
#elif __linux__
void ReRAxis::buttonRightPressed()
{

}

void ReRAxis::buttonLeftPressed()
{

}

void ReRAxis::buttonUpPressed()
{
    system("./Scripts/raxis_up &");
}

void ReRAxis::buttonDownPressed()
{
    system("./Scripts/raxis_down &");
}
#endif
