#include "re_firefox_l.h"
#define JS_SC_PATH "Scripts/Firefox/ElementsWithScrolls.js"
#define WS_SC_PATH "Scripts/Firefox/getWS.sh"
#define VI_SC_PATH "Scripts/Firefox/isVisible.sh"

ReFirefoxL::ReFirefoxL(QObject *parent) : QObject(parent)
{
    socket = new QWebSocket;
    connect(socket, SIGNAL(connected()),    this, SLOT(onConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    ws_buf = "";
}

ReFirefoxL::~ReFirefoxL()
{
    delete socket;
    reset();
}

void ReFirefoxL::refreshURL()
{
    QString ws = getStrCommand(WS_SC_PATH);
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

//Check if firefox is visible
void ReFirefoxL::urlCheck(QString title, QString ws)
{
    QString cmd = VI_SC_PATH " \"";
    cmd += title + "\"";
    QString res = getStrCommand(cmd);

    if( res.length() )
    {
        ws_buf = ws;
        socket->open(QUrl(ws));
        qDebug() << ws;
        reset();
    }
}

void ReFirefoxL::reset()
{
    for( int i=0 ; i<childs_th.size() ; i++ )
    {
        disconnect(this, SIGNAL(startChild()), childs[i], SLOT(run()));
        disconnect(childs[i], SIGNAL(finished(QString,QString)),
                   this     , SLOT  (urlCheck(QString,QString)));
        childs_th[i]->exit();
        childs_th[i]->wait();
        delete childs_th[i];
    }
    childs.clear();
    childs_th.clear();
}

void ReFirefoxL::scrollDown(int speed, QString st_cmd)
{
    sc_speed = speed-1;
    if( ws_buf.length() )
    {
        sc_dir = RE_META_DIVE;
        QString cmd = "bt_speed = ";
        cmd += QString::number(speed_table[sc_speed]) + "; ";
        cmd += "bt_step = ";
        cmd += QString::number(step_table[sc_speed]) + "; ";
        cmd += "clearInterval(scroll_timer); ";
        cmd += "scroll_timer = undefined;";
        cmd += "var scroll_timer = setInterval(pageScroll, bt_speed);";

        send_js(cmd);
        system(st_cmd.toStdString().c_str());
    }
    else
    {
        status_cmd = st_cmd;
        sc_dirb = RE_META_DIVE;
        refreshURL();
    }
}

void ReFirefoxL::scrollUp(int speed, QString st_cmd)
{
    sc_speed = speed-1;
    if( ws_buf.length() )
    {
        sc_dir = RE_META_SKY;
        QString cmd = "bt_speed = ";
        cmd += QString::number(speed_table[sc_speed]) + "; ";
        cmd += "bt_step = ";
        cmd += QString::number(-step_table[sc_speed]) + "; ";
        cmd += "clearInterval(scroll_timer); ";
        cmd += "scroll_timer = undefined;";
        cmd += "var scroll_timer = setInterval(pageScroll, bt_speed);";

        send_js(cmd);
        system(st_cmd.toStdString().c_str());
    }
    else
    {
        status_cmd = st_cmd;
        sc_dirb = RE_META_SKY;
        refreshURL();
    }
}

void ReFirefoxL::scrollEscape()
{
    ws_buf = "";

    QString cmd = "clearInterval(scroll_timer); ";
    cmd += "scroll_timer = undefined;";

    send_js(cmd);
}

void ReFirefoxL::onConnected()
{
   connect(socket, SIGNAL(textMessageReceived(QString)),
           this  , SLOT  (dataReceived(QString)));
   sendScroll();
}

void ReFirefoxL::dataReceived(QString message)
{
    if( cmd_buf.length() )
    {
        QString js_cmd = "{\"id\": 2, \"method\": \"Runtime.evaluate\"";
        js_cmd += ", \"params\": {\"expression\": \"";
        js_cmd += cmd_buf + "\"}}\n";
        cmd_buf = "";
        socket->sendTextMessage(js_cmd);
    }
}

void ReFirefoxL::onDisconnected()
{
//   qDebug() << "WebSocket disconnected";
}

void ReFirefoxL::sendScroll()
{
    QString cmd = "var bt_speed = ";
    cmd += QString::number(speed_table[sc_speed]) + "; ";
    cmd += "bt_step = ";
    if( sc_dirb==RE_META_DIVE )
    {
        cmd += QString::number(step_table[sc_speed]) + "; ";
    }
    else
    {
        cmd += QString::number(-step_table[sc_speed]) + "; ";
    }
    QString filename = JS_SC_PATH;

    QFile file(filename);
    if( file.open(QIODevice::ReadOnly) )
    {
        while( !file.atEnd() )
        {
            QString line = file.readLine();
            line.replace('\n', " ");
            line.replace('\t', " ");
            cmd += line;
        }
        file.close();
    }
    else
    {
        qDebug() << "Error 133: error opening"
                 << filename;
        return;
    }

    send_js(cmd);
    system(status_cmd.toStdString().c_str());
    status_cmd = "";
    sc_dir = sc_dirb;
}

void ReFirefoxL::send_js(QString cmd)
{
    QString en_runtime = "{\"id\": 1, \"method\": \"Runtime.enable\"}\n\n";

    socket->sendTextMessage(en_runtime);
    cmd_buf = cmd;
}
