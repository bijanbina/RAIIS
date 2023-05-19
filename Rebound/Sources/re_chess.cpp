#include "re_chess.h"
#include <unistd.h>

ReChess::ReChess(ReCaptain *cpt, QObject *parent) : QObject(parent)
{
    captain = cpt;
    meta_mode = 0;
}

ReChess::~ReChess()
{
    ;
}

void ReChess::resetChess()
{
    meta_mode = 0;
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
    sendChessKey(text);
}

void ReChess::super(const QString &text)
{
    int val = text.toInt();
    if( val==RE_SUPER_META && captain->state->chess_mode )
    {
        meta_mode = 1;
        cmd_count = 3;
        captain->super->sendPipe("Meta");
    }
    else if( val==RE_SUPER_KICK   || val==RE_SUPER_COMMENT ||
             val==RE_SUPER_SIDE   || val==RE_SUPER_DOUBLE  ||
             val==RE_SUPER_RESIST || val==RE_SUPER_DRAG )
    {
        showChess(val);
    }
}

void ReChess::sendChessKey(QString text)
{
    int val = text.toInt();
    QString cmd = "Key_";
    if( val==KEY_ESC )
    {
        meta_mode = 0;
        cmd_count = 0;
        captain->state->chess_mode = 0;
    }
    else
    {
        cmd_count--;
        if( cmd_count==0 )
        {
            resetChess();
        }
    }

    cmd += text;
    captain->super->sendPipe(cmd.toStdString().c_str());
}

void ReChess::showChess(int val)
{
    if( val==RE_SUPER_KICK )
    {
        captain->state->chess_mode = 1;
        sendChessCmd("show");
    }
    else if( val==RE_SUPER_COMMENT )
    {
        captain->state->chess_mode = 1;
        sendChessCmd("comment");
    }
    else if( val==RE_SUPER_SIDE )
    {
        captain->state->chess_mode = 1;
        sendChessCmd("side");
    }
    else if( val==RE_SUPER_DOUBLE )
    {
        captain->state->chess_mode = 1;
        sendChessCmd("double");
    }
    else if( val==RE_SUPER_RESIST )
    {
        captain->state->chess_mode = 1;
        sendChessCmd("persist");
    }
    else if( val==RE_SUPER_DRAG )
    {
        sendChessCmd("drag");
    }
}

void ReChess::sendChessCmd(QString cmd)
{
#ifdef WIN32
    QString pipe_data = cmd + CH_NP_SEPARATOR;
    captain->super->sendPipe(pipe_data.toStdString().c_str());
#else
    QString pipe_data = "dbus-send --dest=com.benjamin.chess";
    pipe_data += "dbus-send --dest=com.benjamin.chess";
    pipe_data += " / com.benjamin.chess.show string:\"";
    pipe_data += cmd + "\"";
    system(pipe_data.toStdString().c_str());
#endif
}
