#ifndef CHANNEL_H_W
#define CHANNEL_H_W

#include <QObject>
#include <QtCore/QObject>

#include "re_preprocessor.h"
#include "backend.h"
#include "re_captain.h"

// The buffer size specified should be small enough that your process will not run out of nonpaged pool,
// but large enough to accommodate typical requests.
#define BUFFER_SIZE (1024 * 8)
#define INPUT_BUFFER_SIZE BUFFER_SIZE
#define OUTPUT_BUFFER_SIZE BUFFER_SIZE

#define COMMAND_SEPARATOR ","

class ReChannelW : public QObject
{
    Q_OBJECT
public:
    ReChannelW(ReCaptain *cpt, QObject *parent = NULL);
    ~ReChannelW();

public slots:
    void ListenPipe();

signals:
    void dirs(const QString &args);
    void nato(QString args);
    void meta(QString args);
    void apps(QString args);
    void spex(QString args);
    void type(QString args);
    void super(QString args);
    void digit(QString args);
    void debug(QString args);
    void modifier(QString args);

private:
    void createPipe();
    void processCommand(QString cmd, QString args);
    void processLine(QString line);

    RePreProcessor *pre;
    HANDLE hPipe;
};

#endif // CHANNEL_H_W
