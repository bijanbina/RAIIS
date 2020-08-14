#include "re_exec.h"

ReExec::ReExec()
{

}

void ReExec::buttonAPressed()
{
    qDebug() <<  "Client: Go Next Page";
    getIntCommand("xdotool key Right");
}

void ReExec::buttonBPressed()
{
    qDebug() <<  "Client: Go Previous Page";
    getIntCommand("xdotool key Left");
}

void ReExec::buttonXPressed()
{
    qDebug() <<  "Client: Go To Sleep";
    getIntCommand("xdotool key Left");
}

void ReExec::buttonYPressed()
{
    qDebug() <<  "Change Workspace";
    getIntCommand("xdotool key Left");
}

void ReExec::buttonL1Pressed()
{

    qDebug() <<  "Reset F";
       getIntCommand("xdotool key Left");
}

void ReExec::buttonL2Pressed()
{

    qDebug() <<  "Slower";
    getIntCommand("xdotool mousemove_relative 0 -20");
}

void ReExec::buttonR1Pressed()
{
//    qDebug() <<  "Faster";
//#ifdef __linux__
//       getIntCommand("xdotool mousemove_relative 0 -20");
//#endif
}

void ReExec::buttonR2Pressed()
{
    qDebug() <<  "Faster";
    getIntCommand("xdotool mousemove_relative 0 20");
}

void ReExec::buttonAxisLxChanged(double)
{

}

void ReExec::buttonAxisLyChanged(double)
{

}

void ReExec::buttonAxisRxChanged(double)
{

}

void ReExec::buttonAxisRyChanged(double)
{

}

void ReExec::buttonStartChanged()
{
    qDebug() <<  "Enable autoscroll";
    getIntCommand("xdotool key Menu");
    getIntCommand("xdotool key Up");
    getIntCommand("xdotool key Up");
    getIntCommand("xdotool key Up");
    getIntCommand("xdotool key Return");
}

void ReExec::buttonSelectChanged()
{
    qDebug() <<  "Enable autoscroll";
    getIntCommand("xdotool key Escape");
}

void ReExec::buttonDownChanged()
{
    qDebug() <<  "Down workspace";
    getIntCommand("xdotool set_desktop --relative 1");
}

void ReExec::buttonUpChanged()
{
    qDebug() <<  "Up workspace";
    getIntCommand("xdotool set_desktop --relative 4");
}

void ReExec::buttonRightChanged()
{
    qDebug() <<  "Next Window";
    getIntCommand("xdotool key Alt+Escape");
}

void ReExec::buttonLeftChanged()
{
    qDebug() <<  "Previous Window";
    getIntCommand("xdotool key Shift+Alt+Escape");
}




