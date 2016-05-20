#include "chaper.h"

chaper::chaper(QObject *parent) : QObject(parent)
{
    channel = new QSerialPort(this);
    openSerialPort();
    connect(channel,SIGNAL(readyRead()),this,SLOT(updateData()));
}

void chaper::openSerialPort()
{
    channel->setPortName(PORT_NAME);
    channel->setBaudRate(BAUD_RATE);
    channel->setDataBits(DATA_BITS);
    channel->setParity(PARITY);
    channel->setStopBits(STOP_BITS);
    channel->setFlowControl(FLOW_CONT);


    if (channel->open(QIODevice::ReadWrite))
    {
        //console->setEnabled(true);
        qInfo() << QString("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(PORT_NAME).arg(BAUD_RATE).arg(DATA_BITS)
                          .arg(PARITY).arg(STOP_BITS).arg(FLOW_CONT);
    }
    else
    {
        qCritical() << "Error : " << channel->errorString();
    }
}


void chaper::updateData()
{
    QByteArray data;
    data = channel->read(1);
}

chaper::~chaper()
{
    if(channel->isOpen())
    {
        channel->close();
    }
}
