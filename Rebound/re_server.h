#ifndef ReServer_H
#define ReServer_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QObject>
#include <QVector>
#include <stdio.h>
#include <stdlib.h>
#include <QTimer>
#include <QQmlProperty>
#ifdef _WIN32
#include <QGamepad>
#include <re_xbox_win32.h>
#endif
#include "backend.h"

class ReServer : public QObject
{
    Q_OBJECT

public:
    explicit ReServer(QObject *item, QObject *parent = 0);
    ~ReServer();
signals:
    void errorConnection();

public slots:
    void acceptConnection();
    void readyRead();
    void live_timeout();
    void watchdog_timeout();
    void displayError(QAbstractSocket::SocketError socketError);
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
    void reboundSendKey(const char *data, int size);

    long bytesReceived;
    QTcpServer *server;
    QTcpSocket *connection_socket;

    QVector<QString> stack;
    int code;
    char code_char[4];

    QString message;
    char charBuffer;
    bool isBufferEmpty;
    bool commandMode;
    int commandIndex;
    short commandByte;

    QTimer *live;
    QTimer *watchdog;
    QTimer *bufferTimer;

    double last_la_x = 0; //last left axis x value
    double last_la_y = 0; //last left axis y value
    double last_ra_x = 0; //last right axis x value
    double last_ra_y = 0; //last right axis y value

#ifdef _WIN32
    QGamepad    *pad;
    ReXboxWin32 *backup;
#endif

    QObject *ui;
};

#endif // ReServer_H
