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
    QStringList fields = line.split(COMMAND_SEPARATOR,
                               QString::SkipEmptyParts);
    if ( fields.length()!=2 )
    {
        qDebug() << "Invalid data `" + line + "`";
        return;
    }

    QString command = fields[0];
    QString arg = fields[1];
    qDebug() << "Command:" << command
             << "Args:" << arg;
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

void ReChannelW::processCommand(QString cmd, QString args)
{
    if( cmd=="dirs" )
    {
        emit dirs(args);
    }
    else if( cmd=="nato" )
    {
        emit nato(args);
    }
    else if( cmd=="meta" )
    {
        emit meta(args);
    }
    else if( cmd=="apps" )
    {
        emit apps(args);
    }
    else if( cmd=="spex" )
    {
        emit spex(args);
    }
    else if( cmd=="type" )
    {
        emit type(args);
    }
    else if( cmd=="super" )
    {
        emit super(args);
    }
    else if( cmd=="digit" )
    {
        emit digit(args);
    }
    else if( cmd=="debug" )
    {
        emit debug(args);
    }
    else if( cmd=="modifier" )
    {
        emit modifier(args);
    }
}
