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
    executeAhk("raxis_right");
}

void ReRAxis::buttonLeftPressed()
{
    executeAhk("raxis_left");
}

void ReRAxis::buttonUpPressed()
{
    executeAhk("raxis_up");
}

void ReRAxis::buttonDownPressed()
{
    executeAhk("raxis_down");
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
