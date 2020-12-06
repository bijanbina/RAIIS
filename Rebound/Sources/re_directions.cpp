#include "re_directions.h"
#include <QThread>

ReDirections::ReDirections(QObject *item, ReState *st, QObject *parent) : QObject(parent)
{
    ui = item;
    state = st;
}

#ifdef _WIN32
void ReDirections::buttonDownPressed()
{
    if( state->ui_visible )
    {
         state->toggleUi(ui);
         QThread::msleep(20);
         executScript("button_down", RE_SCR_UI);
    }
    else
    {
        executeAhk("button_down");
    }
}

void ReDirections::buttonUpPressed()
{
    if( state->ui_visible )
    {
         state->toggleUi(ui);
         QThread::msleep(20);
         executScript("button_up", RE_SCR_UI);
    }
    else
    {
        executeAhk("button_up");
    }
}

void ReDirections::buttonRightPressed()
{
    if( state->ui_visible )
    {
         state->toggleUi(ui);
         QThread::msleep(20);
         executScript("button_right", RE_SCR_UI);
    }
    else
    {
        executeAhk("button_right");
    }
}

void ReDirections::buttonLeftPressed()
{
    if( state->ui_visible )
    {
         state->toggleUi(ui);
         QThread::msleep(20);
         executScript("button_left", RE_SCR_UI);
    }
    else
    {
        executeAhk("button_left");
    }
}
#elif __linux__
void ReDirections::buttonDownPressed()
{
    qDebug() <<  "Down workspace";
    system("./Scripts/button_down &");
}

void ReDirections::buttonUpPressed()
{
    qDebug() <<  "Up workspace";
    system("./Scripts/button_up &");
}

void ReDirections::buttonRightPressed()
{
    system("./Scripts/button_right &");
}

void ReDirections::buttonLeftPressed()
{
    qDebug() <<  "Previous Window";
    system("./Scripts/button_left &");
}
#endif
