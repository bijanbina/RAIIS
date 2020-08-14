#include "re_server.h"
#include <string.h>

#define JOYSTICK_DELAY 100

ReServer::ReServer(QObject *item, QObject *parent) : QObject(parent)
{
    //init
    ui = item;
    charBuffer = '0';
    isBufferEmpty = true;
    commandMode=false;
    connection_socket = NULL;

    pad = new QGamepad;
    connect(pad, SIGNAL(buttonAChanged(bool)),
            this, SLOT(buttonAChanged(bool)));
    connect(pad, SIGNAL(buttonBChanged(bool)),
            this, SLOT(buttonBChanged(bool)));
    connect(pad, SIGNAL(buttonXChanged(bool)),
            this, SLOT(buttonXChanged(bool)));
    connect(pad, SIGNAL(buttonYChanged(bool)),
            this, SLOT(buttonYChanged(bool)));


    connect(pad, SIGNAL(buttonL1Changed(bool)),
            this, SLOT(buttonL1Changed(bool)));
    connect(pad, SIGNAL(buttonL2Changed(double)),
            this, SLOT(buttonL2Changed(double)));
    connect(pad, SIGNAL(buttonR1Changed(bool)),
            this, SLOT(buttonR1Changed(bool)));
    connect(pad, SIGNAL(buttonR2Changed(double)),
            this, SLOT(buttonR2Changed(double)));

    connect(pad, SIGNAL(axisLeftXChanged(double)),
            this, SLOT(buttonAxisLxChanged(double)));
    connect(pad, SIGNAL(axisLeftYChanged(double)),
            this, SLOT(buttonAxisLyChanged(double)));
    connect(pad, SIGNAL(axisRightXChanged(double)),
            this, SLOT(buttonAxisRxChanged(double)));
    connect(pad, SIGNAL(axisRightXChanged(double)),
            this, SLOT(buttonAxisRxChanged(double)));

    connect(pad, SIGNAL(buttonStartChanged(bool)),
            this, SLOT(buttonStartChanged(bool)));
    connect(pad, SIGNAL(buttonSelectChanged(bool)),
            this, SLOT(buttonSelectChanged(bool)));

    connect(pad, SIGNAL(buttonLeftChanged(bool)),
            this, SLOT(buttonLeftChanged(bool)));
    connect(pad, SIGNAL(buttonRightChanged(bool)),
            this, SLOT(buttonRightChanged(bool)));
    connect(pad, SIGNAL(buttonUpChanged(bool)),
            this, SLOT(buttonUpChanged(bool)));
    connect(pad, SIGNAL(buttonDownChanged(bool)),
            this, SLOT(buttonDownChanged(bool)));
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

    bufferTimer = new QTimer;
    bufferTimer->setSingleShot(true);
//    connect(bufferTimer, SIGNAL(timeout()), this, SLOT(sendBuffer()));
//    bufferTimer->setInterval(JOYSTICK_DELAY);
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
    connect(connection_socket, SIGNAL(readyRead()),
            this, SLOT(readyRead()));
    connect(connection_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    qDebug() << "Accepted connection";
}

void ReServer::readyRead()
{
//    bytesReceived += (int)connection_socket->bytesAvailable();
    qDebug() << "Server" << connection_socket->readAll();

    qDebug() << QString("Ack, Receive Byte: %1").arg(bytesReceived);
    connection_socket->write("a",1);
    connection_socket->waitForBytesWritten();
}

void ReServer::displayError(QAbstractSocket::SocketError socketError)
 {
     if (socketError == QTcpSocket::RemoteHostClosedError)
         return;

     qDebug() <<  QString("Error Happened");
}

void ReServer::buttonAChanged(bool value)
{
    if (connection_socket)
    {
        if ( value==1 && connection_socket->isOpen() )
        {
            connection_socket->write("a",1);
            connection_socket->waitForBytesWritten();
        }
    }
}

void ReServer::buttonBChanged(bool value)
{
    if (connection_socket)
    {
        if ( value==1 && connection_socket->isOpen() )
        {
            connection_socket->write("b",1);
            connection_socket->waitForBytesWritten();
        }
    }
}

void ReServer::buttonXChanged(bool value)
{
    if (connection_socket)
    {
        if ( value==1 && connection_socket->isOpen() )
        {
            connection_socket->write("x",1);
            connection_socket->waitForBytesWritten();
        }
    }
}

void ReServer::buttonYChanged(bool value)
{
    if (connection_socket)
    {
        if ( value==1 && connection_socket->isOpen() )
        {
            connection_socket->write("y",1);
            connection_socket->waitForBytesWritten();
        }
    }
}

void ReServer::buttonL1Changed(bool value)
{
    if (connection_socket)
    {
        if ( value==1 && connection_socket->isOpen() )
        {
            connection_socket->write("l1",2);
            connection_socket->waitForBytesWritten();
        }
    }
}

void ReServer::buttonL2Changed(double value)
{
    if (connection_socket)
    {
        if ( value==1 && connection_socket->isOpen() )
        {
            connection_socket->write("l2",2);
            connection_socket->waitForBytesWritten();
        }
    }
}

void ReServer::buttonR1Changed(bool value)
{
    if (connection_socket)
    {
        if ( value==1 && connection_socket->isOpen() )
        {
            connection_socket->write("r1",2);
            connection_socket->waitForBytesWritten();
        }
    }
}

void ReServer::buttonR2Changed(double value)
{
    if (connection_socket)
    {
        if ( value==1 && connection_socket->isOpen() )
        {
            connection_socket->write("r2",2);
            connection_socket->waitForBytesWritten();
        }
    }
}

void ReServer::buttonAxisLxChanged(double value)
{

}

void ReServer::buttonAxisLyChanged(double value)
{

}

void ReServer::buttonAxisRxChanged(double value)
{

}

void ReServer::buttonAxisRyChanged(double value)
{

}

void ReServer::buttonStartChanged(bool value)
{
    if (connection_socket)
    {
        if ( value==1 && connection_socket->isOpen() )
        {
            connection_socket->write("m",1);
            connection_socket->waitForBytesWritten();
        }
    }
}

void ReServer::buttonSelectChanged(bool value)
{
    if (connection_socket)
    {
        if ( value==1 && connection_socket->isOpen() )
        {
            connection_socket->write("s",1);
            connection_socket->waitForBytesWritten();
        }
    }
}

void ReServer::buttonLeftChanged(bool value)
{
    if (connection_socket)
    {
        if ( value==1 && connection_socket->isOpen() )
        {
            connection_socket->write("l",1);
            connection_socket->waitForBytesWritten();
        }
    }
}

void ReServer::buttonRightChanged(bool value)
{
    if (connection_socket)
    {
        if ( value==1 && connection_socket->isOpen() )
        {
            connection_socket->write("r",1);
            connection_socket->waitForBytesWritten();
        }
    }
}

void ReServer::buttonUpChanged(bool value)
{
    if (connection_socket)
    {
        if ( value==1 && connection_socket->isOpen() )
        {
            connection_socket->write("u",1);
            connection_socket->waitForBytesWritten();
        }
    }
}

void ReServer::buttonDownChanged(bool value)
{
    if (connection_socket)
    {
        if ( value==1 && connection_socket->isOpen() )
        {
            connection_socket->write("d",1);
            connection_socket->waitForBytesWritten();
        }
    }
}






