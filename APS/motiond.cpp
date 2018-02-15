#include "motiond.h"

motiond::motiond(QObject *ui, QObject *parent) : QObject(parent)
{
    root = ui;
}

void motiond::dataready(QByteArray data)
{
    char message[300];
    sprintf(message,"GYRO: %.2x %.2x %.2x",
            data.at(3)&0xff, data.at(4)&0xff, data.at(5)&0xff);
    QQmlProperty::write(root, "gyro_str", message);
    sprintf(message,"MAG: %.2x %.2x %.2x",
            data.at(6)&0xff, data.at(7)&0xff, data.at(8)&0xff);
    QQmlProperty::write(root, "mag_str", message );
    sprintf(message,"AUX: %.2x %.2x %.2x",
            data.at(0)&0xff, data.at(1)&0xff, data.at(2)&0xff);
    QQmlProperty::write(root, "aux_str", message);
    //QQmlProperty::write(root, "acc_str", word);
}
