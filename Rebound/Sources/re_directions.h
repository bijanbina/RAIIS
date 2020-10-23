#ifndef RE_DIRECTIONS_H
#define RE_DIRECTIONS_H

#include <QObject>
#include <QDebug>
#include "backend.h"
#include "re_state.h"

#ifdef _WIN32
    #include <windows.h>
#endif

class ReDirections: public QObject
{
    Q_OBJECT

public:
    ReDirections(QObject *item, ReState *st, QObject *parent = 0);

public slots:
    void buttonDownPressed();
    void buttonUpPressed();
    void buttonRightPressed();
    void buttonLeftPressed();

private:
    QObject *ui;
    ReState *state;
};

#endif // RE_DIRECTIONS_H
