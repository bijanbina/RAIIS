#include "re_apache_cl.h"

ReApacheCl::ReApacheCl(QObject *parent): QObject(parent)
{
    con = new QTcpSocket;

    connect(con, SIGNAL(connected()),
            this, SLOT(tcpConnected()));
    connect(con, SIGNAL(readyRead()),
            this, SLOT(tcpReadyRead()));
    connect(con, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(tcpDisplayError(QAbstractSocket::SocketError)));
    connect(con, SIGNAL(disconnected()),
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
    if( con->isOpen() )
    {
        con->close();
    }
    delete con;
}

void ReApacheCl::start(QString ip, int port)
{
    c_ip = ip;
    c_port = port;
    con->connectToHost(QHostAddress(c_ip), c_port);
}

void ReApacheCl::tcpConnected()
{
    qDebug() << "Remote: Connected";
    con->setSocketOption(QAbstractSocket::LowDelayOption, 1);
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

     qDebug() << "ReApacheCl::Error" << con->errorString();
     emit error();
}

void ReApacheCl::write(QString data)
{
    if( con->isOpen() )
    {
        live->start(RE_LIVE);//don't send live
        QByteArray data_b(data.toStdString().c_str());
        con->write(data_b);
        con->waitForBytesWritten(50);
        live->start(RE_LIVE);//don't send live
    }
}

void ReApacheCl::tcpDisconnected()
{
    con->connectToHost(QHostAddress(c_ip), c_port);
}

// connection lost, drop connection and reconnect
void ReApacheCl::watchdogTimeout()
{
    if( con->isOpen() )
    {
        qDebug() << "ReApacheCl::watchdogTimeout: connection dropped:"
                 << con->state();
        watchdog->stop();
        live->stop();

        // in disconnect it will try to reconnect
        con->close();
    }
    else
    {
        qDebug() << "Remote: watchdog, tcpClient is closed";
    }
}

// send live packet
void ReApacheCl::liveTimeout()
{
    if( con->isOpen() )
    {
        if( con->state()==QAbstractSocket::ConnectedState )
        {
            con->write(FA_LIVE_PACKET);
        }
        else
        {
            qDebug() << "ReApacheCl::liveTimeout: not connected, State:"
                     << con->state();
        }
    }
    else
    {
        qDebug() << "Remote: live, tcpClient is closed";
    }
}

void ReApacheCl::tcpReadyRead()
{
    QByteArray data = con->readAll();
    watchdog->start(RE_WATCHDOG);
    qDebug() << "ReApacheCl::tcpReadyRead()" << data;

    if( data==FA_LIVE_PACKET )
    {
        return;
    }
    else if( data.contains(FA_LIVE_PACKET) )
    {
        data.replace(FA_LIVE_PACKET, "");
    }

    emit readyRead(data);
}
