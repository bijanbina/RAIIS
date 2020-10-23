#ifndef RE_RAXIS_H
#define RE_RAXIS_H

#include <QObject>
#include <QDebug>
#include "backend.h"
#include "re_state.h"

#ifdef _WIN32
    #include <windows.h>
#endif

class ReRAxis: public QObject
{
    Q_OBJECT

public:
    ReRAxis(QObject *item, ReState *st, QObject *parent = 0);

public slots:
    void buttonRight();
    void buttonLeft();
    void buttonUp();
    void buttonDown();

private:
    QObject *ui;
    ReState *state;
};

#endif // RE_RAXIS_H
