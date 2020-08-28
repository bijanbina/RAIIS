#include "re_win.h"

ReWin::ReWin()
{

}

void ReWin::buttonAPressed()
{
    qDebug() << "Client: Go Next Page";
    system("xdotool key Right &");
}

void ReWin::buttonBPressed()
{
    qDebug() << "Client: Go Previous Page";
    system("xdotool key Left");
}

void ReWin::buttonXPressed()
{
    qDebug() << "Client: Go To Sleep";
    system("xdotool key Left &");
}

void ReWin::buttonYPressed()
{
    qDebug() << "Change Workspace";
    system("xdotool key Left &");
}

void ReWin::buttonL1Pressed()
{
    qDebug() << "Reset F";
    system("xdotool key Left &");
}

void ReWin::buttonL2Pressed()
{
    qDebug() << "Slower";
    system("xdotool mousemove_relative 0 -20 &");
}

void ReWin::buttonR1Pressed()
{
//    qDebug() << "Faster";
//#ifdef __linux__
//       system("xdotool mousemove_relative 0 -20");
//#endif
}

void ReWin::buttonR2Pressed()
{
    qDebug() << "Faster";
    system("xdotool mousemove_relative 0 20 &");
}

void ReWin::buttonLAxisRight()
{

}

void ReWin::buttonLAxisLeft()
{

}

void ReWin::buttonLAxisUp()
{

}

void ReWin::buttonLAxisDown()
{

}

void ReWin::buttonRAxisRight()
{

}

void ReWin::buttonRAxisLeft()
{

}

void ReWin::buttonRAxisUp()
{

}

void ReWin::buttonRAxisDown()
{

}

void ReWin::buttonStartChanged()
{
    qDebug() << "Enable autoscroll";
    system("xdotool key Menu");
    system("xdotool key Up");
    system("xdotool key Up");
    system("xdotool key Up");
    system("xdotool key Return");
}

void ReWin::buttonSelectChanged()
{
    qDebug() << "Enable autoscroll";
    system("xdotool key Escape &");
}

void ReWin::buttonDownChanged()
{
    qDebug() << "Down workspace";
    system("xdotool set_desktop --relative 1 &");
}

void ReWin::buttonUpChanged()
{
    qDebug() << "Up workspace";
    system("xdotool set_desktop --relative 4 &");
}

void ReWin::buttonRightChanged()
{
    qDebug() << "Next Window";
    system("xdotool key Alt+Escape &");
}

void ReWin::buttonLeftChanged()
{
    qDebug() << "Previous Window";
    system("xdotool key Shift+Alt+Escape &");
}



