#include "re_laxis.h"
#include <QThread>

ReLAxis::ReLAxis(QObject *item, ReState *st, QObject *parent) : QObject(parent)
{
    ui = item;
    state = st;
}

#ifdef _WIN32
void ReLAxis::buttonRightPressed()
{
    if( state->ui_visible )
    {
        if ( state->getMode()==RE_MODE_SPOTIFY )
        {
            executScript("laxis_right", RE_SCR_SPOTIFY);
        }
        else
        {
            state->toggleUi(ui);
            QThread::msleep(20);
            executScript("laxis_right", RE_SCR_UI);
        }
    }
    else
    {
        executeAhk("laxis_right");
    }
}

void ReLAxis::buttonLeftPressed()
{
    if( state->ui_visible )
    {
        if ( state->getMode()==RE_MODE_SPOTIFY )
        {
            executScript("laxis_left", RE_SCR_SPOTIFY);
        }
        else
        {
            state->toggleUi(ui);
            QThread::msleep(20);
            executScript("laxis_left", RE_SCR_UI);
        }
    }
    else
    {
        executeAhk("laxis_left");
    }
}

void ReLAxis::buttonUpPressed()
{
    if( state->ui_visible )
    {
        if ( state->getMode()==RE_MODE_SPOTIFY )
        {
            executScript("laxis_up", RE_SCR_SPOTIFY);
        }
        else
        {
            state->toggleUi(ui);
            QThread::msleep(20);
            executScript("laxis_up", RE_SCR_UI);
        }
    }
    else
    {
        executeAhk("laxis_up");
    }
}

void ReLAxis::buttonDownPressed()
{
    if( state->ui_visible )
    {
        if ( state->getMode()==RE_MODE_SPOTIFY )
        {
            executScript("laxis_down", RE_SCR_SPOTIFY);
        }
        else
        {
            state->toggleUi(ui);
            QThread::msleep(20);
            executScript("laxis_down", RE_SCR_UI);
        }
    }
    else
    {
        executeAhk("laxis_down");
    }
}
#elif __linux__
void ReLAxis::buttonRightPressed()
{
    if( state->ui_visible )
    {
         state->toggleUi(ui);
         system("xdotool key Super+Right");
    }
    else
    {
        system("./Scripts/laxis_right &");
    }
}

void ReLAxis::buttonLeftPressed()
{
    if( state->ui_visible )
    {
         state->toggleUi(ui);
         system("xdotool key Super+Left");
    }
    else
    {
        system("./Scripts/laxis_left &");
    }
}

void ReLAxis::buttonUpPressed()
{
    if( state->ui_visible )
    {
         state->toggleUi(ui);
         system("xdotool key Super+Shift+Up");
    }
    else
    {
        system("./Scripts/laxis_up &");
    }
}

void ReLAxis::buttonDownPressed()
{
    if( state->ui_visible )
    {
         state->toggleUi(ui);
         system("xdotool key Super+Shift+Down");
    }
    else
    {
        system("./Scripts/laxis_down &");
    }
}
#endif
