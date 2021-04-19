#include "re_admin_win.h"
#include <string.h>
#include <shellapi.h>

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
    qDebug() << "Admin Server: Accepted connection";
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
    qDebug() << "received data:" << data;



#ifdef _WIN32
    QString command = "O:\\Projects\\AccJoon\\release\\AccJoon.exe";

    qDebug() << "Execute command:" << command << data;

    ShellExecuteA(0, "open", command.toStdString().c_str(), data.toStdString().c_str(), 0, SW_HIDE);
#endif
}

void ReAdminWin::displayError(QAbstractSocket::SocketError socketError)
 {
     if (socketError == QTcpSocket::RemoteHostClosedError)
         return;

     qDebug() <<  QString("Error Happened");
}
