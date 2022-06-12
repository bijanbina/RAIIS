#include "re_meta_oc_l.h"

void re_digitQtProc(QVector<CCommand> *cmd_buf, QString text)
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

bool re_dirQtProc(QVector<CCommand> *cmd_buf, QString text)
{
    if( re_isLastQt(*cmd_buf) )
    {
        int key = text.toInt();
        int last_i = cmd_buf->count()-1; //last index

        if( key==KEY_BACKSPACE )
        {
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

QString re_getOpenCmd(ReState *state, int val)
{
    QString cmd;

    qDebug() << "Open" << state->app.pname;

    if( state->app.pname=="xed" )
    {
        cmd = re_getOpenXed(val);
    }
    else if( state->app.pname=="qtcreator" ||
             state->app.pname=="code-oss" )
    {
        cmd = re_getOpenQt(val);
    }
    else if( state->app.pname=="gitkraken" )
    {
        cmd = re_getOpenGitKraken(val);
    }
    else if( state->app.pname=="GeckoMain" ||
             state->app.pname=="firefox" )
    {
        cmd = re_getOpenFirefox(val);
    }
    else if( state->app.pname=="nautilus" )
    {
        cmd = re_getOpenNautilus(val);
    }

    return cmd;
}

QString re_getCloseCmd(ReState *state, int val)
{
    QString cmd;

    qDebug() << "Close" << state->app.pname;

    if( state->app.pname=="xed" )
    {
        cmd = re_getCloseXed(val);
    }
    else if( state->app.pname=="qtcreator" ||
             state->app.pname=="code-oss" )
    {
        cmd = re_getCloseQt(val);
    }
    else if( state->app.pname=="gitkraken" )
    {
        cmd = re_getCloseGitKraken(val);
    }
    else if( state->app.pname=="GeckoMain" ||
             state->app.pname=="firefox" )
    {
        cmd = re_getCloseFirefox(val);
    }
    else if( state->app.pname=="nautilus" )
    {
        cmd = re_getCloseNautilus(val);
    }

    return cmd;
}

QString re_getOpenXed(int val)
{
    QString cmd;

    if( val==KEY_LEFT )
    {
        cmd = "xdotool key ctrl+alt+Page_Up";
    }
    else if( val==KEY_RIGHT )
    {
        cmd = "xdotool key ctrl+alt+Page_Down";
    }
    else if( val==KEY_F ) //focus
    {
        system("xdotool key --delay 200 super+ctrl+k");
        QThread::msleep(100); //little tweak
        cmd = "xdotool key --delay 200 super+ctrl+k";
    }

    return cmd;
}

QString re_getOpenQt(int val)
{
    system("rm ~/.config/polybar/awesomewm/ben_status");
    QString cmd;

    cmd  = "xdotool key F9;";
    cmd += "sleep 0.1;";
    cmd += "xdotool type ";
    cmd += QString::number(val);
    cmd += "; sleep 0.3;";
    cmd += "xdotool key Enter";
    return cmd;
}

QString re_getOpenGitKraken(int val)
{
    QString cmd;

    if( val==KEY_B )
    {
        system("xdotool type 'BaTool: '");
    }
    else if( val==KEY_M )
    {
        cmd = "xdotool key ctrl+M";
    }
    else if( val==KEY_N )
    {
        system("xdotool type 'NATO: '");
    }
    else if( val==KEY_R )
    {
        system("xdotool type 'Rebound-Linux: '");
    }
    else if( val==KEY_F ) //focus
    {
        system("xdotool key --delay 200 super+ctrl+k");
        QThread::msleep(100); //little tweak
        cmd = "xdotool key --delay 200 super+ctrl+k";
    }
    else if( val==KEY_P ) //push
    {
        system("xdotool key ctrl+Enter");
        QThread::msleep(100); //little tweak
        system("xdotool key ctrl+p");
        QThread::msleep(100); //little tweak
        system("xdotool type push");
        QThread::msleep(100); //little tweak
        cmd = "xdotool key Enter";
    }
    else if( val>0 && val<10 ) //tab
    {
        cmd = "xdotool key ctrl+";
        cmd += QString::number(val);
    }

    return cmd;
}

QString re_getOpenFirefox(int val)
{
    QString cmd;

    if( val==KEY_LEFT ) //focus
    {
        cmd = "xdotool key ctrl+shift+Tab";
    }
    else if( val==KEY_RIGHT )
    {
        cmd = "xdotool key ctrl+Tab";
    }
    else if( val==KEY_F ) //find
    {
        cmd = "xdotool key ctrl+F";
    }
    else if( val>0 && val<10 ) //tab
    {
        cmd = "xdotool key alt+";
        cmd += QString::number(val);
    }

    return cmd;
}

QString re_getOpenNautilus(int val)
{
    QString cmd;
    if( val==KEY_BACKSPACE )
    {
        cmd = "xdotool key alt+Up";
    }
    return cmd;
}

QString re_getCloseXed(int val)
{
    QString cmd;

    if( val==KEY_LEFT )
    {
        cmd = "xdotool key ctrl+alt+Page_Up";
    }
    else if( val==KEY_RIGHT )
    {
        cmd = "xdotool key ctrl+alt+Page_Down";
    }
    else if( val==KEY_F ) //focus
    {
        system("xdotool key --delay 200 super+ctrl+k");
        QThread::msleep(100); //little tweak
        cmd = "xdotool key --delay 200 super+ctrl+k";
    }

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

QString re_getCloseGitKraken(int val)
{
    QString cmd;

    if( val==KEY_B )
    {
        system("xdotool type 'BaTool: '");
    }
    else if( val==KEY_M )
    {
        cmd = "xdotool key ctrl+M";
    }
    else if( val==KEY_N )
    {
        system("xdotool type 'NATO: '");
    }
    else if( val==KEY_R )
    {
        system("xdotool type 'Rebound-Linux: '");
    }
    else if( val==KEY_F ) //focus
    {
        system("xdotool key --delay 200 super+ctrl+k");
        QThread::msleep(100); //little tweak
        cmd = "xdotool key --delay 200 super+ctrl+k";
    }
    else if( val==KEY_P ) //push
    {
        system("xdotool key ctrl+Enter");
        QThread::msleep(100); //little tweak
        system("xdotool key ctrl+p");
        QThread::msleep(100); //little tweak
        system("xdotool type push");
        QThread::msleep(100); //little tweak
        cmd = "xdotool key Enter";
    }
    else if( val>0 && val<10 ) //tab
    {
        cmd = "xdotool key ctrl+";
        cmd += QString::number(val);
    }

    return cmd;
}

QString re_getCloseFirefox(int val)
{
    QString cmd;

    if( val==KEY_LEFT ) //focus
    {
        cmd = "xdotool key ctrl+shift+Tab";
    }
    else if( val==KEY_RIGHT )
    {
        cmd = "xdotool key ctrl+Tab";
    }
    else if( val==KEY_F ) //find
    {
        cmd = "xdotool key ctrl+F";
    }
    else if( val>0 && val<10 ) //tab
    {
        cmd = "xdotool key alt+";
        cmd += QString::number(val);
    }

    return cmd;
}

QString re_getCloseNautilus(int val)
{
    QString cmd;
    if( val==KEY_BACKSPACE )
    {
        cmd = "xdotool key alt+Up";
    }
    return cmd;
}
