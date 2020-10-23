#ifndef ReNative_H
#define ReNative_H

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

#ifdef __linux__
#include "re_exec.h"
#endif

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
    ReExec *exec;
#endif

    QObject         *ui;
    QTimer          *std_timer;
    QSocketNotifier *stdin_notify;
    QFile           *stdin_file;
};

#endif // ReNative_H
