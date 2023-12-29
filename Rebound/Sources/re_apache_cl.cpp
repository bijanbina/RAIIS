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
            this, SLOT(disconnected()));

    live = new QTimer;
    watchdog = new QTimer;

    connect(live, SIGNAL(timeout()),
            this, SLOT(liveTimeout()));
    connect(watchdog, SIGNAL(timeout()),
            this, SLOT(watchdogTimeout()));
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
    con->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    con->connectToHost(QHostAddress(c_ip), c_port);
}

void ReApacheCl::tcpConnected()
{
    if( con->state()==QAbstractSocket::ConnectedState )
    { //Qt Bug: This code executed even wo any real connection
        qDebug() << "Remote: Connected";
        live->start(RE_LIVE);
        watchdog->start(RE_WATCHDOG);
        emit connected();
    }
}

void ReApacheCl::tcpDisplayError(QAbstractSocket::SocketError
                              socketError)
 {
    qDebug() << "ReApacheCl::Error" << con->errorString();

    con->close();
    live->stop();
    watchdog->start(RE_RECONNECT);
    if( con->state()!=QTcpSocket::UnconnectedState )
    {
        con->waitForDisconnected();
        con->abort();
    }
    if( socketError==QTcpSocket::RemoteHostClosedError )
    {
        return;
    }
}

void ReApacheCl::write(QString data)
{
    if( con->isOpen() )
    {
        live->start(RE_LIVE);//don't send live
        QByteArray data_b(data.toStdString().c_str());
        data_b.prepend(FA_START_PACKET);
        data_b.append(FA_END_PACKET);
        con->write(data_b);
        con->waitForBytesWritten(50);
        live->start(RE_LIVE);//don't send live
    }
}

// also calls watchdog close the connection
void ReApacheCl::disconnected()
{
    qDebug() << "ReApacheCl::disconnected";
}

// connection lost, drop connection and reconnect
void ReApacheCl::watchdogTimeout()
{
    if( con->state()==QAbstractSocket::ConnectedState )
    {
        qDebug() << "ReApacheCl::watchdogTimeout: connection dropped:"
                 << con->state();
        watchdog->start(RE_RECONNECT);
        live->stop();

        con->close();
        con->waitForDisconnected();
        con->connectToHost(QHostAddress(c_ip), c_port);
    }
    else if( con->state()!=QAbstractSocket::ConnectingState )
    {
        con->connectToHost(QHostAddress(c_ip), c_port);
    }
}

// send live packet
void ReApacheCl::liveTimeout()
{
    if( con->isOpen() )
    {
        if( con->state()==QAbstractSocket::ConnectedState )
        {
            write(FA_LIVE_PACKET);
        }
        else
        {
            qDebug() << "ReApacheCl::liveTimeout: not connected, State:"
                     << con->state();
            live->stop();
        }
    }
    else
    {
        qDebug() << "ReApacheCl::liveTimeout: socket is closed";
        live->stop();
    }
}

void ReApacheCl::tcpReadyRead()
{
    read_buf += con->readAll();
    QString data = processBuffer();
    watchdog->start(RE_WATCHDOG);

    while( data.length() )
    {
//        qDebug() << "ReApacheCl::tcpReadyRead()" << data;

        if( data==FA_LIVE_PACKET )
        {
            data = processBuffer(); //process multi packet
            continue;
        }
        else if( data.contains(FA_LIVE_PACKET) )
        {
            data.replace(FA_LIVE_PACKET, "");
        }

        if( data.length() )
        {
            emit readyRead(data);
        }

        data = processBuffer(); //process multi packet
    }
}

QByteArray ReApacheCl::processBuffer()
{
    if( read_buf.contains(FA_START_PACKET)==0 )
    {
        return "";
    }
    if( read_buf.contains(FA_END_PACKET)==0 )
    {
        return "";
    }
    int start_index = read_buf.indexOf(FA_START_PACKET);
    start_index += strlen(FA_START_PACKET);
    read_buf.remove(0, start_index);

    int end_index = read_buf.indexOf(FA_END_PACKET);
    QByteArray data = read_buf.mid(0, end_index);

    end_index += strlen(FA_END_PACKET);
    read_buf.remove(0, end_index);

    return data;
}
