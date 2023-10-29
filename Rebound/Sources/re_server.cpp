#include "re_server.h"
#include <string.h>

#define JOYSTICK_DELAY 100

ReServer::ReServer(ReState *st, QObject *parent) : QObject(parent)
{
    //init
    state = st;
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
}

void ReServer::acceptConnection()
{
    qDebug() << "Server: Accepted connection";
    QTcpSocket *con = server->nextPendingConnection();
    connection = new ReConnection(con);

    connect(connection, SIGNAL(clientReadyRead(QString)),
            this, SLOT(readyRead(QString)));
    connect(connection, SIGNAL(clientDisconnected()),
            this, SLOT(handleDisconnect()));
    emit clientConnected();
}

void ReServer::handleDisconnect()
{
    emit clientDisconnected();
}

void ReServer::readyRead(QString data)
{
#ifdef _WIN32
    if( data=="M" )
    {
        ///FIXME
        emit clientReqSuspend();
//        win->buttonGuideChanged();
    }
#endif

//    qDebug() << QString("Ack, Receive Byte: %1").arg(bytesReceived);
//    connection_socket->write("a",1);
//    connection_socket->waitForBytesWritten(50);
}

// redundant size parameter, remove it
void ReServer::reboundSendKey(const char *data, int size)
{
    if( connection )
    {
        connection->write(data);
    }
}
