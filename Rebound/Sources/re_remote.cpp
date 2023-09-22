#include "re_remote.h"
#include <unistd.h>
#include "mm_api.h"

ReRemote::ReRemote(RePreProcessor *pre, QObject *parent)
    :QObject(parent)
{
    state = pre->captain->state;
    chess = pre->chess;
    mouse = new ReMetaMos(state);

#ifdef WIN32
    virt = new ReWin32Virt;
#endif

    connect(&tcpClient, SIGNAL(connected()),
            this, SLOT(connected()));
    connect(&tcpClient, SIGNAL(disconnected()),
            this, SLOT(disconnected()));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    connect(this, SIGNAL(dirs(const QString &)),
            pre, SLOT(dirs(const QString &)));
    connect(this, SIGNAL(nato(QString)),
            pre, SLOT(nato(QString)));
    connect(this, SIGNAL(meta(QString)),
            pre, SLOT(meta(QString)));
    connect(this, SIGNAL(apps(QString)),
            pre, SLOT(apps(QString)));
    connect(this, SIGNAL(spex(QString)),
            pre, SLOT(spex(QString)));
    connect(this, SIGNAL(type(QString)),
            pre, SLOT(type(QString)));
    connect(this, SIGNAL(super(QString)),
            pre, SLOT(super(QString)));
    connect(this, SIGNAL(digit(QString)),
            pre, SLOT(digit(QString)));
    connect(this, SIGNAL(debug(QString)),
            pre, SLOT(debug(QString)));
    connect(this, SIGNAL(modifier(QString)),
            pre, SLOT(modifier(QString)));

#ifdef WIN32
    lst = luaL_newstate();
    luaL_openlibs(lst);
#endif

    live = new QTimer;
    watchdog = new QTimer;
    c_timer = new QTimer;

    connect(live, SIGNAL(timeout()),
            this, SLOT(live_timeout()));
    connect(watchdog, SIGNAL(timeout()),
            this, SLOT(connectToHost()));
    connect(c_timer, SIGNAL(timeout()),
            this, SLOT(connectToHost()));
    connect(watchdog, SIGNAL(timeout()),
            this, SLOT(watchdog_timeout()));
    c_timer->start(RE_TIMEOUT);
    connectToHost();
}

ReRemote::~ReRemote()
{
    tcpClient.close();
#ifdef WIN32
    lua_close(lst);
#endif
}

void ReRemote::send(QString word)
{
    qDebug() << "sendRemote" << word;
    if( !tcpClient.isOpen() )
    {
        qDebug() << "Riidi, connecting to: "
                 << RE_CIP << RE_CPORT0;
        tcpClient.connectToHost(QHostAddress(RE_CIP), RE_CPORT0);
    }

    // handle wakeup word
    if( last_word=="system" && word=="romeo" )
    {
        wakeRemote();
    }
    else if( last_word=="go" && word=="sleep" )
    {
        state->remote_state = 0;
        state->goToSleep();
        last_word = word;
        return;
    }
    else if( last_word=="system" )
    {
        if( procSuper(word) )
        {
            last_word = word;
            return;
        }
    }
    else if( last_word=="mouse" )
    {
        if( procMouse(word) )
        {
            last_word = word;
            return;
        }
    }
    else if( last_word=="super" && word=="back" )
    {
        QString cmd_str = "Meta,sound";
        state->sendPipeMom(cmd_str.toStdString().c_str());
    }

    last_word = word;

    // handle mouse commands
    if( procChess(word) )
    {
        return;
    }

    QString data;
    data += "::" + word + "\n";

//    live->start(RE_LIVE);//don't send live
    tcpClient.write(data.toStdString().c_str());
//    live->start(RE_LIVE);//don't send live
}

void ReRemote::displayError(QAbstractSocket::SocketError socketError)
{
    if( socketError==QTcpSocket::RemoteHostClosedError )
    {
        return;
    }

    qDebug() << "Network error:" << tcpClient.errorString();
    tcpClient.close();

    if ( !(c_timer->isActive()) )
    {
        c_timer->start(RE_TIMEOUT);
        qDebug() << "Timer start";
    }
}

void ReRemote::connected()
{
    qDebug() << "Remote: Connected";
    tcpClient.setSocketOption(QAbstractSocket::LowDelayOption, 1);
    connect(&tcpClient, SIGNAL(readyRead()), this, SLOT(readyRead()));
//    watchdog->start(RE_WATCHDOG);
//    live->start(RE_LIVE);
}

void ReRemote::disconnected()
{
    watchdog->stop();
    live->stop();
    tcpClient.close();

    if ( !(c_timer->isActive()) )
    {
        c_timer->start(RE_TIMEOUT);
        qDebug() << "Remote: Timer start";
    }
    qDebug() << "Remote: Disconnected";
}

void ReRemote::readyRead()
{
    QString read_data = tcpClient.readAll();
    if( read_data=="Live" )
    {
//        watchdog->start(RE_WATCHDOG);
        return;
    }

    if( read_data.size()==0 )
    {
        return;
    }

//    watchdog->start(RE_WATCHDOG);

    if( read_data.contains("Live") )
    {
        read_data.replace("Live", "");
        if( read_data.size()==0 )
        {
            return;
        }
    }

    read_data = read_data.trimmed();
    QStringList data_lines = read_data.split("\n", Qt::SkipEmptyParts);

    int len = data_lines.size();
    QStringList data_split;
    for( int i=0 ; i<len ; i++ )
    {
        data_split = data_lines[i].split("::", Qt::SkipEmptyParts);
        if( data_split.size()!=1 )
        {
            qDebug() << "wrong input size:" << data_split.size();
            return;
        }
        QString word = data_split[0];
        runLua(word);
    }
}

void ReRemote::processCommand(QString k_type, QString k_code)
{
    if( k_type=="dirs" )
    {
        emit dirs(k_code);
    }
    else if( k_type=="nato" )
    {
        emit nato(k_code);
    }
    else if( k_type=="meta" )
    {
        emit meta(k_code);
    }
    else if( k_type=="apps" )
    {
        emit apps(k_code);
    }
    else if( k_type=="spex" )
    {
        emit spex(k_code);
    }
    else if( k_type=="type" )
    {
        emit type(k_code);
    }
    else if( k_type=="super" )
    {
        emit super(k_code);
    }
    else if( k_type=="digit" )
    {
        emit digit(k_code);
    }
    else if( k_type=="debug" )
    {
        emit debug(k_code);
    }
    else if( k_type=="modifier" )
    {
        emit modifier(k_code);
    }
}

void ReRemote::runLua(QString word)
{
#ifdef WIN32
    ///FIXME: solve directory problem
    QString current_dir = QDir::currentPath();
    QDir::setCurrent(KAL_SI_DIR_WIN);

    luaL_loadfile(lst, "main_w.lua");

    lua_pushstring(lst, word.toStdString().c_str());
    lua_setglobal(lst, "in_word");
    lua_pcall(lst, 0, LUA_MULTRET, 0);

    lua_getglobal(lst, "output");
    int output = lua_tonumber(lst, -1);

    lua_getglobal(lst, "k_type");
    QString ktype = lua_tostring(lst, -1);

    qDebug() << "LUA : " << output << ktype;

    //Always send debug first
    QString k_code = QString::number(output);
    processCommand(ktype, k_code);

    QDir::setCurrent(current_dir);
#else
    cmd = KAL_SI_DIR"main_l.sh \"";
    cmd += word;
    cmd += "\"";
    system(cmd.toStdString().c_str());
#endif

}

void ReRemote::wakeRemote()
{
    state->remote_state = 0;
    state->wakeUp();
}

int ReRemote::procChess(QString word)
{
    int val = 0;
    if( word=="kick" )
    {
        val = 104;
    }
    else if( word=="comment" )
    {
        val = 105;
    }
    else if( word=="side" )
    {
        val = 108;
    }
    else if( word=="double" )
    {
        val = 113;
    }
    else if( word=="resist" )
    {
        val = 111;
    }
    else if( word=="drag" )
    {
        val = 115;
    }

    if( val )
    {
        chess->showChess(val);
        return 1;
    }
    return 0;
}

int ReRemote::procSuper(QString word)
{
    int val = 0;
    if( word=="one" )
    {
        val = 1;
    }
    else if( word=="two" )
    {
        val = 2;
    }
    else if( word=="three" )
    {
        val = 3;
    }
    else if( word=="four" )
    {
        val = 4;
    }
    else if( word=="five" )
    {
        val = 5;
    }
    else if( word=="six" )
    {
        val = 6;
    }
    else if( word=="quebec" )
    {
        mm_closeWindow();
        return 1;
    }
    else if( word=="sierra" )
    {
        chess->showChess(RE_SUPER_SHOT);
        return 1;
    }

    if( val )
    {
        virt->setDesktop(val-1);
        virt->setFocus();
        wakeRemote();
        return 1;
    }
    return 0;
}

int ReRemote::procMouse(QString word)
{
    int val = 0;

    if( word=="left" )
    {
        re_mouseKey(1);
        return 1;
    }
    else if( word=="right" )
    {
        re_mouseKey(3);
        return 1;
    }
    else if( word=="u" )
    {
        val = KEY_U;
    }
    else if( word=="delta" )
    {
        val = KEY_D;
    }
    else if( word=="golf" )
    {
        val = KEY_G;
    }
    else if( word=="hotel" )
    {
        val = KEY_H;
    }

    if( val )
    {
        mouse->castScroll(val);
        return 1;
    }
    return 0;
}

void ReRemote::connectToHost()
{
    if( tcpClient.isOpen()==0 )
    {
        qDebug() << "TimerTick, connecting to: " << RE_IP << RE_PORT;
#ifdef RE_REMOTE
        tcpClient.connectToHost(QHostAddress(RE_CIP), RE_CPORT1 );
#else
        tcpClient.connectToHost(QHostAddress(RE_CIP), RE_CPORT0 );
#endif

    }
    else if( tcpClient.state()==QAbstractSocket::ConnectingState )
    {
        qDebug() << "TimerTick, Connecting";
    }
    else if( tcpClient.state()!=QAbstractSocket::ConnectedState )
    {
        qDebug() << "TimerTick State:" << tcpClient.state();
    }
}

void ReRemote::watchdog_timeout()
{
    if( tcpClient.isOpen() )
    {
        qDebug() << "Remote: connection dropped:"
                 << tcpClient.state();
        disconnected();
    }
    else
    {
        qDebug() << "Remote: watchdog, tcpClient is closed";
    }
}

void ReRemote::live_timeout()
{
    if( tcpClient.isOpen() )
    {
        if( tcpClient.state()==QAbstractSocket::ConnectedState )
        {
            tcpClient.write("Live");
            tcpClient.waitForBytesWritten(50);
        }
        else
        {
            qDebug() << "Remote: live, not connected, State:"
                     << tcpClient.state();
        }
    }
    else
    {
        qDebug() << "Remote: live, tcpClient is closed";
    }
}
