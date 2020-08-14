#include "re_exec.h"

ReExec::ReExec()
{

}

void ReExec::buttonAPressed()
{
    qDebug() <<  "Client: Go Next Page";
#ifdef __linux__
       getIntCommand("xdotool key Right");
#endif
}

void ReExec::buttonBPressed()
{
    qDebug() <<  "Client: Go Previous Page";
#ifdef __linux__
       getIntCommand("xdotool key Left");
#endif
}

void ReExec::buttonXPressed()
{
    qDebug() <<  "Client: Go To Sleep";
#ifdef __linux__
       getIntCommand("xdotool key Left");
#endif
}

void ReExec::buttonYPressed()
{
    qDebug() <<  "Change Workspace";
#ifdef __linux__
       getIntCommand("xdotool key Left");
#endif
}

void ReExec::buttonL1Pressed()
{

    qDebug() <<  "Reset F";
#ifdef __linux__
       getIntCommand("xdotool key Left");
#endif
}

void ReExec::buttonL2Pressed()
{

    qDebug() <<  "Slower";
#ifdef __linux__
       getIntCommand("xdotool mousemove_relative 0 -20");
#endif
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
#ifdef __linux__
       getIntCommand("xdotool mousemove_relative 0 20");
#endif
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
#ifdef __linux__
       getIntCommand("xdotool key Menu");
       getIntCommand("xdotool key Up");
       getIntCommand("xdotool key Up");
       getIntCommand("xdotool key Up");
       getIntCommand("xdotool key Return");
#endif
}

void ReExec::buttonSelectChanged()
{
    qDebug() <<  "Enable autoscroll";
#ifdef __linux__
       getIntCommand("xdotool key Escape");
#endif
}




