#include "re_channel_w.h"
#include <unistd.h>

ReChannelW::ReChannelW(ReCaptain *cpt, QObject *parent) : QObject(parent)
{
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
}

ReChannelW::~ReChannelW()
{
    ;
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
    if ( fields.length()!=2 )
    {
        qDebug() << "Error 128: wrong field length, `"
                    + line + "`";
        return;
    }

    QString key_type = fields[0];
    QString key_code = fields[1];
    qDebug() << "Command:" << key_type
             << "Args:" << key_code;

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
                            OUTPUT_BUFFER_SIZE,             // nOutBufferSize
                            INPUT_BUFFER_SIZE,              // nInBufferSize
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
