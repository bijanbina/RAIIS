#ifndef CHANNEL_H_L
#define CHANNEL_H_L

#include <QObject>
#include <QtCore/QObject>
#include <QtDBus/QtDBus>
#include <QThread>
#include "re_preprocessor.h"

#include "backend.h"
#include "re_captain_l.h"

class ReChannelL : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", COM_NAME)
public:
    ReChannelL(ReCaptain *cpt, QObject *parent = NULL);
    ~ReChannelL();

private:
    void ConnectDBus();

    RePreProcessor *pre;
};



#endif // CHANNEL_H_L
