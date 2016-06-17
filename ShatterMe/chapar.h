#ifndef chapar_H
#define chapar_H

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
#define TIMOUT_DELAY    300
#define MAX_BUFFER_LEN  100

class chapar : public QObject
{
    Q_OBJECT

public:
    explicit chapar(QObject *parent = 0);
    void     start();
    ~chapar();

signals:

public slots:

private slots:
    void updateData();
    void timout_reach();

private:
    void sendRequest();
    void openSerialPort();

    QSerialPort *channel;
    QTimer *timer;

    char buffer[MAX_BUFFER_LEN];
    int buffer_size;

    int coolerID;
    int paramID;
};

#endif // chapar_H
