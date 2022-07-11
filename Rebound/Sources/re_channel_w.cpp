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
    connect(this, SIGNAL(exec(QString)), pre, SLOT(exec(QString)));
}

ReChannelW::~ReChannelW()
{
    ;
}

void ReChannelW::ListenPipe()
{
    char buffer[BUFFER_SIZE];
    DWORD dwRead;
    QStringList all_line;
    QStringList list_data;
    while(hPipe != INVALID_HANDLE_VALUE)
    {
        // wait for someone to connect to the pipe
        if (ConnectNamedPipe(hPipe, nullptr) != FALSE)
        {
            qDebug() << "Connect client";
            while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, nullptr) != FALSE)
            {
                /* add terminating zero */
                buffer[dwRead] = '\0';

                /* do something with data in buffer */
                printf("Received: %s\n", buffer);

                QString data(buffer);
                qDebug() << data;

                all_line = data.split(LINE_SEPARATOR, QString::SkipEmptyParts);

                foreach (QString line, all_line)
                {
                    line = line.trimmed();
                    list_data = line.split(COMMAND_SEPARATOR, QString::SkipEmptyParts);
                    if ( list_data.length()!=2 )
                    {
                        qDebug() << "Invalid data `" + data + "`";
                        continue;
                    }

                    qDebug() << "Command:" << list_data[COMMAND_POSITION];
                    qDebug() << "Args:" << list_data[ARGUMENT_POSITION];
                    handleNewCommand(list_data[COMMAND_POSITION], list_data[ARGUMENT_POSITION]);
                }
            }
        }

        qDebug() << "Disconnect client";
        DisconnectNamedPipe(hPipe);
    }
}

void ReChannelW::createPipe()
{
    // To create an instance of a named pipe by using CreateNamedPipe,
    // the user must have FILE_CREATE_PIPE_INSTANCE access to the named pipe object.
    hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\ipc"),
                            PIPE_ACCESS_INBOUND,            // dwOpenMode. The flow of data in the pipe goes from client to server only
                            PIPE_TYPE_BYTE | PIPE_WAIT,     // dwPipeMode
                            1,                              // nMaxInstances
                            OUTPUT_BUFFER_SIZE,             // nOutBufferSize
                            INPUT_BUFFER_SIZE,              // nInBufferSize
                            NMPWAIT_WAIT_FOREVER,           // nDefaultTimeOut
                            nullptr);                       // lpSecurityAttributes

    if (hPipe == INVALID_HANDLE_VALUE)
    {
        qFatal("Cannot create \\\\.\\pipe\\ipc");
    }
    qDebug() << "Create pipe \\\\.\\pipe\\ipc";
}

void ReChannelW::handleNewCommand(QString cmd, QString args)
{
    if (cmd == "dirs") {
        emit dirs(args);
    } else if (cmd == "nato") {
        emit nato(args);
    } else if (cmd == "meta") {
        emit meta(args);
    } else if (cmd == "apps") {
        emit apps(args);
    } else if (cmd == "spex") {
        emit spex(args);
    } else if (cmd == "type") {
        emit type(args);
    } else if (cmd == "super") {
        emit super(args);
    } else if (cmd == "digit") {
        emit digit(args);
    } else if (cmd == "debug") {
        emit debug(args);
    } else if (cmd == "modifier") {
        emit modifier(args);
    } else if (cmd == "exec") {
        emit exec(args);
    }
}
