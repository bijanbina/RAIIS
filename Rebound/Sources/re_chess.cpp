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
    sendKeyChess(text);
}

void ReChess::digit(const QString &text)
{
    sendKeyChess(text);
}

void ReChess::dirs(const QString &text) // direction keys
{
    sendKeyChess(text);
}

void ReChess::super(const QString &text)
{
    int val = text.toInt();
    if( val==RE_SUPER_META )
    {
        meta_mode = 1;
        cmd_count = 3;
        captain->super->sendPipe("Meta");
    }
}

void ReChess::sendKeyChess(QString text)
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
