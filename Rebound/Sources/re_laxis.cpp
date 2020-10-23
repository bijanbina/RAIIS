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
    executeAhk("laxis_right");
}

void ReLAxis::buttonLeftPressed()
{
    executeAhk("laxis_left");
}

void ReLAxis::buttonUpPressed()
{
    executeAhk("laxis_up");
}

void ReLAxis::buttonDownPressed()
{
    executeAhk("laxis_down");
}
#elif __linux__
void ReLAxis::buttonRightPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         system("xdotool key Super+Right");
    }
    else
    {
        system("./Scripts/laxis_right &");
    }
}

void ReLAxis::buttonLeftPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         system("xdotool key Super+Left");
    }
    else
    {
        system("./Scripts/laxis_left &");
    }
}

void ReLAxis::buttonUpPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         system("xdotool key Alt+F10");
    }
    else
    {
        system("./Scripts/laxis_up &");
    }
}

void ReLAxis::buttonDownPressed()
{

}
#endif
