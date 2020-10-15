#include "re_exec.h"
#include "backend.h"
#include "QThread"

ReExec::ReExec(QObject *item, QObject *parent) : QObject(parent)
{
    //init
    ui = item;
    reX11_init();

    //switching tab
    timer_tab = new QTimer;
//    timer_tab->setSingleShot(true);
    connect(timer_tab, SIGNAL(timeout()), this, SLOT(tab_timeout()));
}

void ReExec::tab_timeout()
{
    timer_tab->stop();
    sendFakeEvent(0, XK_Alt_L); //A release
}

void ReExec::buttonAPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         system("./Scripts/focus_window spotify");
    }
    else
    {
        system("./Scripts/button_a &");
    }
}

void ReExec::buttonBPressed()
{
    system("./Scripts/button_b &");
}

void ReExec::buttonXPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         system("xdotool key Alt+F4 &");
    }
    else
    {
        system("./Scripts/button_x &");
    }
}

void ReExec::buttonYPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         system("./Scripts/focus_window firefox");
    }
    else
    {
        system("./Scripts/button_y &");
    }
}

void ReExec::buttonL1Pressed()
{
    qDebug() <<  "L1";
    system("./Scripts/button_l1 &");
}

void ReExec::buttonL2Pressed()
{
    qDebug() <<  "Slower";
    system("./Scripts/button_l2 &");
}

void ReExec::buttonL3Pressed()
{
//    qDebug() <<  "Slower";
//    system("xdotool mousemove_relative 0 -20 &");
}

void ReExec::buttonR1Pressed()
{
    qDebug() <<  "R1";
    system("./Scripts/button_r1 &");
}

void ReExec::buttonR2Pressed()
{
    qDebug() <<  "Faster";
    system("./Scripts/button_r2 &");
}

void ReExec::buttonR3Pressed()
{
//    qDebug() <<  "Faster";
//    system("xdotool mousemove_relative 0 20 &");
}

void ReExec::buttonLAxisRight()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         system("xdotool key Super+Right");
    }
    else
    {
        system("./Scripts/laxis_right &");
    }
}

void ReExec::buttonLAxisLeft()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         system("xdotool key Super+Left");
    }
    else
    {
        system("./Scripts/laxis_left &");
    }
}

void ReExec::buttonLAxisUp()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         system("xdotool key Alt+F10");
    }
    else
    {
        system("./Scripts/laxis_up &");
    }
}

void ReExec::buttonLAxisDown()
{

}

void ReExec::buttonRAxisRight()
{

}

void ReExec::buttonRAxisLeft()
{

}

void ReExec::buttonRAxisUp()
{
    system("./Scripts/raxis_up &");
}

void ReExec::buttonRAxisDown()
{
    system("./Scripts/raxis_down &");
}

void ReExec::buttonStartChanged()
{
    qDebug() <<  "Enable autoscroll";
    system("./Scripts/menu_button &");
}

//in native mode add sleep
void ReExec::buttonSelectChanged(int isNative)
{

    if( isUiVisible(ui) )
    {
         hideUI(ui);
         system("xdotool key XF86AudioMute &");
    }
    else
    {
        if( !timer_tab->isActive() )
        {
             sendFakeEvent(1, XK_Alt_L); //ALT_L press
        }

        if( isNative )
        {
            qDebug() <<  "Alt P" << isNative;
            QThread::msleep(100);
        }
        qDebug() <<  "Next Window" << isNative;
        system("xdotool key Tab &");
        timer_tab->start(RE_TAB_TIME);
    }
}

void ReExec::buttonCenterChanged()
{
//    qDebug() <<  "Enable autoscroll";
//    system("xdotool key Escape &");
}

void ReExec::buttonGuideChanged()
{
//    system("xdotool key Escape &");
    QMetaObject::invokeMethod(ui, "uiToggle");
}

void ReExec::buttonDownChanged()
{
    qDebug() <<  "Down workspace";
    system("./Scripts/button_down &");
}

void ReExec::buttonUpChanged()
{
    qDebug() <<  "Up workspace";
    system("./Scripts/button_up &");
}

void ReExec::buttonRightChanged()
{
    system("./Scripts/button_right &");
}

void ReExec::buttonLeftChanged()
{
    qDebug() <<  "Previous Window";
    system("./Scripts/button_left &");
}

