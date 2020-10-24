#include "re_client.h"
#include <string.h>
#include "QThread"

ReClient::ReClient(QObject *item, QObject *parent) : QObject(parent)
{
    //init
    ui = item;
    charBuffer = '0';
    isBufferEmpty = true;
    commandMode=false;

    connect(&tcpClient, SIGNAL(connected()), this, SLOT(connected()));
    connect(&tcpClient, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    live = new QTimer;
    timer = new QTimer;
    watchdog = new QTimer;
//    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(start()));
    connect(live, SIGNAL(timeout()), this, SLOT(live_timeout()));
    connect(watchdog, SIGNAL(timeout()), this, SLOT(watchdog_timeout()));
    timer->start(RE_TIMEOUT);
    start();
}

ReClient::~ReClient()
{
    tcpClient.close();
}

void ReClient::startTransfer(const char* command)
{
    int bytesToWrite = tcpClient.write(command);
}

void ReClient::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    qDebug() << tr("Network error") << tr("The following error occurred: %1.").arg(tcpClient.errorString());
    tcpClient.close();
    if ( !(timer->isActive()) )
    {
        timer->start(RE_TIMEOUT);
        qDebug() << "Timer start";
    }
    emit errorConnection();

}

void ReClient::connected()
{
    qDebug() << "Client: Connected";
    tcpClient.setSocketOption(QAbstractSocket::LowDelayOption, 1);
    connect(&tcpClient, SIGNAL(readyRead()), this, SLOT(readyRead()));
    watchdog->start(RE_WATCHDOG);
    live->start(RE_Live);

//    timer->stop();
}

void ReClient::disconnected()
{
//    QMetaObject::invokeMethod(root, "set_disconnected");
//    m_wakeLock.callMethod<void>("release", "()V");
    watchdog->stop();
    live->stop();
    tcpClient.close();
//    disconnect((&tcpClient, SIGNAL(readyRead()), this, SLOT(readyRead())));

    if ( !(timer->isActive()) )
    {
        timer->start(RE_TIMEOUT);
        qDebug() << "Client: Timer start";
    }
    qDebug() << "Client: Disconnected";
}

//Watchdog TimerTick
void ReClient::watchdog_timeout()
{
    if(tcpClient.isOpen())
    {
        qDebug() << "Client: watchdog shit happened:" << tcpClient.state();
        disconnected();
    }
    else
    {
        qDebug() << "Client: watchdog, tcpClient is closed??";
    }
}

//Live TimerTick
void ReClient::live_timeout()
{
    if(tcpClient.isOpen())
    {
        if(tcpClient.state() == QAbstractSocket::ConnectedState)
        {
            int byte_count = tcpClient.write("Live");
            tcpClient.waitForBytesWritten(50);

            if( byte_count!= 4)
            {
                qDebug() << "Client: live, Fuck Happened" << byte_count;
            }
        }
        else
        {
            qDebug() << "Client: live, not connected, State:" << tcpClient.state();
        }
    }
    else
    {
        qDebug() << "Client: live, tcpClient is closed??";
    }
}

//TimerTick
void ReClient::start()
{
    if(!tcpClient.isOpen())
    {
        qDebug() << "TimerTick, connecting to: " << RE_IP << RE_PORT;
        tcpClient.connectToHost(QHostAddress(RE_IP), RE_PORT );
    }
    else if(tcpClient.state() == QAbstractSocket::ConnectingState)
    {
        qDebug() << "TimerTick, Connecting";
//        tcpClient.close();
//        tcpClient.connectToHost(QHostAddress(RE_IP), RE_PORT );
    }
    else if(tcpClient.state() != QAbstractSocket::ConnectedState)
    {
        qDebug() << "TimerTick State:" << tcpClient.state();
    }
}

void ReClient::sendBuffer()
{
    if (!isBufferEmpty)
    {
        char sendBuffer[10];
        qDebug() << "Joystick: " << charBuffer;
        sprintf(sendBuffer,"%c", charBuffer);
        isBufferEmpty = true;
        startTransfer(sendBuffer);
    }
    else
    {
//        char sendBuffer[20];
//        qDebug() << "Joystick: " << charBuffer;
//        sprintf(sendBuffer,"%c", 'b');
//        isBufferEmpty = true;
//        startTransfer(sendBuffer);
    }
}

void ReClient::readyRead()
{
   QString read_data = tcpClient.readAll();
   if( read_data=="Live" )
   {
       watchdog->start(RE_WATCHDOG);
       return;
   }

   if( read_data.size()==0 )
   {
       return;
   }

   watchdog->start(RE_WATCHDOG);

   if( read_data.contains("Live") )
   {
       qDebug() <<  "Client: Shitty Live=" << read_data << read_data.size();
       read_data.replace("Live", "");
   }

   if( read_data.size() )
   {
       qDebug() <<  "Client: Received=" << read_data << read_data.size();
   }

   emit newKey(read_data);
}

void ReClient::sendData(const char *data, int size)
{
    if ( tcpClient.isOpen() )
    {
        live->start(RE_Live);//don't send live

        if(size == 2)
        {
            qDebug() << "Sending " << data[0] << data[1];
        }
        else
        {
            qDebug() << "Sending " << data[0];
        }

        tcpClient.write(data,size);
        tcpClient.waitForBytesWritten(50);

        qDebug() << "finisihed sending";
        live->start(RE_Live);//don't send live
    }
}
