#ifndef RE_BUMPERS_H
#define RE_BUMPERS_H

#include <QObject>
#include <QDebug>
#include "backend.h"
#include "re_state.h"

#ifdef _WIN32
    #include <windows.h>
#endif

class ReBumpers: public QObject
{
    Q_OBJECT

public:
    ReBumpers(QObject *item, ReState *st, QObject *parent = 0);

public slots:
    void buttonL1Pressed();
    void buttonL2Pressed();
    void buttonR1Pressed();
    void buttonR2Pressed();

private:
    QObject *ui;
    ReState *state;
};

#endif // RE_BUMPERS_H
