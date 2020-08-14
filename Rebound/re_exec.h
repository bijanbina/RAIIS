#ifndef RE_EXEC_H
#define RE_EXEC_H

#include <QObject>
#include <QDebug>
#include "backend.h"

class ReExec
{
public:
    ReExec();

    void buttonAPressed();
    void buttonBPressed();
    void buttonXPressed();
    void buttonYPressed();

    void buttonL1Pressed();
    void buttonL2Pressed();
    void buttonR1Pressed();
    void buttonR2Pressed();

    //Left Analog Axis
    void buttonLAxisRight();
    void buttonLAxisLeft();
    void buttonLAxisUp();
    void buttonLAxisDown();

    //Right Analog Axis
    void buttonRAxisRight();
    void buttonRAxisLeft();
    void buttonRAxisUp();
    void buttonRAxisDown();

    void buttonStartChanged();
    void buttonSelectChanged();

    void buttonDownChanged();
    void buttonUpChanged();
    void buttonRightChanged();
    void buttonLeftChanged();
};

#endif // RE_EXEC_H
