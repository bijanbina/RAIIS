#ifndef CHANNEL_H_L
#define CHANNEL_H_L

#include "backend.h"

#include <QObject>
#include <QtCore/QObject>
#include <QtDBus/QtDBus>
#include "QThread"

#include "re_captain_l.h"

#define PH_UPDATE_INTERVAL 30 //in minutes
#define PH_UPDATE_OUTDATED 8 //in hours


class ReChannelL : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", COM_NAME)
public:
    ReChannelL(ReCaptainL *cpt, QObject *ui, QObject *parent = NULL);

    void startServer();

    ~ReChannelL();

public slots:
    void speex(const QString &text);
    void nato (const QString &text);
    void meta (const QString &text);
    void apps (const QString &text);
    void digit(const QString &text);
    void modifier(const QString &text);
    void debug(const QString &text);

private slots:
    void execute();

private:
    void ConnectDBus();

    QObject  *root;
    ReCaptainL *captain;

    QVector<CaptainCommand> cmd_buf;
    QString commands_str; //just for debug purpose
    QTimer *exec_timer;
};



#endif // CHANNEL_H_L
