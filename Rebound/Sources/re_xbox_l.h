#ifndef Re_XBOX_L
#define Re_XBOX_L

#include <QString>
#include <QObject>
#include <QVector>
#include <stdio.h>
#include <stdlib.h>
#include <QTimer>
#include <QQmlProperty>
#include <QSocketNotifier>
#include <QFile>
#include <QDebug>
#include "backend.h"
#include "re_keycode.h"
#include "re_client.h"

class ReXboxL : public QObject
{
    Q_OBJECT

public:
    explicit ReXboxL(QObject *item, QObject *parent = 0);
    ~ReXboxL();

signals:
    void errorConnection();

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

    void readyData();

signals:
    void buttonAPressed();
    void buttonBPressed();
    void buttonXPressed();
    void buttonYPressed();

    void buttonL1Pressed();
    void buttonL2Pressed();
    void buttonR1Pressed();
    void buttonR2Pressed();

    //Left Analog Axis
    void buttonLAxisRight();
    void buttonLAxisLeft();
    void buttonLAxisUp();
    void buttonLAxisDown();

    //Right Analog Axis
    void buttonRAxisRight();
    void buttonRAxisLeft();
    void buttonRAxisUp();
    void buttonRAxisDown();

    void buttonStartPressed();
    void buttonSelectPressed();
    void buttonGuidePressed();

    void buttonDownPressed();
    void buttonUpPressed();
    void buttonRightPressed();
    void buttonLeftPressed();

private slots:
    void keyTcpRead(QString key);

private:
    void keyParser(QString key, int value);

    QVector<QString> stack;
    int code;
    char code_char[4];

    QString message;
    char charBuffer;
    bool isBufferEmpty;
    bool commandMode;
    int commandIndex;
    short commandByte;

    double last_la_x = 0; //last left axis x value
    double last_la_y = 0; //last left axis y value
    double last_ra_x = 0; //last right axis x value
    double last_ra_y = 0; //last right axis y value

#ifdef __linux__
    ReClient *client;
#endif

    QObject         *ui;
    QTimer          *std_timer;
    QSocketNotifier *stdin_notify;
    QFile           *stdin_file;
};

#endif // Re_XBOX_L
