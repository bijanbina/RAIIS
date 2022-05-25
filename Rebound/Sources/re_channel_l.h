#ifndef CHANNEL_H_L
#define CHANNEL_H_L


#include <QObject>
#include <QtCore/QObject>
#include <QtDBus/QtDBus>
#include "QThread"

#include "backend.h"
#include "re_captain_l.h"

#define RE_EXEC_TIMEOUT_M  1


class ReChannelL : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", COM_NAME)
public:
    ReChannelL(ReCaptainL *cpt, QObject *ui, QObject *parent = NULL);

    ~ReChannelL();

public slots:
    void dirs (const QString &text);
    void nato (const QString &text);
    void meta (const QString &text);
    void apps (const QString &text);
    void type (const QString &text); //No Repeat on LastCmd
    void spex (const QString &text); //special
    void super(const QString &text); //single shot meta cmd
    void digit(const QString &text);
    void modifier(const QString &text);
    void debug(const QString &text);
    void execute();

private slots:
    void execTimeOut();

private:
    void ConnectDBus();
    void handleLastRepeatable(int input);

    QObject  *root;
    ReCaptainL *captain;
    int special_c; //count of special

    QVector<CCommand> cmd_buf;
    QString commands_str; //just for debug purpose
};



#endif // CHANNEL_H_L
