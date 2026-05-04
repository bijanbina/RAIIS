#ifndef RE_LINK_RX_H
#define RE_LINK_RX_H

#include <QDebug>
#include <QGuiApplication>
#include <QMimeData>
#include <QImage>
#include "re_commands.h"
#include "re_config.h"
#include "re_state.h"
#ifdef WIN32
#include <windows.h>
#include "re_app_w.h"
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

public slots:
    void listenPipe();

private:
    void processLine(QString line);
    void processCmd(QString cmd_type, QString cmd_data);
    void processGPT(QString data);
    void createPipe();

    QString     clipboard_s;
    // we need to keep a separate one as ReLinkRx
    // is running in a separate thread
    QClipboard *cb;

#ifdef WIN32
    HANDLE hPipe;
#endif
};

#endif // RE_LINK_RX_H
