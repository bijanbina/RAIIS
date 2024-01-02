#ifndef RE_LAXIS_H
#define RE_LAXIS_H

#include <QObject>
#include "backend.h"
#include "re_state_old.h"

#ifdef _WIN32
    #include <windows.h>
#endif

class ReLAxis: public QObject
{
    Q_OBJECT

public:
    ReLAxis(QObject *item, ReStateOld *st, QObject *parent = 0);

public slots:
    void buttonRightPressed();
    void buttonLeftPressed();
    void buttonUpPressed();
    void buttonDownPressed();

private:
    QObject *ui;
    ReStateOld *state;
};

#endif // RE_LAXIS_H
