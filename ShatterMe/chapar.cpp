#include "chapar.h"

chapar::chapar(QObject *parent) : QObject(parent)
{
    channel = new QSerialPort(this);
    openSerialPort();
    connect(channel,SIGNAL(readyRead()),this,SLOT(updateData()));
    timer = new QTimer(this);
    //channel->write("12\n");
    connect(timer,SIGNAL(timeout()),this,SLOT(timout_reach()));
    buffer_size = 0;
    sendRequest();
    timer->setInterval(TIMOUT_DELAY);
    //timout_reach();
}

void chapar::openSerialPort()
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


void chapar::updateData()
{
    QByteArray data;
    data = channel->readAll();
    buffer[buffer_size] = *data.data();
    qDebug() << QString("receive %1").arg(data.data() , 0, 16);
    buffer_size += data.size();
    timer->start(TIMOUT_DELAY);
}

void chapar::timout_reach()
{
    qDebug() << QString("timeout reached, buffer length is %1").arg(buffer_size);
    qDebug() << QString("%1").arg(timer->interval());
    timer->stop();
    if (buffer_size > 0)
    {
        printf("proccess ");
        int i;
        for ( i = 0 ; i < PACKET_LEN ; i++ )
        {
            printf ("%02x ",(int)(buffer[i] & 0xFF));
        }
        printf ("\n");
        int temp = buffer[3] + 255 * buffer[4];
        QString command = "/usr/local/bin/snmpset -v2c -c tutset 192.168.88.110 NET-SNMP-TUTORIAL-MIB::nstAgentModuleObject.0 = ";
        command.append(QString("%1").arg(temp));

        //temp
        //humedity
        //setpoint

        qDebug() << QString("run %1").arg(command);
        getStrCommand(command);
        buffer_size = 0;
        *buffer = 0;
    }

    sendRequest();
}

chapar::~chapar()
{
    if(channel->isOpen())
    {
        channel->close();
    }
}



void chapar::sendRequest()
{
    //send request
    char send_command[100];
    send_command[0] = 'R';
    send_command[1] = 1;
    send_command[2] = 0x1F;
    send_command[3] = 0;
    send_command[4] = 0;
    send_command[5] = 0;
    send_command[6] = 0;
    send_command[7] = 0x2D;//MakeCRC(send_command);
    send_command[0] = 0;//MakeCRC(send_command);

    qInfo() << QString("send request");
    timer->start(TIMOUT_DELAY);
    channel->write(send_command,PACKET_LEN);
}
