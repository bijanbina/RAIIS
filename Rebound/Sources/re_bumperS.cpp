#include "re_bumpers.h"
#include <QThread>

ReBumpers::ReBumpers(QObject *item, ReState *st, QObject *parent) : QObject(parent)
{
    ui = item;
    state = st;
}

#ifdef _WIN32
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
#elif __linux__
void ReBumpers::buttonL1Pressed()
{
    qDebug() <<  "L1";
    system("./Scripts/button_l1 &");
}

void ReBumpers::buttonL2Pressed()
{
    qDebug() <<  "Slower";
    system("./Scripts/button_l2 &");
}

//void ReBumpers::buttonL3Pressed()
//{
//    qDebug() <<  "Slower";
//    system("xdotool mousemove_relative 0 -20 &");
//}

void ReBumpers::buttonR1Pressed()
{
    qDebug() <<  "R1";
    system("./Scripts/button_r1 &");
}

void ReBumpers::buttonR2Pressed()
{
    qDebug() <<  "Faster";
    system("./Scripts/button_r2 &");
}

//void ReBumpers::buttonR3Pressed()
//{
//    qDebug() <<  "Faster";
//    system("xdotool mousemove_relative 0 20 &");
//}
#endif
