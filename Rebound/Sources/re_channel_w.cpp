#include "re_channel_w.h"
#include <unistd.h>
#include <QMetaObject>

AcceptLoopWorker::AcceptLoopWorker(ReChannelW *channel) : m_channel(channel) {}

void AcceptLoopWorker::doWork()
{
    HANDLE hPipe = m_channel->createPipeInstance();
    while (hPipe != INVALID_HANDLE_VALUE)
    {
        if (ConnectNamedPipe(hPipe, nullptr) != FALSE)
        {
            qDebug() << "ReChannelW::Connect client";
            HANDLE connectedPipe = hPipe;
            hPipe = m_channel->createPipeInstance();
            ClientHandlerWorker *worker = new ClientHandlerWorker(m_channel, connectedPipe);
            QThread *thread = new QThread;
            worker->moveToThread(thread);
            connect(thread, SIGNAL(started()), 
                    worker, SLOT(handle()));
            connect(worker, SIGNAL(finished()), 
                    worker, SLOT(deleteLater()));
            connect(worker, SIGNAL(finished()), 
                    thread, SLOT(quit()));
            connect(thread, SIGNAL(finished()), 
                    thread, SLOT(deleteLater()));
            thread->start();
        }
    }
}

ClientHandlerWorker::ClientHandlerWorker(ReChannelW *channel, HANDLE pipe)
    : m_channel(channel), m_pipe(pipe) {}

void ClientHandlerWorker::handle()
{
    char buffer[PIPE_BUFFER_SIZE];
    DWORD dwRead;
    while( ReadFile(m_pipe, buffer, sizeof(buffer) - 1, &dwRead, nullptr)!=FALSE )
    {
        buffer[dwRead] = 0;
        QString input(buffer);
        QStringList lines = input.split("\n", QString::SkipEmptyParts);
        for (int i = 0; i < lines.length(); i++)
        {
            QString line = lines[i];
            QMetaObject::invokeMethod(m_channel, "processLine", Qt::QueuedConnection,
                                     Q_ARG(QString, line));
        }
    }
    qDebug() << "ReChannelW::Client Disconnected";
    DisconnectNamedPipe(m_pipe);
    CloseHandle(m_pipe);
    emit finished();
}

ReChannelW::ReChannelW(ReCaptain *cpt, QObject *parent)
    : QObject(parent)
{
    captain = cpt;

    pre = new RePreProcessor(cpt);
    hPipe = INVALID_HANDLE_VALUE;

    connect(this, SIGNAL(chess(const QString &)),
            pre , SLOT(chess(const QString &)));
    connect(this, SIGNAL(dirs(const QString &)),
            pre , SLOT(dirs(const QString &)));
    connect(this, SIGNAL(nato(QString)),
            pre , SLOT(nato(QString)));
    connect(this, SIGNAL(meta(QString)),
            pre , SLOT(meta(QString)));
    connect(this, SIGNAL(spex(QString)),
            pre , SLOT(spex(QString)));
    connect(this, SIGNAL(type(QString)),
            pre , SLOT(type(QString)));
    connect(this, SIGNAL(super(QString)),
            pre , SLOT(super(QString)));
    connect(this, SIGNAL(digit(QString)),
            pre , SLOT(digit(QString)));
    connect(this, SIGNAL(debug(QString)),
            pre , SLOT(debug(QString)));
    connect(this, SIGNAL(modifier(QString)),
            pre , SLOT(modifier(QString)));
}

ReChannelW::~ReChannelW()
{
}

void ReChannelW::listenPipe()
{
    AcceptLoopWorker *worker = new AcceptLoopWorker(this);
    QThread *thread = new QThread(this);
    worker->moveToThread(thread);
    connect(thread, &QThread::started, worker, &AcceptLoopWorker::doWork);
    connect(worker, &QObject::destroyed, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    thread->start();
}

void ReChannelW::processLine(QString line)
{
//    qDebug() << "ReChannelW::processLine" << line;
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
    hPipe = createPipeInstance();
    if (hPipe == INVALID_HANDLE_VALUE)
    {
        qDebug(RE_PIPE_PATH "Failed");
    }
}

HANDLE ReChannelW::createPipeInstance()
{
    // PIPE_UNLIMITED_INSTANCES allows creating more instances so the next client can connect.
    return CreateNamedPipe(TEXT(RE_PIPE_PATH),
                           PIPE_ACCESS_INBOUND,
                           PIPE_TYPE_BYTE | PIPE_WAIT,
                           PIPE_UNLIMITED_INSTANCES,
                           PIPE_BUFFER_SIZE,
                           PIPE_BUFFER_SIZE,
                           NMPWAIT_WAIT_FOREVER,
                           nullptr);
}

void ReChannelW::processCommand(QString k_type,
                                QString k_code)
{
    if( ReState::remote_state   &&
        ReState::sleep_state==0 &&
        ReState::ch_count==0 )
    {
        if( k_type=="debug" )
        {
            emit sendRemote(k_code);
        }
    }
    else if( k_type=="chess" )
    {
        emit chess(k_code);
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
    else if( k_type=="wake" )
    {
        ReState::wakeUp();
    }
}
