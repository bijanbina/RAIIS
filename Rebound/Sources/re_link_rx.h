#ifndef RE_LINK_RX_H
#define RE_LINK_RX_H

#include <QDebug>
#include "re_commands.h"
#include "re_config.h"
#ifdef WIN32
#include <windows.h>
#endif

#ifdef WIN32
#define RE_PIPE_LINKTX      "\\\\.\\pipe\\com_binaee_linktx"
#else
#define RE_PIPE_LINK      "com.binaee.link"
#endif

class ReLinkRx : public QObject
{
    Q_OBJECT
public:
    ReLinkRx();

    QString curr_url;

public slots:
    void listenPipe();

private:
    void processLine(QString line);
    void processCmd(QString cmd_type, QString cmd_data);
    void createPipe();

#ifdef WIN32
    HANDLE hPipe;
#endif
};

#endif // RE_LINK_RX_H
