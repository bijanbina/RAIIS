#ifndef RE_RAXIS_H
#define RE_RAXIS_H

#include <QObject>
#include <QDebug>
#include "backend.h"
#include "re_state_old.h"

#ifdef _WIN32
    #include <windows.h>
#endif

class ReRAxis: public QObject
{
    Q_OBJECT

public:
    ReRAxis(QObject *item, ReStateOld *st, QObject *parent = 0);

public slots:
    void buttonRightPressed();
    void buttonLeftPressed();
    void buttonUpPressed();
    void buttonDownPressed();

private:
    QObject *ui;
    ReStateOld *state;
};

#endif // RE_RAXIS_H
