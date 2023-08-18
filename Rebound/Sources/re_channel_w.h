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

class ReChannelW : public QObject
{
    Q_OBJECT
public:
    ReChannelW(ReCaptain *cpt, QObject *parent = NULL);
    ~ReChannelW();

    void initTCP();

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

private slots:
    void connected();
    void displayError(QAbstractSocket::SocketError socketError);
    void disconnected();
    void readyRead();

private:
    void createPipe();
    void processCommand(QString k_type, QString k_code);
    void processLine(QString line);
    void sendRemote(QString k_type, QString k_code);

    RePreProcessor *pre;
    ReCaptain      *captain;
    QTcpSocket      tcpClient;
    HANDLE hPipe;
};

#endif // CHANNEL_H_W
