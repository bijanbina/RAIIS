#ifndef RE_LAXIS_H
#define RE_LAXIS_H

#include <QObject>
#include "backend.h"
#include "re_state.h"

#ifdef _WIN32
    #include <windows.h>
#endif

class ReLAxis: public QObject
{
    Q_OBJECT

public:
    ReLAxis(QObject *item, ReState *st, QObject *parent = 0);

public slots:
    void buttonRight();
    void buttonLeft();
    void buttonUp();
    void buttonDown();

private:
    QObject *ui;
    ReState *state;
};

#endif // RE_LAXIS_H
