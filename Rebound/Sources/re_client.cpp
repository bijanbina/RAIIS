#include "re_client.h"
#include <string.h>
#include "QThread"

ReClient::ReClient(QObject *item, QObject *parent) : QObject(parent)
{
    //init
    ui = item;
    char_buffer = '0';
    is_buffer_empty = true;

    connect(&tcp_client, SIGNAL(connected()), this, SLOT(connected()));

    timer = new QTimer;
//    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(start()));
    timer->start(RE_TIMEOUT);
    start();
}

ReClient::~ReClient()
{
}

void ReClient::startTransfer(const char* command)
{
    if( connection )
    {
        connection->write(command);
    }
}

void ReClient::displayError()
{
    qDebug() << "Network error The following error occurred:"
             << tcp_client.errorString();
    tcp_client.close();
    if( !timer->isActive() )
    {
        timer->start(RE_TIMEOUT);
        qDebug() << "Timer start";
    }
    emit errorConnection();
}

void ReClient::connected()
{
    qDebug() << "Client: Connected";
    connection = new ReConnection(&tcp_client);
    connect(connection, SIGNAL(clientReadyRead(QString)),
            this, SLOT(readyRead(QString)));
    connect(connection, SIGNAL(clientDisconnected()),
            this, SLOT(disconnected()));
    connect(connection, SIGNAL(clientError()),
            this, SLOT(displayError()));
//    timer->stop();
}

void ReClient::disconnected()
{
//    QMetaObject::invokeMethod(root, "set_disconnected");
//    m_wakeLock.callMethod<void>("release", "()V");
//    disconnect((&tcpClient, SIGNAL(readyRead()), this, SLOT(readyRead())));
    if ( !timer->isActive() )
    {
        timer->start(RE_TIMEOUT);
        qDebug() << "Client: Timer start";
    }
    qDebug() << "Client: Disconnected";
}

//TimerTick
void ReClient::start()
{
    if( tcp_client.isOpen()==0 )
    {
        qDebug() << "TimerTick connecting to: " << RE_IP << RE_PORT;
        tcp_client.connectToHost(QHostAddress(RE_IP), RE_PORT );
    }
    else if( tcp_client.state()==QAbstractSocket::ConnectingState )
    {
        qDebug() << "TimerTick, Connecting";
//        tcpClient.close();
//        tcpClient.connectToHost(QHostAddress(RE_IP), RE_PORT );
    }
    else if( tcp_client.state()!=QAbstractSocket::ConnectedState )
    {
        qDebug() << "TimerTick State:" << tcp_client.state();
    }
}

void ReClient::sendBuffer()
{
    if( !is_buffer_empty )
    {
        char send_buffer[10];
        qDebug() << "Joystick: " << char_buffer;
        sprintf(send_buffer,"%c", char_buffer);
        is_buffer_empty = true;
        startTransfer(send_buffer);
    }
    else
    {
//        char send_buffer[20];
//        qDebug() << "Joystick: " << char_buffer;
//        sprintf(send_buffer,"%c", 'b');
//        is_buffer_empty = true;
//        startTransfer(sendBuffer);
    }
}

void ReClient::readyRead(QString read_data)
{
   if( read_data.size() )
   {
       qDebug() <<  "Client: Received=" << read_data << read_data.size();
       emit newKey(read_data);
   }

}

// redundant size parameter, remove it
void ReClient::sendData(const char *data, int size)
{
    if ( connection )
    {
        connection->write(data);
    }
}
