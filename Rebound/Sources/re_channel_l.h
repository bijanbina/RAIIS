#ifndef RE_CHANNEL_L_H
#define RE_CHANNEL_L_H

#include <QObject>
#include <QtCore/QObject>
#include <QtDBus/QtDBus>
#include <QThread>
#include "re_preprocessor.h"

#include "backend.h"
#include "re_captain.h"

class ReChannelL : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", COM_NAME)
public:
    ReChannelL(ReCaptain *cpt, QObject *parent = NULL);
    ~ReChannelL();

    RePreProcessor *pre;

signals:
    void sendRemote(QString k_type, QString k_code);

private:
    void ConnectDBus();
};

#endif // RE_CHANNEL_L_H
