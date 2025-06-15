#include "re_chess.h"
#include <unistd.h>

int ReChess::drag_mode    = 0;
int ReChess::magic_mode   = 0;
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
    sendChessKey(text);
}

void ReChess::meta(const QString &text)
{
    sendChessKey(text);
}

// only call on isChessCmd(text)==true
void ReChess::super(const QString &text,
                    QVector<CCommand> cmd_buf)
{
    if( re_isLastMod(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index
        mod_cmd = cmd_buf[last_i];
        re_modPress(mod_cmd);
    }
    int val = text.toInt();
    showChess(val);
}

void ReChess::handleBackspace()
{
    int max = 2;
    if( drag_mode==CH_DRAG_STATE2 )
    {
        max = 4;
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
    qDebug() << "val" << val;
    sendCmd(cmd.toStdString().c_str());

    if( val==KEY_ESC )
    {
        setCount(0);
    }
    else if( magic_mode )
    {
        addCount(-1);
    }
    else if( val==KEY_BACKSPACE )
    {
        handleBackspace();
    }
    else if( val!=KEY_HOME  && val!=KEY_END &&
             val!=KEY_RIGHT && val!=KEY_LEFT &&
             30<val && val<240 )
    {
        addCount(-1);
    }
}

void ReChess::showChess(int val)
{
    // This function only on valid val values
    setCount(2);
    magic_mode = 0;
    if( val==RE_SUPER_KICK )
    {
        sendCmd("show");
    }
    else if( val==RE_SUPER_COMMENT )
    {
        sendCmd("no_click");
    }
    else if( val==RE_SUPER_SIDE )
    {
        sendCmd("side");
    }
    else if( val==RE_SUPER_DOUBLE )
    {
        sendCmd("double");
    }
    else if( val==RE_SUPER_TOUCH )
    {
        setCount(999); //some large num
        sendCmd("touch");
    }
    else if( val==RE_SUPER_DRAG )
    {
        setCount(4);
        drag_mode = CH_DRAG_STATE2;
        sendCmd("drag");
    }
    else if( val==RE_SUPER_HOOLEY )
    {
        setCount(2);
        sendCmd("hover");
    }
    else if( val==RE_SUPER_SHOT )
    {
        setCount(4);
        sendCmd("screenshot");
    }
    else if( val==RE_SUPER_MAGIC )
    {
        sendCmd("magic");
        setCount(1);
        magic_mode = 1;
    }
    else if( val==RE_SUPER_JAMES )
    {
        sendCmd("james");
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
        magic_mode = 0;

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
    if( val==RE_SUPER_KICK  || val==RE_SUPER_COMMENT ||
        val==RE_SUPER_SIDE  || val==RE_SUPER_DOUBLE  ||
        val==RE_SUPER_TOUCH || val==RE_SUPER_DRAG    ||
        val==RE_SUPER_MAGIC || val==RE_SUPER_DRAG )
    {
        return 1;
    }
    if( ReState::ch_count && val==RE_SUPER_JAMES )
    {
        return 1;
    }

    return 0;
}

int ReChess::isValidChess(QString text)
{
    int val = text.toInt();
    if( val==RE_SUPER_LAST || val==RE_SUPER_FRONT )
    {
        return 0;
    }
    if( isChessCmd(text) && magic_mode==0 )
    {
        return 0;
    }

    return 1;
}
