#include "re_chess.h"
#include <unistd.h>

ReChess::ReChess(ReCaptain *cpt, QObject *parent) : QObject(parent)
{
    captain   = cpt;
    meta_mode = 0;
    persist_mode = 0;
}

ReChess::~ReChess()
{
    ;
}

void ReChess::resetChess()
{
    meta_mode = 0;
    persist_mode = 0;
    captain->state->chess_mode = 0;
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
    if( val==VK_ESCAPE || val==KEY_BACKSPACE )
    {
        sendChessKey(text);
    }
}

void ReChess::super(const QString &text)
{
    int val = text.toInt();
    if( val==RE_SUPER_META && captain->state->chess_mode )
    {
        meta_mode = 1;
        setCount(cmd_count+1);
        sendChessCmd("Meta");
    }
    else if( val==RE_SUPER_KICK   || val==RE_SUPER_COMMENT ||
             val==RE_SUPER_SIDE   || val==RE_SUPER_DOUBLE  ||
             val==RE_SUPER_RESIST || val==RE_SUPER_DRAG )
    {
        showChess(val);
    }
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

    if( cmd_count<max )
    {
        setCount(cmd_count+1);
    }
}

void ReChess::sendChessKey(QString text)
{
    int val = text.toInt();
    QString cmd = "Key_";
    if( val==KEY_ESC )
    {
        meta_mode = 0;
        setCount(0);
        captain->state->chess_mode = 0;
    }
    else if( val==KEY_BACKSPACE )
    {
        handleBackspace();
    }
    else
    {
        setCount(cmd_count-1);
        if( cmd_count==0 )
        {
            resetChess();
        }
    }

    cmd += text;
    sendChessCmd(cmd.toStdString().c_str());
}

void ReChess::showChess(int val)
{
    // This function only on valid val values
    captain->state->chess_mode = 1;
    setCount(2);
    if( val==RE_SUPER_KICK )
    {
        sendChessCmd("show");
    }
    else if( val==RE_SUPER_COMMENT )
    {
        sendChessCmd("comment");
    }
    else if( val==RE_SUPER_SIDE )
    {
        sendChessCmd("side");
    }
    else if( val==RE_SUPER_DOUBLE )
    {
        sendChessCmd("double");
    }
    else if( val==RE_SUPER_RESIST )
    {
        setCount(999); //some large num
        sendChessCmd("persist");
    }
    else if( val==RE_SUPER_DRAG )
    {
        setCount(4);
        drag_mode = CH_DRAG_STATE2;
        sendChessCmd("drag");
    }
}

void ReChess::sendChessCmd(QString cmd)
{
#ifdef WIN32
    QString pipe_data = cmd + CH_NP_SEPARATOR;
    captain->super->sendPipe(pipe_data.toStdString().c_str());
    qDebug() << "pipe" << pipe_data;
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
    cmd_count = val;

    if( cmd_count )
    {
#ifdef WIN32
        QString cmd = "Chess ";
        cmd += QString::number(val);
        cmd  = "%{B#1b8572}%{F#ffffff}  " + cmd;
        cmd += "  %{B- F1-}";
        re_writeStatus(cmd);
#else
        QString cmd = "echo ";
        cmd += QString::number(special_c);
        cmd += " > ~/.config/polybar/awesomewm/ben_spex";
        system(cmd.toStdString().c_str());
#endif
    }
    else
    {
        re_rmSpex();
    }
}
