#ifndef RE_EXECW_H
#define RE_EXECW_H

#include <QObject>
#include <QDebug>
#include "backend.h"
#include <windows.h>

class ReExecW: public QObject
{
    Q_OBJECT

public:
    ReExecW(QObject *item, QObject *parent = 0);

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
    void buttonGuideChanged();

    void buttonDownChanged();
    void buttonUpChanged();
    void buttonRightChanged();
    void buttonLeftChanged();

    void executeAhk(QString name);
    void executeUi(QString name);

private:
    QObject *ui;
};

#endif // RE_EXECW_H
