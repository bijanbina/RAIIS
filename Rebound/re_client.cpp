#include "re_client.h"
#include <string.h>

ReClient::ReClient(QObject *parent) : QObject(parent)
{
    //init
    charBuffer = '0';
    isBufferEmpty = true;
    commandMode=false;

    connect(&tcpClient, SIGNAL(connected()), this, SLOT(connected()));
    connect(&tcpClient, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    timer = new QTimer;
//    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(start()));
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
    connect(&tcpClient, SIGNAL(readyRead()), this, SLOT(readyRead()));

//    timer->stop();
}

void ReClient::disconnected()
{
//    QMetaObject::invokeMethod(root, "set_disconnected");
//    m_wakeLock.callMethod<void>("release", "()V");
    qDebug() << "Client Disconnected";
    tcpClient.close();
//    disconnect((&tcpClient, SIGNAL(readyRead()), this, SLOT(readyRead())));

    if ( !(timer->isActive()) )
    {
        timer->start(RE_TIMEOUT);
        qDebug() << "Timer start";
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
   qDebug() <<  "Client: Received=" << read_data;
   if( read_data=="a" )
   {
       exec.buttonAPressed();
   }
   else if( read_data=="b" )
   {
       exec.buttonBPressed();
   }
   else if( read_data=="c" ) //Left Axis
   {
       exec.buttonLAxisRight();
   }
   else if( read_data=="d" )
   {
       exec.buttonDownChanged();
   }
   else if( read_data=="e" ) //Left Axis
   {
       exec.buttonLAxisLeft();
   }
   else if( read_data=="f" ) //Left Axis
   {
       exec.buttonLAxisUp();
   }
   else if( read_data=="g" ) //Right Axis
   {
       exec.buttonLAxisDown();
   }
   else if( read_data=="h" ) //Right Axis
   {
       exec.buttonRAxisRight();
   }
   else if( read_data=="i" ) //Right Axis
   {
       exec.buttonRAxisLeft();
   }
   else if( read_data=="j" ) //Right Axis
   {
       exec.buttonRAxisUp();
   }
   else if( read_data=="k" ) //Right Axis
   {
       exec.buttonRAxisDown();
   }
   else if( read_data=="l" )
   {
       exec.buttonLeftChanged();
   }
   else if( read_data=="m" )
   {
       exec.buttonStartChanged();
   }
   else if( read_data=="x" )
   {
       exec.buttonXPressed();
   }
   else if( read_data=="y" )
   {
       exec.buttonYPressed();
   }
   else if( read_data=="l1" )
   {
       exec.buttonL1Pressed();
   }
   else if( read_data=="l2" )
   {
       exec.buttonL2Pressed();
   }
   else if( read_data=="r" )
   {
       exec.buttonRightChanged();
   }
   else if( read_data=="r1" )
   {
       exec.buttonR1Pressed();
   }
   else if( read_data=="r2" )
   {
       exec.buttonR2Pressed();
   }
   else if( read_data=="s" )
   {
       exec.buttonSelectChanged();
   }
   else if( read_data=="u" )
   {
       exec.buttonUpChanged();
   }
   else
   {
       qDebug() << "Get unkdown packet:" << read_data;
   }
}
