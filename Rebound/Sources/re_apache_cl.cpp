#include "re_apache_cl.h"

ReApacheCl::ReApacheCl(QObject *parent): QObject(parent)
{
    connection = new QTcpSocket;
    connection->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    connect(connection, SIGNAL(connected()),
            this, SLOT(tcpConnected()));
    connect(connection, SIGNAL(readyRead()),
            this, SLOT(tcpReadyRead()));
    connect(connection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(tcpDisplayError(QAbstractSocket::SocketError)));
    connect(connection, SIGNAL(disconnected()),
            this, SLOT(tcpDisconnected()));

    live = new QTimer;
    watchdog = new QTimer;

    connect(live, SIGNAL(timeout()),
            this, SLOT(liveTimeout()));
    connect(watchdog, SIGNAL(timeout()),
            this, SLOT(watchdogTimeout()));

//#ifdef RE_REMOTE
//    connection->connectToHost(QHostAddress(RE_CIP), RE_CPORT1 );
//#else
//    connection->connectToHost(QHostAddress(RE_CIP), RE_CPORT0 );
//#endif
}

ReApacheCl::~ReApacheCl()
{
    if( connection->isOpen() )
    {
        connection->close();
    }
    delete connection;
}

void ReApacheCl::start(QString ip, int port)
{
    c_ip = ip;
    c_port = port;
    connection->connectToHost(QHostAddress(c_ip), c_port);
}

void ReApacheCl::tcpConnected()
{
    live->start(RE_LIVE);
    watchdog->start(RE_WATCHDOG);

    emit connected();
}

void ReApacheCl::tcpDisplayError(QAbstractSocket::SocketError
                              socketError)
 {
     if( socketError==QTcpSocket::RemoteHostClosedError )
     {
         return;
     }

     qDebug() << QString("ReConnection::Error Happened");
     emit error();
}

void ReApacheCl::write(QString data)
{
    if( connection->isOpen() )
    {
        live->start(RE_LIVE);//don't send live
        QByteArray data_b(data.toStdString().c_str());
        connection->write(data_b);
        connection->waitForBytesWritten(50);
        live->start(RE_LIVE);//don't send live
    }
}

void ReApacheCl::tcpDisconnected()
{
    connection->connectToHost(QHostAddress(c_ip), c_port);
}

// connection lost, drop connection and reconnect
void ReApacheCl::watchdogTimeout()
{
    if( connection->isOpen() )
    {
        qDebug() << "Remote: connection dropped:"
                 << connection->state();
        watchdog->stop();
        live->stop();

        // in disconnect it will try to reconnect
        connection->close();
    }
    else
    {
        qDebug() << "Remote: watchdog, tcpClient is closed";
    }
}

// send live packet
void ReApacheCl::liveTimeout()
{
    if( connection->isOpen() )
    {
        if( connection->state()==QAbstractSocket::ConnectedState )
        {
            int byte_count = connection->write("Live");
            connection->waitForBytesWritten(50);
            if( byte_count!=4 )
            {
                qDebug() << "Client: live, byte_count:" << byte_count;
            }
        }
        else
        {
            qDebug() << "Remote: live, not connected, State:"
                     << connection->state();
        }
    }
    else
    {
        qDebug() << "Remote: live, tcpClient is closed";
    }
}

void ReApacheCl::tcpReadyRead()
{
    QByteArray data = connection->readAll();
    watchdog->start(RE_WATCHDOG);

    if( data=="Live" )
    {
        return;
    }
    else if( data.contains("Live") )
    {
        data.replace("Live", "");
    }

    emit readyRead(data);
}
