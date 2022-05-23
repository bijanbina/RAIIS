#include "re_firefox_l.h"
#define CMD_PATH "Resources/Scripts/ElementsWithScrolls.js"

ReFirefoxL::ReFirefoxL(QObject *parent) : QObject(parent)
{
    socket = new QWebSocket;
    connect(socket, SIGNAL(connected()),    this, SLOT(onConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QString ws = getStrCommand("Resources/Scripts/ff_getWS.sh");
    QStringList ws_list = ws.split("\n");
    for( int i=0 ; i<ws_list.length() ; i++ )
    {
        ReFirefoxWs *child = new ReFirefoxWs(ws_list[i]);
        QThread  *child_th = new QThread;
        child->moveToThread(child_th);
        child_th->start();
        childs.push_back(child);
        childs_th.push_back(child_th);
        connect(this , SIGNAL(startChild()), child, SLOT(run()));
        connect(child, SIGNAL(finished(QString,QString)),
                this , SLOT  (urlCheck(QString,QString)));
    }
    emit startChild();
}

ReFirefoxL::~ReFirefoxL()
{
    delete socket;
    for( int i=0 ; i<childs_th.size() ; i++ )
    {
        delete childs[i];
        delete childs_th[i];
    }
    childs.clear();
    childs_th.clear();
}

void ReFirefoxL::urlCheck(QString title, QString ws)
{
    QString cmd = "Resources/Scripts/ff_isVisible.sh \"";
    cmd += title + "\"";
    QString res = getStrCommand(cmd);

    if( res.length() )
    {
        qDebug() << "W" << ws;
        socket->open(QUrl(ws));
    }
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
    if( cmd_buf.length() )
    {
        qDebug() << message;
        QString js_cmd = "{\"id\": 2, \"method\": \"Runtime.evaluate\"";
        js_cmd += ", \"params\": {\"expression\": \"";
        js_cmd += cmd_buf + "\"}}\n";
        qDebug() << "executing" << cmd_buf.toStdString().c_str();
        cmd_buf = "";
//        QThread::msleep(50);
        socket->sendTextMessage(js_cmd);
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
