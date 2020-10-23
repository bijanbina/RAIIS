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
    executeAhk("button_down");
}

void ReDirections::buttonUpPressed()
{
    executeAhk("button_up");
}

void ReDirections::buttonRightPressed()
{
    executeAhk("button_right");
}

void ReDirections::buttonLeftPressed()
{
    executeAhk("button_left");
}
#elif __linux__
void ReExec::buttonDownPressed()
{
    qDebug() <<  "Down workspace";
    system("./Scripts/button_down &");
}

void ReExec::buttonUpPressed()
{
    qDebug() <<  "Up workspace";
    system("./Scripts/button_up &");
}

void ReExec::buttonRightPressed()
{
    system("./Scripts/button_right &");
}

void ReExec::buttonLeftPressed()
{
    qDebug() <<  "Previous Window";
    system("./Scripts/button_left &");
}
#endif
