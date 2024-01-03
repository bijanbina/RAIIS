#include "re_chess.h"
#include <unistd.h>

int ReChess::meta_mode    = 0;
int ReChess::drag_mode    = 0;
int ReChess::persist_mode = 0;
QObject *ReChess::root    = NULL;
CCommand ReChess::mod_cmd;

ReChess::ReChess()
{
}

ReChess::~ReChess()
{
    ;
}

void ReChess::resetChess()
{
    meta_mode = 0;
    persist_mode = 0;
}

void ReChess::nato(const QString &text)
{
    sendChessKey(text);
}

void ReChess::digit(const QString &text)
{
    sendChessKey(text);
}

void ReChess::dirs(const QString &text) // direction keys
{
    int val = text.toInt();
    if( val==KEY_ESC || val==KEY_BACKSPACE )
    {
        sendChessKey(text);
    }
    else if( val==KEY_RIGHT || val==KEY_LEFT )
    {
        sendChessKey(text);
    }
}

void ReChess::super(const QString &text,
                    QVector<CCommand> cmd_buf)
{
    int val = text.toInt();
    if( val==RE_SUPER_META && ReState::ch_count )
    {
        meta_mode = 1;
        addCount(1);
        sendCmd("Meta");
    }
    else if( isChessCmd(text) )
    {
        if( re_isLastMod(cmd_buf) )
        {
            int last_i = cmd_buf.count()-1; //last index
            mod_cmd = cmd_buf[last_i];
            re_modPress(mod_cmd);
        }
        showChess(val);
 ;   }
}

void ReChess::handleBackspace()
{
    int max = 2;
    if( drag_mode==CH_DRAG_STATE2 )
    {
        if( meta_mode )
        {
            max = 5;
        }
        else
        {
            max = 4;
        }
    }
    else if( persist_mode==0 )
    {
        if( meta_mode )
        {
            max = 3;
        }
        else
        {
            max = 2;
        }
    }

    if( ReState::ch_count<max )
    {
        addCount(1);
    }
}

void ReChess::sendChessKey(QString text)
{
    int val = text.toInt();
    QString cmd = "Key_";
    cmd += text;
    sendCmd(cmd.toStdString().c_str());

    if( val==KEY_ESC )
    {
        meta_mode = 0;
        setCount(0);
    }
    else if( val==KEY_BACKSPACE )
    {
        handleBackspace();
    }
    else if( val!=KEY_HOME  && val!=KEY_END &&
             val!=KEY_RIGHT && val!=KEY_LEFT )
    {
        addCount(-1);
    }
}

void ReChess::showChess(int val)
{
    // This function only on valid val values
    setCount(2);
    if( val==RE_SUPER_KICK )
    {
        sendCmd("show");
    }
    else if( val==RE_SUPER_COMMENT )
    {
        sendCmd("comment");
    }
    else if( val==RE_SUPER_SIDE )
    {
        sendCmd("side");
    }
    else if( val==RE_SUPER_DOUBLE )
    {
        sendCmd("double");
    }
    else if( val==RE_SUPER_RESIST )
    {
        setCount(999); //some large num
        sendCmd("persist");
    }
    else if( val==RE_SUPER_DRAG )
    {
        setCount(4);
        drag_mode = CH_DRAG_STATE2;
        sendCmd("drag");
    }
    else if( val==RE_SUPER_SHOT )
    {
        setCount(4);
        sendCmd("screenshot");
    }
    else if( val==RE_SUPER_MAGIC )
    {
        sendCmd("magic");
    }
}

void ReChess::sendCmd(QString cmd, QString arg)
{
#ifdef WIN32
    QString pipe_data = cmd + CH_NP_SEPARATOR + arg;
    RePipe::sendChess(pipe_data.toStdString().c_str());
//    qDebug() << "pipe" << pipe_data;
#else
    QString pipe_data = "dbus-send --dest=com.benjamin.chess";
    pipe_data += "dbus-send --dest=com.benjamin.chess";
    pipe_data += " / com.benjamin.chess.show string:\"";
    pipe_data += cmd + "\"";
    system(pipe_data.toStdString().c_str());
#endif
}

void ReChess::setCount(int val)
{
    ReState::ch_count = val;

    if( val )
    {
#ifdef WIN32
        QString cmd = "Chess ";
        cmd += QString::number(val);
        cmd  = "%{B#1b8572}%{F#ffffff}  " + cmd;
        cmd += "  %{B- F1-}";
        re_writeStatus(cmd);
#else
        QString cmd = "echo ";
        cmd += QString::number(val);
        cmd += " > ~/.config/polybar/awesomewm/ben_spex";
        system(cmd.toStdString().c_str());
#endif
    }
    else
    {
        re_modWait(mod_cmd, 500);
        re_modRelease(mod_cmd);
        mod_cmd.type = RE_COMMAND_NULL;
        re_rmSpex();
        resetChess();

        if( ReState::remote_state )
        {
            ReState::goToRemote();
        }
    }
}

// set count relative
void ReChess::addCount(int val)
{
    int count = ReState::ch_count;
    setCount(count+val);
}

int ReChess::isChessCmd(QString text)
{
    int val = text.toInt();
    if( val==RE_SUPER_KICK   || val==RE_SUPER_COMMENT ||
        val==RE_SUPER_SIDE   || val==RE_SUPER_DOUBLE  ||
        val==RE_SUPER_RESIST || val==RE_SUPER_DRAG    ||
        val==RE_SUPER_MAGIC )
    {
        return 1;
    }

    return 0;
}
