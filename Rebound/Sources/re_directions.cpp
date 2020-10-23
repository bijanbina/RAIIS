#include "re_directions.h"
#include <QThread>

ReDirections::ReDirections(QObject *item, ReState *st, QObject *parent) : QObject(parent)
{
    ui = item;
    state = st;
}

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
