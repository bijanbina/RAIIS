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
    coolerID = 0;
    paramID = 0;

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
    shatter_debug(QString("receive %1").arg(data.data() , 0, 16));
    buffer_size += data.size();
    timer->start(TIMOUT_DELAY);
}

void chapar::timout_reach()
{
    shatter_debug(QString("timeout reached, buffer length is %1").arg(buffer_size));
    shatter_debug(QString("%1").arg(timer->interval()));
    timer->stop();
    if (buffer_size > 0)
    {
        shatter_debug_hex("proccess ", buffer, PACKET_LEN);
        int temp = buffer[3] + 255 * buffer[4];
        QString command = "/usr/local/bin/snmpset -v2c -c tutset localhost NET-SNMP-TUTORIAL-MIB::nstAgentModuleObject.0 = ";
        command.append(QString("%1").arg(temp));

        //temp
        //humedity
        //setpoint

        shatter_debug(QString("update %1").arg(temp));
        runCommand(command);
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

    printf("%02x\n",MakeCRC(send_command));

    shatter_debug(QString("send request"));
    timer->start(TIMOUT_DELAY);
    channel->write(send_command,PACKET_LEN);

    if (coolerID < 10)
    {
        coolerID++;
    }
    else
    {
        coolerID = 0;
    }

    if (paramID < 3)
    {
        paramID++;
    }
    else
    {
        paramID = 2;
    }
}
