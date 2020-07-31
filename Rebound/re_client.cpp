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
    emit errorConnection();

}

void ReClient::connected()
{
    qDebug() << "Client: Connected";
    connect(&tcpClient, SIGNAL(readyRead()), this, SLOT(readyRead()));

    timer->stop();
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

void ReClient::start()
{
//    qDebug() << "Timer tick";
    if(!tcpClient.isOpen())
    {
        qDebug() << "connecting to server: " << RE_IP << RE_PORT;
        tcpClient.connectToHost(QHostAddress(RE_IP), RE_PORT );
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
   else if( read_data=="r1" )
   {
       exec.buttonR1Pressed();
   }
   else if( read_data=="r2" )
   {
       exec.buttonR2Pressed();
   }
}
