#include "re_remote.h"
#include <unistd.h>
#include <QColor>
#include "mm_api.h"

ReRemote::ReRemote(RePreProcessor *pre, QObject *parent)
    :QObject(parent)
{
    ReState::remote_id = ini_getRemoteId();
    is_last_mouse      = 0;
    last_history_count = 0;

#ifdef WIN32
    ReVirtualW::init();
#endif

    connect(this, SIGNAL(dirs(const QString &)),
            pre, SLOT(dirs(const QString &)));
    connect(this, SIGNAL(nato(QString)),
            pre, SLOT(nato(QString)));
    connect(this, SIGNAL(meta(QString)),
            pre, SLOT(meta(QString)));
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

    timer_history = new QTimer;
    connect(timer_history, SIGNAL(timeout()),
            this, SLOT(shiftHistory()));
    timer_history->start(BT_HISTORY_UPDATE);

    apache_rx = new ReApacheCl;
    apache_tx = new ReApacheCl;

    connect(apache_rx, SIGNAL(readyRead(QString)),
            this, SLOT(readyRead(QString)));
    apache_rx->start(RE_CIP, RE_CPORT1);
    apache_tx->start(RE_CIP, RE_CPORT0);
}

ReRemote::~ReRemote()
{
#ifdef WIN32
    lua_close(lst);
#endif
}

void ReRemote::send(QString word)
{
    qDebug() << "sendRemote"
             << ReState::rust_id << word;

    if( word=="go" || word=="system" || word=="mouse" )
    {
        last_word = word;
        return;
    }
    if( procSpecialKey(word) )
    {
        return;
    }

    last_word = word;

    // handle mouse commands
    if( procChess(word) )
    {
        return;
    }

    QString data = QString::number(ReState::rust_id) + "::";
    data += word + "\n";
    apache_tx->write(data);
}

void ReRemote::readyRead(QString read_data)
{
    read_data = read_data.trimmed();
    QStringList data_lines = read_data.split("\n", Qt::SkipEmptyParts);

    int len = data_lines.size();
    QStringList data_split;
    for( int i=0 ; i<len ; i++ )
    {
        data_split = data_lines[i].split("::", Qt::SkipEmptyParts);
        if( data_split.size()!=2 )
        {
            qDebug() << "wrong input size:" << data_split.size();
            return;
        }

        QString rx_id = data_split[0];
        if( rx_id.toInt()!=ReState::remote_id )
        {
            return;
        }

        QString word = data_split[1];
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

    qDebug() << "LUA:" << output << ktype;

    //Always send debug first
    QString k_code = QString::number(output);
    processCommand(ktype, k_code);

    QDir::setCurrent(current_dir);
#else
    QString cmd = KAL_SI_DIR"/main_l.sh \"";
    cmd += word;
    cmd += "\"";
    system(cmd.toStdString().c_str());
#endif

    BtHistory tmp;
    tmp.time = time(NULL);
    tmp.word = word;
    history.append(tmp);
    writeResult();
}

void ReRemote::wakeRemote()
{
    ReState::remote_state = 0;
    ReState::wakeUp();
}

int ReRemote::procChess(QString word)
{
    if( word=="kick"    || word=="comment" || word=="side" ||
        word=="double"  || word=="touch"   || word=="drag" )
    {
        if( word=="kick" )
        {
            ReChess::sendCmd("system", "left");
        }
        else
        {
            ReChess::sendCmd("system", word);
        }
        if( word=="touch" )
        {
            ReChess::setCount(999); //some large num
        }
        else if( word=="drag")
        {
            ReChess::setCount(4);
        }
        else
        {
            ReChess::setCount(2);
        }
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
    else if( word=="free" )
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
#ifdef WIN32
    else if( word=="quebec" )
    {
        mm_closeWindow();
        return 1;
    }
    else if( word=="sierra" )
    {
        ReChess::showChess(RE_CHESS_SHOT);
        return 1;
    }
    else if( word=="back" )
    {
        RePipe::sendMom("super sound");
        return 1;
    }

    if( val )
    {
        ReVirtualW::setDesktop(val-1);
        ReVirtualW::setFocus();
        wakeRemote();
        return 1;
    }
#endif
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
    else if( word=="raise" )
    {
        re_mouseKey(4);
        return 1;
    }
    else if( word=="down" )
    {
        re_mouseKey(5);
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
        ReMetaMos::castScroll(val);
        return 1;
    }
    return 0;
}

void ReRemote::writeResult()
{
    if( history.length()==0 && last_history_count==0 )
    {
        return;
    }
#ifdef WIN32
    QString bar_path = BT_BAR_DIR_WS;
    bar_path += BT_BAR_RESULT_WS;
#else
    QString bar_path = getenv("HOME");
    bar_path += "/.config/polybar/awesomewm/";
    bar_path += BT_BAR_RESULT;
#endif

    QFile bar_file(bar_path);
    if( !bar_file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Error creating" << bar_path;
#ifdef WIN32
        qDebug() << "Trying to create" << BT_BAR_DIR_WS;
        system("mkdir " BT_BAR_DIR_WS);
#endif
        return;
    }

    QTextStream out(&bar_file);
    last_history_count = history.length();
    for( int i=0 ; i<history.length() ; i++ )
    {
        out << "%{F#ddd}%{u";
        out << QColor::fromHsv(150, 200, 200).name();
        out << "}%{+u}";
        out << history[i].word;
        out << "%{-u} ";
    }

    out << "\n";

    bar_file.close();
}

void ReRemote::shiftHistory()
{
    time_t start_treshold = time(NULL)-10;

    for( int i=0 ; i<history.length() ; i++ )
    {
        if( (history[i].time<start_treshold) || //5 second history size
            (history.length()>BT_HISTORY_LEN) ) // max len = 8
        {
            history.remove(i);
            i--;
        }
    }

    writeResult();
}

int ReRemote::procSpecialKey(QString word)
{
    if( word=="last" || word=="front" )
    {
        last_word = word;
        re_mouseMoveC(0, 0);
        procScroll(word);
        return 1;
    }
    else if( last_word=="system" )
    {
        if( word=="down" )
        {
            ReState::remote_state = 0;
            ReState::goToSleep();
            last_word = word;
            return 1;
        }
        else if( procSuper(word) )
        {
            last_word = word;
            return 1;
        }
    }
    else if( last_word=="mouse" )
    {
        if( procMouse(word) )
        {
            last_word = word;
            is_last_mouse = 1;
            return 1;
        }
    }
#ifdef WIN32
    else if( last_word=="super" && word=="back" )
    {
        QString cmd_str = "Meta,sound";
        RePipe::sendMom(cmd_str.toStdString().c_str());
        return 1;
    }
    else if( is_last_mouse )
    {
        int val = procDigit(word);
        if( val )
        {
            for( int i=0 ; i<val-1 ; i++ )
            {
                procMouse(last_word);
            }
            return 1;
        }
    }
    else if( last_word=="last" || last_word=="front" )
    {
        int val = procDigit(word);
        if( val )
        {
            for( int i=0 ; i<val-1 ; i++ )
            {
                procScroll(last_word);
            }
            return 1;
        }
    }
#endif
    is_last_mouse = 0;
    return 0;
}

int ReRemote::procDigit(QString word)
{
    if( word=="one" )
    {
        return 1;
    }
    else if( word=="two" )
    {
        return 2;
    }
    else if( word=="free" )
    {
        return 3;
    }
    else if( word=="four" )
    {
        return 4;
    }
    else if( word=="five" )
    {
        return 5;
    }
    else if( word=="six" )
    {
        return 6;
    }
    else if( word=="seven" )
    {
        return 7;
    }
    else if( word=="eight" )
    {
        return 8;
    }
    else if( word=="nine" )
    {
        return 9;
    }

    return 0;
}

void ReRemote::procScroll(QString word)
{
    int count = 6;
    if( word=="last" )
    {
        for( int j=0 ; j<count ; j++ )
        {
            re_mouseKey(5);
        }
    }
    else if( word=="front" )
    {
        for( int j=0 ; j<count ; j++ )
        {
            re_mouseKey(4);
        }
    }

}

