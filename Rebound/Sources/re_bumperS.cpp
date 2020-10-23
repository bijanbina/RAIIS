#include "re_bumpers.h"
#include <QThread>

ReBumpers::ReBumpers(QObject *item, QObject *parent) : QObject(parent)
{
    ui = item;
}

void ReBumpers::buttonL1Pressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("l1");
    }
    else
    {
        executeAhk("button_l1");
    }
}

void ReBumpers::buttonL2Pressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("l2");
    }
    else
    {
        executeAhk("button_l2");
    }
}

void ReBumpers::buttonR1Pressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("r1");
    }
    else
    {
        executeAhk("button_r1");
    }
}

void ReBumpers::buttonR2Pressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("r2");
    }
    else
    {
        executeAhk("button_r2");
    }
}
