#include "blue_driver.h"

blue_driver::blue_driver(motiond *ch, QObject *parent) : QObject(parent)
{
    channel = ch;
    controller = new QLowEnergyController(QBluetoothAddress("34:81:F4:2E:C1:83"));
    controller->setRemoteAddressType(QLowEnergyController::PublicAddress);

    controller->connect(controller,SIGNAL(connected()),this,SLOT(connected()));
    controller->connect(controller,SIGNAL(discoveryFinished()),this,SLOT(service_discovered()));
    controller->connect(controller,SIGNAL(error(QLowEnergyController::Error)),this,SLOT(get_error(QLowEnergyController::Error)));
    controller->connect (controller,SIGNAL(disconnected()),
                           this,SLOT(disconnected()));

    controller->connectToDevice();
}

void blue_driver::connected()
{
    qDebug() << "We are happy to say that connecting process was such a success";
    controller->discoverServices();
}

void blue_driver::disconnected()
{
    qDebug() << "We are sorry to say the connection gets disconnected";
    controller->connectToDevice();
}

void blue_driver::service_discovered()
{
    qDebug() << "service discovery just finished";
    m_service = controller->createServiceObject(QBluetoothUuid(QString("49535343-fe7d-4ae5-8fa9-9fafd205e455")));
    m_service->connect(m_service, SIGNAL(stateChanged(QLowEnergyService::ServiceState)),
            this, SLOT(service_ready(QLowEnergyService::ServiceState)));
    m_service->discoverDetails();
}

void blue_driver::service_ready(QLowEnergyService::ServiceState state)
{
    if (state == QLowEnergyService::ServiceDiscovered)
    {
        qDebug() << "service charactaristics discovered";
        m_characteristics = m_service->characteristic(QBluetoothUuid(QString("49535343-1e4d-4bd9-ba61-23c647249616")));

        qDebug()  << m_characteristics.isValid() << m_characteristics.properties();
        qDebug()  << m_characteristics.descriptors().count() << m_characteristics.descriptors().at(0).uuid() <<
                     m_characteristics.descriptors().at(0).type()  << m_characteristics.descriptors().at(0).name();

        QLowEnergyDescriptor notification = m_characteristics.descriptor(
                     QBluetoothUuid::ClientCharacteristicConfiguration);
        if (!notification.isValid())
        {
            qDebug() << "No notification detected";
            return;
        }

        m_service->connect(m_service,SIGNAL(characteristicChanged(QLowEnergyCharacteristic,QByteArray)),
                           this,SLOT(data_ready(QLowEnergyCharacteristic,QByteArray)));

        //Enable Notifiaction
        m_service->writeDescriptor(notification, QByteArray::fromHex("0100"));
        m_service->writeCharacteristic(m_characteristics,QByteArray("start"),QLowEnergyService::WriteWithoutResponse);
        //m_service->readCharacteristic(m_characteristics);
    }
    else
    {
        qDebug() << state;
    }
}

void blue_driver::get_error(QLowEnergyController::Error error)
{
    qDebug() << error;
}

void blue_driver::data_ready(QLowEnergyCharacteristic ch,QByteArray data)
{
    //uint *rx_data = (uint *)data.at(0);
    /*char message[300];
    sprintf(message,"AUX: %.2x %.2x %.2x GYRO: %.2x %.2x %.2x MAG: %.2x %.2x %.2x            SIZE: %d",
            data.at(0)&0xff, data.at(1)&0xff, data.at(2)&0xff,
            data.at(3)&0xff, data.at(4)&0xff, data.at(5)&0xff,
            data.at(6)&0xff, data.at(7)&0xff, data.at(8)&0xff, data.size());
    qInfo() << message;*/

    channel->dataready(data);
}
