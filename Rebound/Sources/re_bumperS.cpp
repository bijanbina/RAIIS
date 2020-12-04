#include "re_bumpers.h"
#include <QThread>

ReBumpers::ReBumpers(QObject *item, QObject *switcher, ReState *st, QObject *parent) : QObject(parent)
{
    ui = item;
    state = st;
    uiSwitcher = switcher;
}

#ifdef _WIN32
void ReBumpers::buttonL1Pressed()
{
    if( state->ui_visible )
    {
         state->toggleUi(ui);
         QThread::msleep(20);
         executeUi("l1");
    }
    else
    {
        if( isItemVisible(uiSwitcher) )
        {
            QQmlProperty::write(uiSwitcher, "visible", 0);
        }
        else
        {
            if( state->youtube_mode )
            {
                qDebug() << "fuck";
                executeYoutube("l1");
            }
            else
            {
                executeAhk("button_l1");
            }
        }
    }
}

void ReBumpers::buttonL2Pressed()
{
    if( state->ui_visible )
    {
         state->toggleUi(ui);
         QThread::msleep(20);
         executeUi("l2");
    }
    else
    {
         executeAhk("button_l2");
    }
}

void ReBumpers::buttonR1Pressed()
{
    if( state->ui_visible )
    {
         state->toggleUi(ui);
         QThread::msleep(00);
         executeUi("r1");
    }
    else
    {
        executeAhk("button_r1");
    }
}

void ReBumpers::buttonR2Pressed()
{
    if( state->ui_visible )
    {
         state->toggleUi(ui);
         QThread::msleep(20);
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
