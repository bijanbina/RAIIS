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
         state->toggleUi(ui);
         QThread::msleep(20);
         executeUi("raxis_right");
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
         state->toggleUi(ui);
         QThread::msleep(20);
         executeUi("raxis_left");
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
         state->toggleUi(ui);
         QThread::msleep(20);
         executeUi("raxis_up");
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
         state->toggleUi(ui);
         QThread::msleep(20);
         executeUi("raxis_down");
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
