#ifndef CHAPER_H
#define CHAPER_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>

#define PORT_NAME "ttyUSB0"
#define BAUD_RATE QSerialPort::Baud9600
#define DATA_BITS QSerialPort::Data8
#define PARITY    QSerialPort::NoParity
#define STOP_BITS QSerialPort::OneStop
#define FLOW_CONT QSerialPort::NoFlowControl

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

private:
    void openSerialPort();
    QSerialPort *channel;
    QString getStrCommand(QString command);



    QString buffer;
};

#endif // CHAPER_H
