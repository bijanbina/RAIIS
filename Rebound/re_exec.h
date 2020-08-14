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

    void buttonAxisLxChanged(double);
    void buttonAxisLyChanged(double);
    void buttonAxisRxChanged(double);
    void buttonAxisRyChanged(double);
    void buttonStartChanged();
    void buttonSelectChanged();

    void buttonDownChanged();
    void buttonUpChanged();
    void buttonRightChanged();
    void buttonLeftChanged();
};

#endif // RE_EXEC_H
