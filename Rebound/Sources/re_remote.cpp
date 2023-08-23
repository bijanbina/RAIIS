#include "re_remote.h"
#include <unistd.h>

ReRemote::ReRemote(RePreProcessor *pre, QObject *parent)
    :QObject(parent)
{
    state = pre->captain->state;

    connect(&tcpClient, SIGNAL(connected()),
            this, SLOT(connected()));
    connect(&tcpClient, SIGNAL(disconnected()),
            this, SLOT(disconnected()));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
#ifdef RE_REMOTE
    tcpClient.connectToHost(QHostAddress(RE_CIP), RE_CPORT1 );
#else
    tcpClient.connectToHost(QHostAddress(RE_CIP), RE_CPORT0 );
#endif

    connect(this, SIGNAL(dirs(const QString &)),
            pre, SLOT(dirs(const QString &)));
    connect(this, SIGNAL(nato(QString)),
            pre, SLOT(nato(QString)));
    connect(this, SIGNAL(meta(QString)), pre, SLOT(meta(QString)));
    connect(this, SIGNAL(apps(QString)), pre, SLOT(apps(QString)));
    connect(this, SIGNAL(spex(QString)), pre, SLOT(spex(QString)));
    connect(this, SIGNAL(type(QString)), pre, SLOT(type(QString)));
    connect(this, SIGNAL(super(QString)), pre, SLOT(super(QString)));
    connect(this, SIGNAL(digit(QString)), pre, SLOT(digit(QString)));
    connect(this, SIGNAL(debug(QString)), pre, SLOT(debug(QString)));
    connect(this, SIGNAL(modifier(QString)),
            pre, SLOT(modifier(QString)));

#ifdef WIN32
    lst = luaL_newstate();
    luaL_openlibs(lst);
#endif
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
    if(!tcpClient.isOpen())
    {
        qDebug() << "Riidi, connecting to: " << RE_CIP << RE_CPORT0;
        tcpClient.connectToHost(QHostAddress(RE_CIP), RE_CPORT0 );
    }

    if( last_word=="system" && word=="romeo" )
    {
        wakeRemote();
    }
    last_word = word;
    QString data;
    data += "::" + word + "\n";

    tcpClient.write(data.toStdString().c_str());
}

void ReRemote::displayError(QAbstractSocket::SocketError socketError)
{
    if( socketError==QTcpSocket::RemoteHostClosedError )
    {
        return;
    }

    qDebug() << "Network error:" << tcpClient.errorString();
    tcpClient.close();
}

void ReRemote::connected()
{
    qDebug() << "Client: Connected";
    tcpClient.setSocketOption(QAbstractSocket::LowDelayOption, 1);
    connect(&tcpClient, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void ReRemote::disconnected()
{
    tcpClient.close();
    qDebug() << "Client: Disconnected";
}

void ReRemote::readyRead()
{
    QString read_data = tcpClient.readAll();
    if( read_data.size()==0 )
    {
        return;
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
            qDebug() << "SHIR TUT" << data_split.size();
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
