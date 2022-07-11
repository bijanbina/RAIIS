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

#define LINE_SEPARATOR "\r\n"
#define COMMAND_SEPARATOR "###"
#define COMMAND_POSITION 0
#define ARGUMENT_POSITION 1


class ReChannelW : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", COM_NAME)
public:
    ReChannelW(ReCaptain *cpt, QObject *parent = NULL);
    ~ReChannelW();

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
    void exec(QString args);


private:
    void createPipe();
    void handleNewCommand(QString cmd, QString args);

    RePreProcessor *pre;
    HANDLE hPipe;
};

#endif // CHANNEL_H_W
