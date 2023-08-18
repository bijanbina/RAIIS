#include "re_channel_w.h"
#include <unistd.h>

ReChannelW::ReChannelW(ReCaptain *cpt, QObject *parent) : QObject(parent)
{
    captain = cpt;

    pre = new RePreProcessor(cpt);
    createPipe();

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

    initTCP();
}

ReChannelW::~ReChannelW()
{
    tcpClient.close();
}

void ReChannelW::initTCP()
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

void ReChannelW::ListenPipe()
{
    char buffer[BUFFER_SIZE];
    DWORD dwRead;
    while( hPipe!=INVALID_HANDLE_VALUE )
    {
        // wait for someone to connect to the pipe
        if( ConnectNamedPipe(hPipe, nullptr)!=FALSE )
        {
            qDebug() << "Connect client";
            while( ReadFile(hPipe, buffer, sizeof(buffer)-1, &dwRead, nullptr)!=FALSE )
            {
                // add terminating zero
                buffer[dwRead] = 0;
                QString input(buffer);

                QStringList lines = input.split("\n", QString::SkipEmptyParts);

                for(int i=0 ; i<lines.length() ; i++)
                {
                    processLine(lines[i]);
                }
            }
        }

        qDebug() << "Client Disconnected";
        DisconnectNamedPipe(hPipe);
    }
}

void ReChannelW::processLine(QString line)
{
    line = line.trimmed();
    QStringList fields = line.split(RE_NP_SEPARATOR,
                               QString::SkipEmptyParts);

    QString key_type, key_code;
    if ( fields.length()>0 )
    {
        key_type = fields[0];
    }
    if ( fields.length()>1 )
    {
        key_code = fields[1];
    }
    if ( fields.length()==0 ||
         fields.length()>2 )
    {
        qDebug() << "Error 128: wrong field length, data=`"
                    + line + "`";
        return;
    }
//    qDebug() << "Command:" << key_type
//             << "Args:" << key_code;

    processCommand(key_type, key_code);
}

void ReChannelW::createPipe()
{
    // To create an instance of a named pipe by using CreateNamedPipe,
    // the user must have FILE_CREATE_PIPE_INSTANCE access to the named pipe object.
    hPipe = CreateNamedPipe(TEXT(PIPE_PATH),
                            PIPE_ACCESS_INBOUND,            // dwOpenMode. The flow of data in the pipe goes from client to server only
                            PIPE_TYPE_BYTE | PIPE_WAIT,     // dwPipeMode
                            1,                              // nMaxInstances
                            BUFFER_SIZE,                    // nOutBufferSize
                            BUFFER_SIZE,                    // nInBufferSize
                            NMPWAIT_WAIT_FOREVER,           // nDefaultTimeOut
                            nullptr);                       // lpSecurityAttributes

    if( hPipe==INVALID_HANDLE_VALUE )
    {
        qDebug(PIPE_PATH"Failed");
    }
    qDebug() << PIPE_PATH << "pipe Created";
}

void ReChannelW::processCommand(QString k_type, QString k_code)
{
    if( captain->state->remote_state )
    {
        sendRemote(k_type, k_code);
    }
    else if( k_type=="dirs" )
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

void ReChannelW::sendRemote(QString k_type, QString k_code)
{
    if(!tcpClient.isOpen())
    {
        qDebug() << "Riidi, connecting to: " << RE_CIP << RE_CPORT0;
        tcpClient.connectToHost(QHostAddress(RE_CIP), RE_CPORT0 );
    }

    QString data = k_type;
    data += "::" + k_code + "\n";

    tcpClient.write(data.toStdString().c_str());
}

void ReChannelW::displayError(QAbstractSocket::SocketError socketError)
{
    if( socketError==QTcpSocket::RemoteHostClosedError )
    {
        return;
    }

    qDebug() << "Network error:" << tcpClient.errorString();
    tcpClient.close();
}

void ReChannelW::connected()
{
    qDebug() << "Client: Connected";
    tcpClient.setSocketOption(QAbstractSocket::LowDelayOption, 1);
    connect(&tcpClient, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void ReChannelW::disconnected()
{
    tcpClient.close();
    qDebug() << "Client: Disconnected";
}

void ReChannelW::readyRead()
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
   processCommand(k_type, k_code);
}
