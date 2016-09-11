#include "transmission.h"
#include <string.h>
#include <QQmlProperty>

#define JOYSTICK_DELAY 100

#define DEVICE1_IP  "192.168.1.21"
#define DEVICE2_IP  "192.168.1.22"
#define DEVICE3_IP  "192.168.1.23"
#define DEVICE4_IP  "192.168.1.24"

Transmission::Transmission(QObject *ui,QObject *parent) : QObject(parent)
{
    //init
    charBuffer = '0';
    isBufferEmpty = true;
    commandMode=false;

    connect(&tcpClient, SIGNAL(connected()), this, SLOT(connected()));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    root = ui;
}

Transmission::~Transmission()
{
    tcpClient.close();
}

int Transmission::startTransfer(const char* command)
{
    if (tcpClient.isOpen())
    {
        int bytesToWrite = tcpClient.write(command);
        return bytesToWrite;
    }
}

void Transmission::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    QString error =  QString("\nNetwork error\nThe following error occurred: %1.").arg(tcpClient.errorString());
    tof_on_screen( error );
    tcpClient.close();
    emit errorConnection();

}

void Transmission::connected()
{
    qDebug() << "connected";
    tof_on_screen( "\nconnected" );
}

void Transmission::start(QString IP)
{
    if (tcpClient.isOpen())
    {
        tcpClient.disconnect();
    }
    tcpClient.connectToHost(QHostAddress(IP), 7778 );
    qDebug() << "connecting to " << IP;
    tof_on_screen( "\nconnecting to " );
    tof_on_screen( IP );
}

void Transmission::set_lamp(int id)
{
    QString ip_address;
    switch (id)
    {
        case 0:
            ip_address = DEVICE1_IP;
            break;
        case 1:
            ip_address = DEVICE2_IP;
            break;
        case 2:
            ip_address = DEVICE3_IP;
            break;
        case 3:
            ip_address = DEVICE4_IP;
            break;
        default:
            return;
    }
    start(ip_address);
}

void Transmission::change_color(int id)
{
    ColorButtonID button_id = static_cast<ColorButtonID>(id);
    QString command;
    switch (button_id)
    {
        case GREEN_BUTTON:
            command = "3000100000";
            break;
        case BLUE_BUTTON:
            command = "3000000100";
            break;
        case RED_BUTTON:
            command = "3100000000";
            break;
    }
    startTransfer(command.toStdString().c_str());
}

void Transmission::music_random()
{
    QString command = "4";
    startTransfer(command.toStdString().c_str());
}

void Transmission::music_play()
{
    QString command = "5";
    startTransfer(command.toStdString().c_str());
}

void Transmission::tof_on_screen(QString message)
{
    QQmlProperty::write(root, "message", message);
    QMetaObject::invokeMethod(root, "tof_on_screen"); //show warning to

}
