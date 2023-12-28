#include "re_firefox.h"
#define JS_SC_PATH "Scripts/Firefox/ElementsWithScrolls.js"
#define VI_SC_PATH "Scripts/Firefox/isVisible.sh"

ReFirefox::ReFirefox(QObject *parent) : QObject(parent)
{
    socket = new QWebSocket;
    connect(socket, SIGNAL(connected()),
            this, SLOT(onConnected()));
    connect(socket, SIGNAL(disconnected()),
            this, SLOT(onDisconnected()));
    ws_buf = "";
    lua = new ReLua;
#ifdef WIN32
    pipe_firefox = connectPipe(RE_PIPE_FIREFOX);
#endif
}

ReFirefox::~ReFirefox()
{
    delete socket;
    reset();
}

void ReFirefox::refreshURL()
{
    QStringList ws_list = lua->getWSList();
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
void ReFirefox::urlCheck(QString title, QString ws)
{
#ifdef  __linux__
    QString cmd = VI_SC_PATH " \"";
    cmd += title + "\"";
    QString res = getStrCommand(cmd);

    if( res.isEmpty() )
    {
        return;
    }
#endif
    ws_buf = ws;
    socket->open(QUrl(ws));
    qDebug() << "urlCheck:" << ws;
    reset();
}

void ReFirefox::reset()
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

void ReFirefox::scrollDown(int speed, QString st_cmd)
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
#ifdef __linux__
        system(st_cmd.toStdString().c_str());
#endif
    }
    else
    {
        status_cmd = st_cmd;
        sc_dirb = RE_META_DIVE;
        refreshURL();
    }
}

void ReFirefox::scrollUp(int speed, QString st_cmd)
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
#ifdef __linux__
        system(st_cmd.toStdString().c_str());
#endif
    }
    else
    {
        status_cmd = st_cmd;
        sc_dirb = RE_META_SKY;
        refreshURL();
    }
}

void ReFirefox::scrollEscape()
{
    ws_buf = "";

    QString cmd = "clearInterval(scroll_timer); ";
    cmd += "scroll_timer = undefined;";

    send_js(cmd);
}

void ReFirefox::onConnected()
{
   connect(socket, SIGNAL(textMessageReceived(QString)),
           this  , SLOT  (dataReceived(QString)));
   sendScroll();
}

void ReFirefox::dataReceived(QString message)
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

void ReFirefox::onDisconnected()
{
//   qDebug() << "WebSocket disconnected";
}

void ReFirefox::sendScroll()
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
            line.replace('\r', " ");
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
#ifdef __linux__
    system(status_cmd.toStdString().c_str());
#endif
    status_cmd = "";
    sc_dir = sc_dirb;
}

void ReFirefox::send_js(QString cmd)
{
    QString en_runtime = "{\"id\": 1, \"method\": \"Runtime.enable\"}\n\n";

    socket->sendTextMessage(en_runtime);
    cmd_buf = cmd;

#ifdef WIN32
//    sendPipe(cmd.toStdString().c_str());
#else
    ///FIXME: Implement for unix too
#endif
}

#ifdef WIN32
HANDLE ReFirefox::connectPipe(const char *pipe_name)
{
    // 0: Default Wait Time
    int ready = WaitNamedPipeA(pipe_name, 0);
    HANDLE hPipe;
    if( ready )
    {
        hPipe = CreateFileA(pipe_name, GENERIC_WRITE, // dwDesiredAccess
                            0, nullptr,    // lpSecurityAttributes
                            OPEN_EXISTING,  // dwCreationDisposition
                            0, nullptr);    // hTemplateFile

        if( hPipe==INVALID_HANDLE_VALUE )
        {
            qDebug() << "Error 120: Cannot connect"
                     << pipe_name;
        }
    }
    else
    {
        hPipe = INVALID_HANDLE_VALUE;
        qDebug() << "Error 121: Pipe "
                 << pipe_name << " not found";
    }

    return hPipe;
}

void ReFirefox::sendPipe(const char *data)
{
    DWORD len = strlen(data);
    if( pipe_firefox==INVALID_HANDLE_VALUE )
    {
        qDebug() << "Try to reconnect to"
                 << RE_PIPE_FIREFOX;

        pipe_firefox = connectPipe(RE_PIPE_FIREFOX);
        if( pipe_firefox==INVALID_HANDLE_VALUE )
        {
            return;
        }
    }

    DWORD dwWritten;
    int success = WriteFile(pipe_firefox, data, len, &dwWritten, NULL);
    if( !success )
    {
        qDebug() << "Error: NamedPipe writing failed," << GetLastError();
    }

    if( dwWritten!=len )
    {
        qDebug() << "Error: Wrong writing length."
                    "Try to revive channel";
        CloseHandle(pipe_firefox);
        pipe_firefox = INVALID_HANDLE_VALUE;
        sendPipe(data);
    }
}
#endif
