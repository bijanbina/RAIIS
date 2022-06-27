#include "re_qt.h"

void re_qtDigitProc(QVector<CCommand> *cmd_buf, QString text)
{
    if( cmd_buf->count()==0 )
    {
        CCommand cmd;
        cmd.val1 = 0;
        cmd.val2 = re_keyCode2Digit(text);
        cmd.type = RE_COMMAND_QDIGIT;
        re_updateQtState(cmd.val2);

        cmd_buf->append(cmd);
        return;
    }

    int last_i = cmd_buf->count()-1; //last index
    int cmd_type = cmd_buf->at(last_i).type;

    if( cmd_type==RE_COMMAND_QDIGIT )
    {
        (*cmd_buf)[last_i].val2 *= 10;
        (*cmd_buf)[last_i].val2 += re_keyCode2Digit(text);
        re_updateQtState((*cmd_buf)[last_i].val2);

        return;
    }
    else
    {
        CCommand cmd;
        cmd.val1 = 0;
        cmd.val2 = re_keyCode2Digit(text);
        cmd.type = RE_COMMAND_QDIGIT;
        re_updateQtState(cmd.val2);

        cmd_buf->append(cmd);
        return;
    }
}

bool re_qtDirProc(QVector<CCommand> *cmd_buf, QString text)
{
    if( re_isLastQt(*cmd_buf) )
    {
        int key = text.toInt();
        int last_i = cmd_buf->count()-1; //last index

        if( key==KEY_BACKSPACE )
        {
            system("xdotool key BackSpace");
            (*cmd_buf)[last_i].val2 /= 10;

            if( (*cmd_buf)[last_i].val2==0 )
            {
                system("rm ~/.config/polybar/awesomewm/ben_status");
                cmd_buf->pop_back();
            }
            else
            {
                re_updateQtState((*cmd_buf)[last_i].val2);
            }
            return true;
        }
        cmd_buf->pop_back();
        system("rm ~/.config/polybar/awesomewm/ben_status");
    }
    return false;
}

void re_updateQtState(int buf)
{
    QString cmd = "echo '";
    cmd += QString::number(buf);
    cmd += "' > ~/.config/polybar/awesomewm/ben_status";
    system(cmd.toStdString().c_str());
}

void re_getQtCmd(CCommand val)
{
    QString cmd;

    if( val.val1==RE_META_CLOSE )
    {
        cmd = re_getCloseQt(val.val2);
    }
    else if( val.val1==RE_META_OPEN )
    {
        cmd = re_getOpenQt(val.val2);
    }
    else
    {
        return;
    }

    system(cmd.toStdString().c_str());
}

QString re_getOpenQt(int val)
{
    system("rm ~/.config/polybar/awesomewm/ben_status");
    QString cmd;

    cmd = "xdotool key Enter";
    return cmd;
}

QString re_getCloseQt(int val)
{
    QString cmd;

    cmd = re_getOpenQt(val);
    cmd += "; sleep 0.3;";
    cmd += "xdotool key End";
    return cmd;
}
