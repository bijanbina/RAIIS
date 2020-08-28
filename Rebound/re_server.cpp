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
    connect(pad, SIGNAL(buttonL3Changed(bool)),
            this, SLOT(buttonL3Changed(bool)));
    connect(pad, SIGNAL(buttonR1Changed(bool)),
            this, SLOT(buttonR1Changed(bool)));
    connect(pad, SIGNAL(buttonR2Changed(double)),
            this, SLOT(buttonR2Changed(double)));
    connect(pad, SIGNAL(buttonR3Changed(bool)),
            this, SLOT(buttonR3Changed(bool)));

    connect(pad, SIGNAL(axisLeftXChanged(double)),
            this, SLOT(buttonAxisLxChanged(double)));
    connect(pad, SIGNAL(axisLeftYChanged(double)),
            this, SLOT(buttonAxisLyChanged(double)));
    connect(pad, SIGNAL(axisRightXChanged(double)),
            this, SLOT(buttonAxisRxChanged(double)));
    connect(pad, SIGNAL(axisRightYChanged(double)),
            this, SLOT(buttonAxisRyChanged(double)));

    connect(pad, SIGNAL(buttonStartChanged(bool)),
            this, SLOT(buttonStartChanged(bool)));
    connect(pad, SIGNAL(buttonSelectChanged(bool)),
            this, SLOT(buttonSelectChanged(bool)));
    connect(pad, SIGNAL(buttonCenterChanged(bool)),
            this, SLOT(buttonCenterChanged(bool)));
    connect(pad, SIGNAL(buttonGuideChanged(bool)),
            this, SLOT(buttonGuideChanged(bool)));

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
    connection_socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
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
    if ( value==1 )
    {
        reboundSendKey("a",1);
    }
}

void ReServer::buttonBChanged(bool value)
{
    if ( value==1 )
    {
        reboundSendKey("b",1);
    }
}

void ReServer::buttonXChanged(bool value)
{
    if ( value==1 )
    {
        reboundSendKey("x",1);
    }
}

void ReServer::buttonYChanged(bool value)
{
    if ( value==1 )
    {
        reboundSendKey("y",1);
    }
}

void ReServer::buttonL1Changed(bool value)
{
    if ( value==1 )
    {
        reboundSendKey("l1",2);
    }
}

void ReServer::buttonL2Changed(double value)
{
    if ( value==1 )
    {
        reboundSendKey("l2",2);
    }
}

void ReServer::buttonL3Changed(bool value)
{
    qDebug() << "l3 pressed";
    if ( value==1 )
    {
        reboundSendKey("l3",2);
    }
}

void ReServer::buttonR1Changed(bool value)
{
    if ( value==1 )
    {
        reboundSendKey("r1",2);
    }
}

void ReServer::buttonR2Changed(double value)
{
    qDebug() << "r2 pressed";
    if ( value==1 )
    {
        reboundSendKey("r2",2);
    }
}

void ReServer::buttonR3Changed(bool value)
{
    qDebug() << "r3 pressed";
    if ( value==1 )
    {
        reboundSendKey("r3",2);
    }
}

void ReServer::buttonAxisLxChanged(double value)
{
    if( last_la_x==0 )
    {
        if( value==1 )
        {
            last_la_x = 1;
            reboundSendKey("e",1);
        }
        else if( value==-1 )
        {
            last_la_x = 1;
            reboundSendKey("f",1);
        }
    }
    else if( value<0.5 && value>-0.5 )
    {
        last_la_x = 0;
    }
}

void ReServer::buttonAxisLyChanged(double value)
{
    if( last_la_y==0 )
    {
        if( value<-0.99 ) //up
        {
            last_la_y = 1;
            reboundSendKey("h",1);
        }
        else if( value>0.99 ) //down
        {
            last_la_y = 1;
            reboundSendKey("i",1);
        }
    }
    else if( value<0.5 && value>-0.5 )
    {
        last_la_y = 0;
    }
}

void ReServer::buttonAxisRxChanged(double value)
{
    if( last_la_x==0 )
    {
        if( value==1 )
        {
            last_la_x = 1;
            reboundSendKey("j",1);
        }
        else if( value==-1 )
        {
            last_la_x = 1;
            reboundSendKey("k",1);
        }
    }
    else if( value<0.5 && value>-0.5 )
    {
        last_la_x = 0;
    }
}

void ReServer::buttonAxisRyChanged(double value)
{
//    qDebug() << value;
    if( last_ra_y==0 )
    {
        if( value<-0.99 ) //up
        {
            last_ra_y = 1;
            reboundSendKey("n",1);
        }
        else if( value>0.99 ) //down
        {
            last_ra_y = 1;
            reboundSendKey("o",1);
        }
    }
    else if( value<0.5 && value>-0.5 )
    {
        last_ra_y = 0;
    }
}

void ReServer::buttonStartChanged(bool value)
{
    if ( value==1 )
    {
        reboundSendKey("m",1); //menu key
    }
}

void ReServer::buttonSelectChanged(bool value)
{
    if ( value==1 )
    {
        reboundSendKey("s",1);
    }
}

void ReServer::buttonCenterChanged(bool value)
{
    if ( value==1 )
    {
        qDebug() << "Center pressed";
        reboundSendKey("c",1);
    }
}

void ReServer::buttonGuideChanged(bool value)
{
    qDebug() << "Guide pressed";
    if ( value==1 )
    {
        reboundSendKey("g",1);
    }
}

void ReServer::buttonLeftChanged(bool value)
{
    if ( value==1 )
    {
        reboundSendKey("l",1);
    }
}

void ReServer::buttonRightChanged(bool value)
{
    if ( value==1 )
    {
        reboundSendKey("r",1);
    }
}

void ReServer::buttonUpChanged(bool value)
{
    if ( value==1 )
    {
        reboundSendKey("u",1);
    }
}

void ReServer::buttonDownChanged(bool value)
{
    if ( value==1 )
    {
        reboundSendKey("d",1);
    }
}

void ReServer::reboundSendKey(const char *data, int size)
{
    if (connection_socket)
    {
        if ( connection_socket->isOpen() )
        {
            if(size == 2)
            {
                qDebug() << "Sending " << data[0] << data[1];
            }
            else
            {
                qDebug() << "Sending " << data[0];
            }

            connection_socket->write(data,size);
            connection_socket->waitForBytesWritten();

            qDebug() << "finisihed sending";
        }
    }
}






