#include "re_firefox_l.h"
#define WS_URL   "ws://127.0.0.1:9222/devtools/page/0fa1e028-f8af-41d5-8e8f-b74fb085e35a"
#define CMD_PATH "Resources/Scripts/ElementsWithScrolls.js"

ReFirefoxL::ReFirefoxL(QObject *parent) : QObject(parent)
{
    socket = new QWebSocket;
    connect(socket, SIGNAL(connected()),    this, SLOT(onConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QString ws = getStrCommand("Resources/Scripts/ff_getFocusedWS.sh");
    qDebug() << ws;
    socket->open(QUrl(ws));
}

void ReFirefoxL::onConnected()
{
   qDebug() << "WebSocket connected";
   connect(socket, SIGNAL(textMessageReceived(QString)),
           this  , SLOT  (dataReceived(QString)));
   sendScroll();
}

void ReFirefoxL::dataReceived(QString message)
{
    qDebug() << message;
    if( cmd_buf.length() )
    {
        QString js_cmd = "{\"id\": 2, \"method\": \"Runtime.evaluate\"";
        js_cmd += ", \"params\": {\"expression\": \"";
        js_cmd += cmd_buf + "\"}}\n\n";
        qDebug() << "executing" << cmd_buf.toStdString().c_str();
        QThread::msleep(50);
        socket->sendTextMessage(js_cmd);
        cmd_buf = "";
    }
}

void ReFirefoxL::onDisconnected()
{
   qDebug() << "WebSocket disconnected";
}

void ReFirefoxL::sendScroll()
{
    QString cmd;
    QString filename = CMD_PATH;

    QFile file(filename);
    if( file.open(QIODevice::ReadOnly) )
    {
        while( !file.atEnd() )
        {
            QString line = file.readLine();
//            if( line.contains(QRegExp("(\\{|\\}|;)")) )
//            {
                line.replace('\n', " ");
                line.replace('\t', " ");
////                qDebug() << "444444444"  << line;
//            }
//            else
//            {
//                line.replace('\n', "; ");
//            }
            cmd += line;
        }
        file.close();
    }
    else
    {
        qDebug() << "Error 133: error opening"
                 << filename;
    }

    send_js(cmd);
}

void ReFirefoxL::send_js(QString cmd)
{
    QString en_runtime = "{\"id\": 1, \"method\": \"Runtime.enable\"}\n\n";

    socket->sendTextMessage(en_runtime);
    cmd_buf = cmd;
//    qDebug() << "send_js" << cmd;
}
