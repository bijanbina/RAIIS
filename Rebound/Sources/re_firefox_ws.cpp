#include "re_firefox_ws.h"
#define RE_MATCH_PATTERN "\"result\":{\"type\":\"string\""

ReFirefoxWs::ReFirefoxWs(QString ws_url, QObject *parent) : QObject(parent)
{
    url = ws_url;
}

ReFirefoxWs::~ReFirefoxWs()
{
    delete socket;
}

void ReFirefoxWs::run()
{
    socket = new QWebSocket;
    connect(socket, SIGNAL(connected()),    this, SLOT(onConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    socket->open(QUrl(url));
}

void ReFirefoxWs::onConnected()
{
   connect(socket, SIGNAL(textMessageReceived(QString)),
           this  , SLOT  (dataReceived(QString)));
   send_js("document.visibilityState");
}

void ReFirefoxWs::dataReceived(QString message)
{
    if( cmd_buf.length() )
    {
        QString js_cmd = "{\"id\": 2, \"method\": \"Runtime.evaluate\"";
        js_cmd += ", \"params\": {\"expression\": \"";
        js_cmd += cmd_buf + "\"}}\n\n";
        socket->sendTextMessage(js_cmd);
        cmd_buf = "";
    }
    else if( message.contains(RE_MATCH_PATTERN) )
    {
        if( message.contains("visible") )
        {
            title_state = 1;
            QString js_cmd = "{\"id\": 2, \"method\": \"Runtime.evaluate\"";
            js_cmd += ", \"params\": {\"expression\": \"";
            js_cmd += "document.title";
            js_cmd += "\"}}\n\n";
            socket->sendTextMessage(js_cmd);
        }
        else if( title_state )
        {
            QStringList vals = message.split("\"value\":\"");
            if( vals.length()>1 )
            {
                vals[1].remove("\"}}}"); //remove endings
                socket->close();
                emit finished(vals[1], url);
            }
        }
    }
}

void ReFirefoxWs::onDisconnected()
{
//   qDebug() << "WebSocket disconnected";
}

void ReFirefoxWs::send_js(QString cmd)
{
    QString en_runtime = "{\"id\": 1, \"method\": \"Runtime.enable\"}\n\n";

    socket->sendTextMessage(en_runtime);
    cmd_buf = cmd;
}
