#include "chaper.h"

chaper::chaper(QObject *parent) : QObject(parent)
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
    data = channel->readAll();
    buffer[buffer_size] = *data.data();
    qInfo() << QString("receive %1").arg(data.data() , 0, 16);
    buffer_size += data.size();
    timer->start(TIMOUT_DELAY);
}

void chaper::timout_reach()
{
    qInfo() << QString("timeout reached, buffer length is %1").arg(buffer_size);
    qInfo() << QString("%1").arg(timer->interval());
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

        qInfo() << QString("run %1").arg(command);
        getStrCommand(command);
        buffer_size = 0;
        *buffer = 0;
    }

    sendRequest();
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

void chaper::sendRequest()
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

short chaper::MakeCRC(char *BitString)
   {

   /*char CRC[8];
   int  i;
   char DoInvert;
   char x=0;
   short oo=0;

   for (i=0; i<8; ++i)  CRC[i] = 0;                    // Init before calculation


   for (i=0; i<56; ++i)
      {
       if((bitreader(BitString,i))==1)
       {
        x=1;
       }
       else
       {
       x=0;
       }
      DoInvert =x ^ CRC[7];//('1'==BitString[i]) ^ CRC[7];         // XOR required?

      CRC[7] = CRC[6] ^ DoInvert;
      CRC[6] = CRC[5] ^ DoInvert;
      CRC[5] = CRC[4];
      CRC[4] = CRC[3] ^ DoInvert;
      CRC[3] = CRC[2];
      CRC[2] = CRC[1] ^ DoInvert;
      CRC[1] = CRC[0];
      CRC[0] = DoInvert;
      }

   for (i=0; i<8; ++i)
   {
    if (CRC[i]==1)
    {
    // Res[7-i]='1';
     oo=oo+1*((short)pow(2,(double)(i)));
    }
    else
    {
    // Res[7-i]='0';
    }
   }

   //Res[8] = 0;                                         // Set string terminator

   return oo;
  // return(Res);*/
}

//d5

/*char chaper::bitreader(char *string, int offset)
{
    int index = offset/8;
    qinfo() <<
}*/
