#include "re_exec.h"
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
    qDebug() <<  "Client: Go Next Page";
    system("./Scripts/button_a &");
}

void ReExec::buttonBPressed()
{
    qDebug() <<  "Client: Go Previous Page";
    system("./Scripts/button_b &");
}

void ReExec::buttonXPressed()
{
    qDebug() <<  "Client: Go To Sleep";
    system("xdotool click 1 &");
}

void ReExec::buttonYPressed()
{
    qDebug() <<  "Change Workspace";
    system("xdotool click 3 &");
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

}

void ReExec::buttonLAxisLeft()
{

}

void ReExec::buttonLAxisUp()
{

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
    system("xdotool set_desktop --relative 1 &");
}

void ReExec::buttonUpChanged()
{
    qDebug() <<  "Up workspace";
    system("xdotool set_desktop --relative 4 &");
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
