#include "re_remote.h"
#include <unistd.h>

ReRemote::ReRemote(QObject *parent) : QObject(parent)
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

   QStringList data_split = read_data.trimmed().split("::",
                                        Qt::SkipEmptyParts);
   qDebug() << "readyRead" << data_split;
   if( data_split.size()!=2 )
   {
       qDebug() << "SHIR TUT" << data_split.size();
       return;
   }
   QString k_type = data_split[0];
   QString k_code = data_split[1];
   emit process(k_type, k_code);
}
