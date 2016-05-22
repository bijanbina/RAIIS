#ifndef CHAPER_H
#define CHAPER_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <backend.h>


#define PORT_NAME "ttyUSB0"
#define BAUD_RATE QSerialPort::Baud115200
#define DATA_BITS QSerialPort::Data8
#define PARITY    QSerialPort::NoParity
#define STOP_BITS QSerialPort::OneStop
#define FLOW_CONT QSerialPort::NoFlowControl
#define PACKET_LEN 8
#define TIMOUT_DELAY    100
#define MAX_BUFFER_LEN  100

class chaper : public QObject
{
    Q_OBJECT

public:
    explicit chaper(QObject *parent = 0);
    ~chaper();

signals:

public slots:

private slots:
    void updateData();
    void timout_reach();

private:
    void sendRequest();
    void openSerialPort();
    short MakeCRC(char *BitString);

    QSerialPort *channel;
    QString getStrCommand(QString command);
    QTimer *timer;

    char buffer[MAX_BUFFER_LEN];
    int buffer_size;
};

#endif // CHAPER_H
