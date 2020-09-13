#include "re_exec.h"

ReExec::ReExec(QObject *item, QObject *parent) : QObject(parent)
{
    //init
    ui = item;
}

void ReExec::buttonAPressed()
{
    qDebug() <<  "Client: Go Next Page";
    system("xdotool key Right &");
}

void ReExec::buttonBPressed()
{
    qDebug() <<  "Client: Go Previous Page";
    system("xdotool key Left");
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
    qDebug() <<  "Reset F";
    system("xdotool key Left &");
}

void ReExec::buttonL2Pressed()
{
    qDebug() <<  "Slower";
    system("xdotool mousemove_relative 0 -20 &");
}

void ReExec::buttonL3Pressed()
{
//    qDebug() <<  "Slower";
//    system("xdotool mousemove_relative 0 -20 &");
}

void ReExec::buttonR1Pressed()
{
//    qDebug() <<  "Faster";
//#ifdef __linux__
//       system("xdotool mousemove_relative 0 -20");
//#endif
}

void ReExec::buttonR2Pressed()
{
    qDebug() <<  "Faster";
    system("xdotool mousemove_relative 0 20 &");
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

}

void ReExec::buttonRAxisDown()
{

}

void ReExec::buttonStartChanged()
{
    qDebug() <<  "Enable autoscroll";
    system("./Scripts/menu_button");
}

void ReExec::buttonSelectChanged()
{
    qDebug() <<  "Enable autoscroll";
    system("xdotool key Escape &");
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
    qDebug() <<  "Next Window";
    system("xdotool key Alt+Escape &");
}

void ReExec::buttonLeftChanged()
{
    qDebug() <<  "Previous Window";
    system("xdotool key Shift+Alt+Escape &");
}




