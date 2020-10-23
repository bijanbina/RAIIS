#include "re_raxis.h"
#include <QThread>

ReRAxis::ReRAxis(QObject *item, QObject *parent) : QObject(parent)
{
    ui = item;
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
