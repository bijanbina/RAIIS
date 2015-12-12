#include "grid.h"
#include <string.h>
#include <QtMath>


Grid::Grid(QObject *parent) : QObject(parent)
{
    port->setPortName("/dev/ttyUSB0");

    bool status = port->open(QIODevice::ReadWrite);
    if (status){
        port->setBaudRate(QSerialPort::Baud38400,QSerialPort::AllDirections);
        port->setDataBits(QSerialPort::Data8);
        port->setStopBits(QSerialPort::OneStop);
        port->setFlowControl(QSerialPort::NoFlowControl);
        port->setParity(QSerialPort::EvenParity);
        connect(port,SIGNAL(readyRead()),this,SLOT(on_dataReady()));
        qDebug() << "Device connected";
    }
    else
    {
        qDebug() << "Connection failed";
        qDebug() << "Error code: " << port->error();
        port->close();
    }

    y_last = 0.0;
    x_last = 0.0;
}

Grid::~Grid()
{

}

void Grid::pressedSlot(qreal x, qreal y)
{

    int x_send = qFloor(x_last + (x - 0.5) * SCREEN_WIDTH);
    int y_send = qFloor(y_last + (y - 0.5) * SCREEN_HEIGHT);

    qDebug() << (x - x_last) << "\t" << x_last;

    qDebug() << "x: " << x << "y: " << y << "\t pressed\t" << "x send: " <<
                x_send << "y send: " << y_send;

    if ( x_send < 0 || y_send < 0  || x_send > X_MAX || y_send > Y_MAX)
    {
        qDebug() << "Entered Dead Zone!!!";
        return;
    }

    char writeBuffer[WRITE_BUFFER_LENGTH];
    sprintf(writeBuffer,"%d %d\n",x_send,y_send);
    qint64 bytesWritten = port->write(writeBuffer);

    qDebug() << bytesWritten << "is written.";

    x_last += (x - 0.5) * SCREEN_WIDTH;
    y_last += (y - 0.5) * SCREEN_HEIGHT;

}

void Grid::releaseSlot(qreal x, qreal y)
{
    int x_send = qFloor(x_last + (x - 0.5) * SCREEN_WIDTH);
    int y_send = qFloor(y_last + (y - 0.5) * SCREEN_HEIGHT);


    qDebug() << "x: " << x << "y: " << y << "\t pressed\t" << "x send: " <<
                x_send << "y send: " << y_send;

    if ( x_send < 0 || y_send < 0  || x_send > X_MAX || y_send > Y_MAX)
    {
        qDebug() << "Entered Dead Zone!!!";
        return;
    }

    char writeBuffer[WRITE_BUFFER_LENGTH];
    sprintf(writeBuffer,"%d %d\n",x_send,y_send);
    qint64 bytesWritten = port->write(writeBuffer);

    qDebug()<<bytesWritten << "is written.";

    x_last += (x - 0.5) * SCREEN_WIDTH;
    y_last += (y - 0.5) * SCREEN_HEIGHT;
}

void Grid::on_dataReady()
{
    readData += QString(port->readAll());
    //qDebug()<<readData;
}
