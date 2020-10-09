#ifndef RE_EXEC_H
#define RE_EXEC_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include "backend.h"
#include "re_x11.h"

class ReExec: public QObject
{
    Q_OBJECT

public:
    ReExec(QObject *item, QObject *parent = 0);

    void buttonAPressed();
    void buttonBPressed();
    void buttonXPressed();
    void buttonYPressed();

    void buttonL1Pressed();
    void buttonL2Pressed();
    void buttonL3Pressed();
    void buttonR1Pressed();
    void buttonR2Pressed();
    void buttonR3Pressed();

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
    void buttonSelectChanged(int isNative);
    void buttonCenterChanged();
    void buttonGuideChanged();

    void buttonDownChanged();
    void buttonUpChanged();
    void buttonRightChanged();
    void buttonLeftChanged();

private slots:
    void tab_timeout();

private:
    void hideUI();
    int isUiVisible();

    QObject *ui;
    QTimer  *timer_tab;
};

#endif // RE_EXEC_H
