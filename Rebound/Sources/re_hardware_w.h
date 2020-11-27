#ifndef RE_HARDWARE_W_H
#define RE_HARDWARE_W_H

#include <QDebug>
#include <QTimer>
#include <windows.h>
#include <Setupapi.h>
#include <Devpkey.h>

#define RE_TIMER_STATE_INIT 0 //initialise mode
#define RE_TIMER_STATE_DIS0 1
#define RE_TIMER_STATE_ENB1 2
#define RE_TIMER_STATE_DIS2 3

class ReHardwareW: public QObject
{
    Q_OBJECT

public:
    ReHardwareW(QObject *parent = 0);
    void disconnectXbox();

public slots:
    void timerTimeout();

private:
    void disableXbox();
    void enableXbox();
    void setDevice(long state);

    QObject *ui;
    QTimer  *timer;
    int timer_state;
    HDEVINFO hDevInfo;
    SP_DEVINFO_DATA DeviceInfoData;
};

#endif // RE_HARDWARE_W_H
