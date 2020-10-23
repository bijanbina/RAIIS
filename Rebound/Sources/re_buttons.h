#ifndef RE_BUTTONS_H
#define RE_BUTTONS_H

#include <QObject>
#include <QDebug>
#include "backend.h"
#include "re_state.h"

#ifdef _WIN32
    #include <windows.h>
#endif

class ReButtons: public QObject
{
    Q_OBJECT

public:
    ReButtons(QObject *item, ReState *st, QObject *parent = 0);

public slots:
    void buttonAPressed();
    void buttonBPressed();
    void buttonXPressed();
    void buttonYPressed();

    void buttonStartPressed();
    void buttonSelectPressed();
    void buttonGuidePressed();

private:
    QObject *ui;
    ReState *state;
};

#endif // RE_BUTTONS_H
