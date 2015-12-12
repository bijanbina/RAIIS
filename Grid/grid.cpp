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

    y_last = 0.5;
    x_last = 0.5;
}

Grid::~Grid()
{

}

void Grid::pressedSlot(qreal x, qreal y)
{
    qDebug() << "X: " << qFloor(x * X_MAX) << "Y: " << qFloor(y * Y_MAX) << "\t Pressed";
    int x_send = qFloor((x - x_last) * X_MAX);
    int y_send = qFloor((y - y_last) * Y_MAX);

    char writeBuffer[WRITE_BUFFER_LENGTH];
    sprintf(writeBuffer,"%d %d\n",x_send,y_send);
    qint64 bytesWritten = port->write(writeBuffer);

    qDebug()<<bytesWritten << "is written.";

    x_last = x;
    y_last = y;
}

void Grid::releaseSlot(qreal x, qreal y)
{
    qDebug() << "X: " << qFloor(x * X_MAX) << "Y: " << qFloor(y * Y_MAX) << "\t Released";
    int x_send = qFloor((x - x_last) * X_MAX);
    int y_send = qFloor((y - y_last) * Y_MAX);

    char writeBuffer[WRITE_BUFFER_LENGTH];
    sprintf(writeBuffer,"%d %d\n",x_send,y_send);
    qint64 bytesWritten = port->write(writeBuffer);

    qDebug()<<bytesWritten << "is written.";

    x_last = x;
    y_last = y;
}

void Grid::on_dataReady()
{
    readData += QString(port->readAll());
    //qDebug()<<readData;

}
