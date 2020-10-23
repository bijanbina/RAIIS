#include "re_laxis.h"
#include <QThread>

ReLAxis::ReLAxis(QObject *item, ReState *st, QObject *parent) : QObject(parent)
{
    ui = item;
    state = st;
}

void ReLAxis::buttonRight()
{
    executeAhk("laxis_right");
}

void ReLAxis::buttonLeft()
{
    executeAhk("laxis_left");
}

void ReLAxis::buttonUp()
{
    executeAhk("laxis_up");
}

void ReLAxis::buttonDown()
{
    executeAhk("laxis_down");
}
