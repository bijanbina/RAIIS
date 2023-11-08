#include "re_server.h"
#include <string.h>

#define JOYSTICK_DELAY 100

ReServer::ReServer(ReState *st, QObject *parent) : QObject(parent)
{
    //init
    state = st;
    charBuffer = '0';
    isBufferEmpty = true;
    commandMode=false;
    connection_socket = NULL;

    live = new QTimer;
    watchdog = new QTimer;
    bufferTimer = new QTimer;
    bufferTimer->setSingleShot(true);
//    connect(bufferTimer, SIGNAL(timeout()), this, SLOT(sendBuffer()));
//    bufferTimer->setInterval(JOYSTICK_DELAY);
    connect(watchdog, SIGNAL(timeout()), this, SLOT(watchdog_timeout()));
    connect(live, SIGNAL(timeout()), this, SLOT(live_timeout()));

    server = new QTcpServer;
    connect(server, SIGNAL(newConnection()),
            this, SLOT(acceptConnection()));

    //server->listen(QHostAddress("127.0.0.1"), RE_PORT);
    if(server->listen(QHostAddress::Any, RE_PORT))
    {
        qDebug() << "Server created on port " << RE_PORT;
    }
    else
    {
        qDebug() << "Server failed";
        qDebug() << "Error message is:" << server->errorString();
    }
}

ReServer::~ReServer()
{
    qDebug() << "Closing Server";
    server->close();
    if( connection_socket )
    {
        if( connection_socket->isOpen() )
        {
            connection_socket->close();
        }
    }
}

void ReServer::acceptConnection()
{
    qDebug() << "Server: Accepted connection";
    connection_socket = server->nextPendingConnection();
    connection_socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    connect(connection_socket, SIGNAL(readyRead()),
            this, SLOT(readyRead()));
    connect(connection_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    live->start(RE_LIVE);
    watchdog->start(RE_WATCHDOG);
    emit clientConnected();
}

void ReServer::watchdog_timeout()
{
//    bytesReceived += (int)connection_socket->bytesAvailable();
    qDebug() << "Watchdog: Miss Window" ;
    connection_socket->close();

    if( connection_socket->state() != QAbstractSocket::UnconnectedState )
    {
        int success = connection_socket->waitForDisconnected();

        if( success )
        {
            qDebug() << "Watchdog: Disconnected successfully" ;
        }
        else
        {
            qDebug() << "Watchdog: Fuck Happened" ;
        }
    }
    else
    {
        qDebug() << "Watchdog: Disconnected successfully" ;
    }
    live->stop();
    watchdog->stop();
    delete connection_socket;
    connection_socket = NULL;
    emit clientDisconnected();

//    qDebug() << QString("Ack, Receive Byte: %1").arg(bytesReceived);
//    connection_socket->write("a",1);
//    connection_socket->waitForBytesWritten();
}

void ReServer::live_timeout()
{
    if(connection_socket->isOpen())
    {
        if(connection_socket->state() == QAbstractSocket::ConnectedState)
        {
            int byte_count = connection_socket->write("Live");
            connection_socket->waitForBytesWritten(50);

            if( byte_count!= 4)
            {
                qDebug() << "Client: live, Fuck Happened" << byte_count;
            }
        }
        else
        {
            qDebug() << "Client: live, not connected, State:" << connection_socket->state();
        }
    }
    else
    {
        qDebug() << "Client: live, tcpClient is closed??";
    }
}

void ReServer::readyRead()
{
    QByteArray data = connection_socket->readAll();
    if(data.length() == 4)
    {
        watchdog->start(RE_WATCHDOG);
    }
    else if (data.contains("Live"))
    {
        qDebug() << "Server: Misterious Live" << data;
        watchdog->start(RE_WATCHDOG);
        data.replace("Live", "");
    }
    else
    {
        qDebug() << "Server: Single watchdog failure," << data;
    }

#ifdef _WIN32
    if( data=="M" )
    {
        ///FIXME
        emit clientReqSusspend();
//        win->buttonGuideChanged();
    }
#endif

//    qDebug() << QString("Ack, Receive Byte: %1").arg(bytesReceived);
//    connection_socket->write("a",1);
//    connection_socket->waitForBytesWritten(50);
}

void ReServer::displayError(QAbstractSocket::SocketError socketError)
 {
     if (socketError == QTcpSocket::RemoteHostClosedError)
         return;

     qDebug() <<  QString("Error Happened");
}

void ReServer::reboundSendKey(const char *data, int size)
{
    if (connection_socket)
    {
        if ( connection_socket->isOpen() )
        {
            live->start(RE_LIVE);//don't send live

            if(size == 2)
            {
                qDebug() << "Sending " << data[0] << data[1];
            }
            else
            {
                qDebug() << "Sending " << data[0];
            }

            connection_socket->write(data,size);
            connection_socket->waitForBytesWritten(50);

            qDebug() << "finisihed sending";
            live->start(RE_LIVE);//don't send live
        }
    }
}
