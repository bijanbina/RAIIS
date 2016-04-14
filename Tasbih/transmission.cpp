#include "transmission.h"
#include <string.h>

#define JOYSTICK_DELAY 100

Transmission::Transmission(QObject *item, QObject *parent) : QObject(parent)
{
    //init
    ui = item;
    charBuffer = '0';
    isBufferEmpty = true;
    commandMode=false;

    connect(&tcpClient, SIGNAL(connected()), this, SLOT(connected()));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    bufferTimer = new QTimer;
    bufferTimer->setSingleShot(true);
    connect(bufferTimer, SIGNAL(timeout()), this, SLOT(sendBuffer()));
    bufferTimer->setInterval(JOYSTICK_DELAY);
    start("192.168.43.100");
}



Transmission::~Transmission()
{
    tcpClient.close();
}

void Transmission::startTransfer(const char* command)
{
    int bytesToWrite = tcpClient.write(command);
}

void Transmission::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    qDebug() << tr("Network error") << tr("The following error occurred: %1.").arg(tcpClient.errorString());
    tcpClient.close();
    emit errorConnection();

}

void Transmission::connected()
{
    qDebug() << "connected";
    connect(&tcpClient, SIGNAL(readyRead()),this, SLOT(updateNumber()));

}

void Transmission::start(QString IP)
{
    qDebug() << "connecting to " << IP;
    tcpClient.connectToHost(QHostAddress(IP), TR_PORT_ADDRESS );
}

void Transmission::sendBuffer()
{
    if (!isBufferEmpty)
    {
        char sendBuffer[10];
        qDebug() << "Joystick: " << charBuffer;
        sprintf(sendBuffer,"%c", charBuffer);
        isBufferEmpty = true;
        startTransfer(sendBuffer);
    }
}

void Transmission::updateNumber()
{
    QString data = tcpClient.readAll().data();
    qDebug() << "Get:" << data;

    //QQmlProperty::write(ui, "counterNumber", "21");
    QQmlProperty::write(ui, "counterNumber", data);
}
