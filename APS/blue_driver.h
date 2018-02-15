#ifndef BLUE_DRIVER_H
#define BLUE_DRIVER_H

#include <QObject>
#include <qbluetoothglobal.h>
#include <qbluetoothlocaldevice.h>
#include <QObject>
#include <QVariant>
#include <QList>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QBluetoothServiceInfo>
#include <QDebug>
#include "motiond.h"

class blue_driver : public QObject
{
    Q_OBJECT
public:
    explicit blue_driver(motiond *ch, QObject *parent = 0);

signals:

public slots:
    void connected();
    void disconnected();
    void service_ready(QLowEnergyService::ServiceState state);
    void service_discovered();
    void get_error(QLowEnergyController::Error error);
    void data_ready(QLowEnergyCharacteristic ch,QByteArray data);

private:
    QLowEnergyController *controller;
    QLowEnergyService *m_service;
    QLowEnergyCharacteristic m_characteristics;
    motiond *channel;
    //QDebug dbg;
};

#endif // BLUE_DRIVER_H
