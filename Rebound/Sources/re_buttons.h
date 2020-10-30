 #ifndef RE_BUTTONS_H
#define RE_BUTTONS_H

#include <QObject>
#include <QDebug>
#include "backend.h"
#include "re_state.h"

#ifdef _WIN32
    #include <windows.h>
#elif __linux__
#include "re_x11.h"
#include <QTimer>
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

#ifdef __linux__
private slots:
    void tab_timeout();
#endif

private:
    QObject *ui;
    ReState *state;

#ifdef __linux__
    QTimer  *timer_tab;
#endif
};

#endif // RE_BUTTONS_H
