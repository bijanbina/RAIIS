#ifndef RE_RAXIS_H
#define RE_RAXIS_H

#include <QObject>
#include <QDebug>
#include "backend.h"

#ifdef _WIN32
    #include <windows.h>
#endif

class ReRAxis: public QObject
{
    Q_OBJECT

public:
    ReRAxis(QObject *item, QObject *parent = 0);

public slots:
    void buttonRight();
    void buttonLeft();
    void buttonUp();
    void buttonDown();

private:
    QObject *ui;
};

#endif // RE_RAXIS_H
