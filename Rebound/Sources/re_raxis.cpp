#include "re_raxis.h"
#include <QThread>

ReRAxis::ReRAxis(QObject *item, ReState *st, QObject *parent) : QObject(parent)
{
    ui = item;
    state = st;
}

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
