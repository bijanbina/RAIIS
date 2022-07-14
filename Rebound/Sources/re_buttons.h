 #ifndef RE_BUTTONS_H
#define RE_BUTTONS_H

#include <QObject>
#include <QDebug>
#if __linux__
#include <QTimer>
#endif
#include "backend.h"
#include "re_state.h"

#ifdef _WIN32
    #include <windows.h>
    #include "re_hardware_w.h"
#endif

class ReButtons: public QObject
{
    Q_OBJECT

public:
    ReButtons(QObject *item, QObject *switcher, ReState *st, QObject *parent = 0);

public slots:
    void buttonAPressed();
    void buttonBPressed();
    void buttonXPressed();
    void buttonYPressed();

    void buttonStartPressed();
    void buttonSelectPressed();
    void buttonGuidePressed();

#ifdef __linux__
    void tab_timeout();
#endif

private:
    QObject *ui;
    QObject *uiSwitcher;
    ReState *state;

#ifdef __linux__
    QTimer  *timer_tab;
#endif
};

#endif // RE_BUTTONS_H
