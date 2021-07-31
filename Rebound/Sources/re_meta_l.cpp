#include "re_meta_l.h"

ReMetaL::ReMetaL(ReState *st, QObject *parent): QObject(parent)
{
    state = st;
}

ReMetaL::~ReMetaL()
{
    ;
}

void ReMetaL::execMeta(CaptainCommand command)
{
    if( command.val2==0 )
    {
        if( command.val1==RE_META_WAKE )
        {
//                sendKey(command.val1);
        }
        return;
    }

    if( command.val1==RE_META_OPEN )
    {
        QString cmd = "./Scripts/open ";
        cmd += QString::number(command.val2)+ " &";
        system(cmd.toStdString().c_str());
    }
    else if( command.val1==RE_META_SYS )
    {
        QString cmd = getSystemCmd(command.val2);

        if( command.val3==0 )
        {
            command.val3 = 1; //change default to 1
        }

        for( int j=0 ; j<command.val3 ; j++ )
        {
            system(cmd.toStdString().c_str());
        }
    }
    else if( command.val1==RE_META_WAKE )
    {

    }
    else if( command.val1==RE_META_START )
    {

    }
    else if( command.val1==RE_META_PAGE )
    {

    }
    else if( command.val1==RE_META_GO )
    {

    }
    else if( command.val1==RE_META_SKY ||
             command.val1==RE_META_DIVE )
    {
        QString cmd = getScrollCmd(state->scroll_mode,
                                   command.val1, command.val2);

        if( state->scroll_mode==0 )
        {
            state->scroll_mode = 1;
        }
        system(cmd.toStdString().c_str());
    }
    else if( command.val1==RE_META_MUSIC )
    {
        QString cmd = getMusicCmd(command.val2);

        if( command.val3==0 )
        {
            command.val3 = 1; //change default to 1
        }

        for( int j=0 ; j<command.val3 ; j++ )
        {
            system(cmd.toStdString().c_str());
        }
    }
}

QString ReMetaL::getSystemCmd(int val)
{
    QString cmd = "xdotool key ";

    if( val==KEY_ENTER )
    {
        cmd += "org.mpris.MediaPlayer2.Player.PlayPause";
    }
    else if( val==KEY_LEFT )
    {
        cmd += "Ctrl+Alt+Left";
    }
    else if( val==KEY_RIGHT )
    {
        cmd += "Ctrl+Alt+Right";
    }
    else
    {
        qDebug() << "Unknown Music" << val;
    }

    return cmd;
}

QString ReMetaL::getMusicCmd(int val)
{
    QString cmd = "dbus-send --print-reply --dest="
                  "org.mpris.MediaPlayer2.spotify "
                  "/org/mpris/MediaPlayer2 ";

    if( val==KEY_ENTER )
    {
        cmd += "org.mpris.MediaPlayer2.Player.PlayPause";
    }
    else if( val==KEY_LEFT )
    {
        cmd += "org.mpris.MediaPlayer2.Player.Previous";
    }
    else if( val==KEY_RIGHT )
    {
        cmd += "org.mpris.MediaPlayer2.Player.Next";
    }
    else
    {
        qDebug() << "Unknown Music" << val;
    }

    cmd += " >/dev/null";

    return cmd;
}

QString ReMetaL::getScrollCmd(bool scroll_mode, int meta, int val)
{
    QString change_gear;
    QString direction;
    QString cmd = "./Scripts/scroll";
    if( scroll_mode )
    {
        change_gear = " 0 ";
    }
    else
    {
        change_gear = " 1 ";
    }

    if( meta==RE_META_SKY )
    {
        direction = " up ";
    }
    else if( meta==RE_META_DIVE )
    {
        direction = " down ";
    }

    cmd += direction;
    cmd += change_gear;
    cmd += QString::number(val);

    return cmd;
}
