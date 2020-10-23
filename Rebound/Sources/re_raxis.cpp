#include "re_raxis.h"
#include <QThread>

ReRAxis::ReRAxis(QObject *item, ReState *st, QObject *parent) : QObject(parent)
{
    ui = item;
    state = st;
}

void ReRAxis::buttonRight()
{
    executeAhk("raxis_right");
}

void ReRAxis::buttonLeft()
{
    executeAhk("raxis_left");
}

void ReRAxis::buttonUp()
{
    executeAhk("raxis_up");
}

void ReRAxis::buttonDown()
{
    executeAhk("raxis_down");
}
