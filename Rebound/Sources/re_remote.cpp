#include "re_remote.h"
#include <unistd.h>

ReRemote::ReRemote(RePreProcessor *pre, QObject *parent) : QObject(parent)
{
    connect(&tcpClient, SIGNAL(connected()), this, SLOT(connected()));
    connect(&tcpClient, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
#ifdef RE_REMOTE
    tcpClient.connectToHost(QHostAddress(RE_CIP), RE_CPORT1 );
#else
    tcpClient.connectToHost(QHostAddress(RE_CIP), RE_CPORT0 );
#endif

    connect(this, SIGNAL(dirs(const QString &)), pre, SLOT(dirs(const QString &)));
    connect(this, SIGNAL(nato(QString)), pre, SLOT(nato(QString)));
    connect(this, SIGNAL(meta(QString)), pre, SLOT(meta(QString)));
    connect(this, SIGNAL(apps(QString)), pre, SLOT(apps(QString)));
    connect(this, SIGNAL(spex(QString)), pre, SLOT(spex(QString)));
    connect(this, SIGNAL(type(QString)), pre, SLOT(type(QString)));
    connect(this, SIGNAL(super(QString)), pre, SLOT(super(QString)));
    connect(this, SIGNAL(digit(QString)), pre, SLOT(digit(QString)));
    connect(this, SIGNAL(debug(QString)), pre, SLOT(debug(QString)));
    connect(this, SIGNAL(modifier(QString)), pre, SLOT(modifier(QString)));
}

ReRemote::~ReRemote()
{
    tcpClient.close();
}

void ReRemote::send(QString k_type, QString k_code)
{
    qDebug() << "sendRemote" << k_type << k_code;
    if(!tcpClient.isOpen())
    {
        qDebug() << "Riidi, connecting to: " << RE_CIP << RE_CPORT0;
        tcpClient.connectToHost(QHostAddress(RE_CIP), RE_CPORT0 );
    }

    QString data = k_type;
    data += "::" + k_code + "\n";

    tcpClient.write(data.toStdString().c_str());
}

void ReRemote::displayError(QAbstractSocket::SocketError socketError)
{
    if( socketError==QTcpSocket::RemoteHostClosedError )
    {
        return;
    }

    qDebug() << "Network error:" << tcpClient.errorString();
    tcpClient.close();
}

void ReRemote::connected()
{
    qDebug() << "Client: Connected";
    tcpClient.setSocketOption(QAbstractSocket::LowDelayOption, 1);
    connect(&tcpClient, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void ReRemote::disconnected()
{
    tcpClient.close();
    qDebug() << "Client: Disconnected";
}

void ReRemote::readyRead()
{
    QString read_data = tcpClient.readAll();
    if( read_data.size()==0 )
    {
        return;
    }

    read_data = read_data.trimmed();
    QStringList data_lines = read_data.split("\n", Qt::SkipEmptyParts);

    int len = data_lines.size();
    QStringList data_split;
    for( int i=0 ; i<len ; i++ )
    {
        data_split = data_lines[i].split("::", Qt::SkipEmptyParts);
        if( data_split.size()!=2 )
        {
            qDebug() << "SHIR TUT" << data_split.size();
            return;
        }
        QString k_type = data_split[0];
        QString k_code = data_split[1];
        processCommand(k_type, k_code);
    }
}

void ReRemote::processCommand(QString k_type, QString k_code)
{
    if( k_type=="dirs" )
    {
        emit dirs(k_code);
    }
    else if( k_type=="nato" )
    {
        emit nato(k_code);
    }
    else if( k_type=="meta" )
    {
        emit meta(k_code);
    }
    else if( k_type=="apps" )
    {
        emit apps(k_code);
    }
    else if( k_type=="spex" )
    {
        emit spex(k_code);
    }
    else if( k_type=="type" )
    {
        emit type(k_code);
    }
    else if( k_type=="super" )
    {
        emit super(k_code);
    }
    else if( k_type=="digit" )
    {
        emit digit(k_code);
    }
    else if( k_type=="debug" )
    {
        emit debug(k_code);
    }
    else if( k_type=="modifier" )
    {
        emit modifier(k_code);
    }
}
