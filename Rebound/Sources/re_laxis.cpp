#include "re_laxis.h"
#include <QThread>

ReLAxis::ReLAxis(QObject *item, ReState *st, QObject *parent) : QObject(parent)
{
    ui = item;
    state = st;
}

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
