#include "motiond.h"

motiond::motiond(QObject *ui, QObject *parent) : QObject(parent)
{
    root = ui;
}

void motiond::dataready(QByteArray data)
{
    char message[300];
    float mag_x;
    float mag_y;
    float mag_z;

    float gyro_x;
    float gyro_y;
    float gyro_z;

    float aux_x;
    float aux_y;
    float aux_z;

    gyro_x = data.at(3)&0xff;
    gyro_x = data.at(4)&0xff;
    gyro_x = data.at(5)&0xff;

    QQmlProperty::write(root, "gyro_x", message);
    QQmlProperty::write(root, "gyro_x", message);
    QQmlProperty::write(root, "gyro_x", message);

    mag_x = data.at(6)&0xff;
    mag_y = data.at(7)&0xff;
    mag_z = data.at(8)&0xff;

    QQmlProperty::write(root, "mag_x", mag_x);
    QQmlProperty::write(root, "mag_y", mag_y);
    QQmlProperty::write(root, "mag_z", mag_z);

    aux_x = data.at(0)&0xff;
    aux_y = data.at(1)&0xff;
    aux_z = data.at(2)&0xff;

    QQmlProperty::write(root, "aux_x", aux_x);
    QQmlProperty::write(root, "aux_y", aux_y);
    QQmlProperty::write(root, "aux_z", aux_z);
}
