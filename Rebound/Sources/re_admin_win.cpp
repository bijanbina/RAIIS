#include "re_admin_win.h"
#include <string.h>

#define JOYSTICK_DELAY 100

ReAdminWin::ReAdminWin(int port, QObject *parent) : QObject(parent)
{
    //init
    connection_socket = NULL;
    server = new QTcpServer;
    connect(server, SIGNAL(newConnection()),
            this, SLOT(acceptConnection()));

    //server->listen(QHostAddress("127.0.0.1"), RE_PORT);
    if(server->listen(QHostAddress::Any, port))
    {
        qDebug() << "Admin server created on port " << port;
    }
    else
    {
        qDebug() << "Server failed";
        qDebug() << "Error message is:" << server->errorString();
    }
}

ReAdminWin::~ReAdminWin()
{
    qDebug() << "Closing Server";
    server->close();
}

void ReAdminWin::acceptConnection()
{
    qDebug() << "Server: Accepted connection";
    connection_socket = server->nextPendingConnection();
    connection_socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    connect(connection_socket, SIGNAL(readyRead()),
            this, SLOT(readyRead()));
    connect(connection_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    emit clientConnected();
}

void ReAdminWin::readyRead()
{
    QByteArray data = connection_socket->readAll();

#ifdef _WIN32
    if( data=="M" )
    {
        ///FIXME
        emit clientReqSusspend();
//        win->buttonGuideChanged();
    }
#endif
}

void ReAdminWin::displayError(QAbstractSocket::SocketError socketError)
 {
     if (socketError == QTcpSocket::RemoteHostClosedError)
         return;

     qDebug() <<  QString("Error Happened");
}
