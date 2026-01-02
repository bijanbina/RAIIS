#ifndef RE_CHANNEL_W_H
#define RE_CHANNEL_W_H

#include <QObject>
#include <QtCore/QObject>
#include <QThread>

#include "re_preprocessor.h"
#include "backend.h"
#include "re_captain.h"

class ReChannelW;

// Runs the accept loop in its own thread (creates pipe instances and spawns client handlers).
class AcceptLoopWorker : public QObject
{
    Q_OBJECT
public:
    explicit AcceptLoopWorker(ReChannelW *channel);

public slots:
    void doWork();

private:
    ReChannelW *m_channel;
};

// Handles one connected client in its own thread (reads lines, forwards to channel via processLine).
class ClientHandlerWorker : public QObject
{
    Q_OBJECT
public:
    ClientHandlerWorker(ReChannelW *channel, HANDLE pipe);

public slots:
    void handle();

signals:
    void finished();

private:
    ReChannelW *m_channel;
    HANDLE m_pipe;
};

class ReChannelW : public QObject
{
    Q_OBJECT
public:
    ReChannelW(ReCaptain *cpt, QObject *parent = NULL);
    ~ReChannelW();

    RePreProcessor *pre;

    HANDLE createPipeInstance();

public slots:
    void listenPipe();
    void processLine(QString line);
    void processCommand(QString k_type, QString k_code);

signals:
    void chess(QString args);
    void digit(QString args);
    void debug(QString args);
    void dirs(const QString &args);
    void modifier(QString args);
    void meta(QString args);
    void nato(QString args);
    void type(QString args);
    void spex(QString args);
    void super(QString args);
    void sendRemote(QString k_code);

private:
    void createPipe();

    ReCaptain      *captain;
    HANDLE hPipe;
};

#endif // RE_CHANNEL_W_H
