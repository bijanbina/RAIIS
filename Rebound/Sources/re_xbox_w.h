#ifndef RE_WIN_H
#define RE_WIN_H

#include <QObject>
#include "re_server.h"
#include "re_execw.h"
#ifdef _WIN32
#include <QGamepad>
#include "re_xbox_win32.h"
#endif


class ReXboxW : public QObject
{
    Q_OBJECT

public:
    explicit ReXboxW(QObject *item, int native, QObject *parent = 0);
    ~ReXboxW();

public slots:
    void buttonAChanged(bool);
    void buttonBChanged(bool);
    void buttonXChanged(bool);
    void buttonYChanged(bool);

    void buttonL1Changed(bool);
    void buttonL2Changed(double);
    void buttonL3Changed(bool);
    void buttonR1Changed(bool);
    void buttonR2Changed(double);
    void buttonR3Changed(bool);

    void buttonAxisLxChanged(double);
    void buttonAxisLyChanged(double);
    void buttonAxisRxChanged(double);
    void buttonAxisRyChanged(double);

    void buttonStartChanged(bool);
    void buttonSelectChanged(bool);
    void buttonCenterChanged(bool);
    void buttonGuideChanged(bool);

    void buttonLeftChanged(bool);
    void buttonRightChanged(bool);
    void buttonUpChanged(bool);
    void buttonDownChanged(bool);

private:
    QObject  *ui;
    ReServer *tcp;
    QGamepad *pad;
    ReExecW  *exec;

    int isNative;

    double last_la_x = 0; //last left axis x value
    double last_la_y = 0; //last left axis y value
    double last_ra_x = 0; //last right axis x value
    double last_ra_y = 0; //last right axis y value

#ifdef _WIN32
    ReXboxWin32 *backup;
#endif

};

#endif // RE_WIN_H
