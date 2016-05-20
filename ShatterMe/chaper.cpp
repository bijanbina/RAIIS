#include "chaper.h"

chaper::chaper(QObject *parent) : QObject(parent)
{
    channel = new QSerialPort(this);
    openSerialPort();
    connect(channel,SIGNAL(readyRead()),this,SLOT(updateData()));
    channel->write("12\n");
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
    if (*data.data() == '\n')
    {
        bool ok;
        int temp = QString(buffer).toInt(&ok);
        if (ok)
        {
            qInfo() << QString("set temp to %1").arg(temp);
            QString command = "snmpset -v2c -c tutset localhost NET-SNMP-TUTORIAL-MIB::nstAgentModuleObject.0 = ";
            command.append(buffer);
            //qInfo() << QString("run %1").arg(command);
            getStrCommand(command);
        }
        else
        {
            qCritical() << "Error : " << "Entered value is not a integer";
        }
        buffer = "";
    }
    else
    {
        buffer.append(data);
        qInfo() << QString("receive %1").arg(data.data());
    }
}

chaper::~chaper()
{
    if(channel->isOpen())
    {
        channel->close();
    }
}



QString chaper::getStrCommand(QString command)
{
    FILE *fp;
    QString returnData;

    char path[1035];

    /* Open the command for reading. */
    fp = popen(command.toStdString().c_str(), "r");

    if (fp == NULL) {
      printf("Failed to run command\n" );
      return returnData;
    }

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
      returnData = QString(path);
    }

    returnData.remove('\n');

    /* close */
    pclose(fp);
    return returnData;
}
