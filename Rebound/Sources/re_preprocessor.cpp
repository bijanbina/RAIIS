#include "re_preprocessor.h"
#include <unistd.h>

RePreProcessor::RePreProcessor(ReCaptain *cpt, QObject *parent) : QObject(parent)
{
    captain = cpt;
    special_c = 0;
    chess = new ReChess(captain);
    re_rmSpex();
}

RePreProcessor::~RePreProcessor()
{
    ;
}

void RePreProcessor::execute()
{
    if( cmd_buf.length() )
    {
//        qDebug() << QTime::currentTime().toString("mm:ss:zzz")
//                 << "exec" << commands_str << special_c
//                 << cmd_buf.last().val2;

        if( "jordan arch"==commands_str )
        {
            qDebug() << "exec" << cmd_buf.length()
                     << cmd_buf.first().type;
        }
        commands_str.clear();

        captain->execute(cmd_buf);
        cmd_buf.clear();
    }
}

void RePreProcessor::nato(const QString &text)
{
    int val = text.toInt();
    if( captain->state->ch_count )
    {
        chess->nato(text);
        return;
    }
    else if( special_c ) //FUNC KEY
    {
        CCommand cmd;

        int f_num;
#ifdef WIN32
        f_num = text.toInt() - 'A' + 9;
#else

#endif
        qDebug() << "fnum" << f_num;
        cmd.val1 = RE_KEY_FMIN + f_num;
        cmd.val2 = 1;
        cmd.type = RE_COMMAND_DIRS;

        cmd_buf.append(cmd);

        special_c = 0;
        re_rmSpex();
        execute();

        return;
    }
    else if( captain->state->fl->sc_dir &&
             KEY_A<=val && val<=KEY_F )
    {
        CCommand cmd;
        cmd.val1 = captain->state->fl->sc_dir;
        cmd.val2 = val;
        cmd.val3 = 1;
        cmd.type = RE_COMMAND_META;

        cmd_buf.append(cmd);
        execute();

        return;
    }
    else if( re_isLastGo(cmd_buf) )
    {
        if( val==KEY_S )
        {
            captain->state->goToSleep();
            cmd_buf.clear();
            return;
        }
    }
    else if( re_isLastMeta(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index
        cmd_buf[last_i].val2 = text.toInt();
        execute();
        return;
    }
    else if( re_isLastMod(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index

        cmd_buf[last_i].val1=text.toInt();
        execute();
        return;
    }

    CCommand cmd;

    cmd.val1  = text.toInt();
    cmd.val2  = 1;
    cmd.type  = RE_COMMAND_NATO;
    cmd.state = RE_CSTATE_0;

    cmd_buf.append(cmd);
    execute();
}

void RePreProcessor::digit(const QString &text)
{
    if( captain->state->ch_count )
    {
        chess->digit(text);
        return;
    }
    else if( special_c ) //FUNC KEY
    {
        CCommand cmd;

        int f_num = re_keyCode2Digit(text) - 1;
        qDebug() << "fnum" << f_num;
        cmd.val1 = RE_KEY_FMIN + f_num;
        cmd.val2 = 1;
        cmd.type = RE_COMMAND_DIRS;

        cmd_buf.append(cmd);

        special_c = 0;
        re_rmSpex();
        execute();
    }
    else if( captain->state->fl->sc_dir )
    {
        CCommand cmd;
        cmd.val1 = captain->state->fl->sc_dir;
        cmd.val2 = text.toInt();
        cmd.val3 = 1;
        cmd.type = RE_COMMAND_META;

        cmd_buf.append(cmd);
        execute();
    }
    else if( re_isLastMeta(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index

        cmd_buf[last_i].val2 = text.toInt();
        execute();
    }
    else if( re_isLastMod(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index
        qDebug() << "re_isLastMod";

        cmd_buf[last_i].val1 = text.toInt();
        execute();
    }
    else if( re_isLastQt(cmd_buf) )
    {
        if( captain->state->isSleep() )
        {
            return;
        }
        re_qtDigitProc(&cmd_buf, text);

        int key_code = text.toInt();
        captain->key->sendKey(key_code);
    }
    else if( captain->isLastRepeatable() ) //max 2 digit
    {
        int input = re_keyCode2Digit(text);
        handleLastRepeatable(input);
    }
    else
    {
        CCommand cmd;
        cmd.val1 = text.toInt();
        cmd.val2 = 1;
        cmd.type = RE_COMMAND_DIGIT;

        cmd_buf.append(cmd);

        execute();
    }
}

void RePreProcessor::dirs(const QString &text) // direction keys
{
    if( captain->state->ch_count )
    {
        chess->dirs(text);
        return;
    }
    else if( re_isLastMeta(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index
        cmd_buf[last_i].val2 = text.toInt();
        execute();
        return;
    }
    else if( re_isLastMod(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index

        cmd_buf[last_i].val1=text.toInt();
        execute();
        return;
    }
    else if( captain->state->app.pname==RE_PROC_QT )
    {
        if( re_qtDirProc(&cmd_buf, text) )
        {
            return;
        }
    }
    CCommand cmd;
    cmd.val1  = text.toInt();
    cmd.val2  = 1; //press count
    cmd.type  = RE_COMMAND_DIRS;
    cmd.state = RE_CSTATE_0;

    cmd_buf.append(cmd);
    execute();
}

void RePreProcessor::modifier(const QString &text)
{
    //"super four" in <control super four> should be "super four"
    // if sleep
    if( re_isLastMod(cmd_buf) &&
        captain->state->isSleep()==false )
    {
        int last_i = cmd_buf.count()-1; //last index
        if( cmd_buf[last_i].val1==0 )
        {
            cmd_buf[last_i].mod_list.append(text.toInt());
            return;
        }
    }

//    qDebug() << "modifier re_isLastMod";
    CCommand cmd;
    cmd.val1  = 0;
    cmd.val2  = 1;
    cmd.type  = RE_COMMAND_MOD;
    cmd.state = RE_CSTATE_0;
    cmd.mod_list.append(text.toInt());

    cmd_buf.append(cmd);
    captain->state->last_cmd.type = RE_COMMAND_NULL;
}

void RePreProcessor::meta(const QString &text)
{
    if( re_isLastQt(cmd_buf) )
    {
        int last_i  = cmd_buf.count()-1; //last index
        int cmd_val = text.toInt();

        if( cmd_val==RE_META_OPEN ||
            cmd_val==RE_META_CLOSE )
        {
            cmd_buf[last_i].val1 = cmd_val;
            cmd_buf[last_i].val3 = 1;
            execute();
        }
        // ignore all others
        return;
    }
    else if( re_isLastMeta(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index
        cmd_buf[last_i].val2 = text.toInt();
        execute();
        return;
    }
    else if( captain->state->app.pname==RE_PROC_QT )
    {
        int val = text.toInt();

        if( captain->state->isSleep() ) // ignore sleep
        {
            return;
        }

        if( val==RE_META_FOX )
        {
            CCommand cmd = re_getGoQt(&cmd_buf);
            execute();

            cmd_buf.append(cmd);
            return;
        }
    }

    CCommand cmd;
    cmd.val1 = text.toInt();
    cmd.val2 = 0;
    cmd.val3 = 1;
    cmd.type = RE_COMMAND_META;

    if( cmd.val1==RE_META_OPEN ||
        cmd.val1==RE_META_CLOSE )
    {
        return; // we don't accept empty open/close
        system("rm ~/.config/polybar/awesomewm/ben_status");
    }

    cmd_buf.append(cmd);
    captain->state->last_cmd.type = RE_COMMAND_NULL;
}

void RePreProcessor::spex(const QString &text)
{
    if( !captain->state->isSleep() )
    {
        special_c = 1;
        qDebug() << "special_c" << special_c;

#ifdef WIN32
        QString cmd = "Special";

        cmd = "%{B#721b85}%{F#ffffff}  " + cmd;
        cmd += "  %{B- F1-}";
        re_writeStatus(cmd);
#else
        QString cmd = "echo ";
        cmd += QString::number(special_c);
        cmd += " > ~/.config/polybar/awesomewm/ben_spex";
        system(cmd.toStdString().c_str());
#endif
    }
}

void RePreProcessor::super(const QString &text)
{
    if( re_isLastMeta(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index
        cmd_buf[last_i].val2 = text.toInt();
        execute();
        return;
    }
    else if( captain->state->isSleep()==0 )
    {
        CCommand cmd; //fake command
        int val = text.toInt();
        if( chess->isChessCmd(val) )
        {
            commands_str = "";

            if( re_isLastMod(cmd_buf) )
            {
                int last_i = cmd_buf.count()-1; //last index
                cmd = cmd_buf[last_i];
            }
        }

        chess->super(text, cmd);
    }
    if( captain->state->ch_count )
    {
        // no need to process super mode while in
        // chess mode
        return;
    }
    if( re_isLastMod(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index

        cmd_buf[last_i].val1 = text.toInt();
        execute();
        return;
    }

    if( captain->state->isSleep() )
    {
        return;
    }

    CCommand cmd;
    cmd.val1 = text.toInt();
    cmd.val2 = 1;
    cmd.val3 = 1;
    cmd.type = RE_COMMAND_SUPER;
    captain->super->castCmd(text.toInt(), &cmd);
    if( cmd.val3==-1 )
    {
        captain->state->goToSleep();
        cmd.val3 = 3;
    }
    cmd_buf.append(cmd);

    execute();
}

void RePreProcessor::type(const QString &text)
{
    captain->state->last_cmd.type = RE_COMMAND_NATO;
}

void RePreProcessor::debug(const QString &text)
{
    if( captain->state->ch_count )
    {
        return;
    }
    if( commands_str.length() )
    {
        commands_str += " ";
    }
    commands_str += text;
//    qDebug() << "debug" << text;
}

void RePreProcessor::handleLastRepeatable(int input)
{
//    qDebug() << "captain->isLastRepeatable()";
    //////////FIXME: USE POINTER/////////////////
    if( captain->state->last_cmd.type==RE_COMMAND_META )
    {
        if( captain->state->last_cmd.state==RE_CSTATE_0 )
        {
            captain->state->last_cmd.state = RE_CSTATE_1;
            captain->state->last_cmd.val3 = input-1;
        }
        else if( captain->state->last_cmd.state==RE_CSTATE_1 )
        {
            captain->state->last_cmd.state = RE_CSTATE_2;
            int l_count = captain->state->last_cmd.val3+1; //last count
            captain->state->last_cmd.val3  = l_count*10;
            captain->state->last_cmd.val3 += input;
            captain->state->last_cmd.val3 -= l_count;
        }
        else
        {
            qDebug() << "digit unsupported handleLastRepeatable";
        }
    }
    else // not meta command
    {
        if( captain->state->last_cmd.state==RE_CSTATE_0 )
        {
            captain->state->last_cmd.state = RE_CSTATE_1;
            captain->state->last_cmd.val2  = input-1;
        }
        else if( captain->state->last_cmd.state==RE_CSTATE_1 )
        {
            captain->state->last_cmd.state = RE_CSTATE_2;
            int l_count = captain->state->last_cmd.val2+1; //last count
            captain->state->last_cmd.val2  = l_count*10;
            captain->state->last_cmd.val2 += input;
            captain->state->last_cmd.val2 -= l_count;
        }
        else
        {
            qDebug() << "digit unsupported handleLastRepeatable";
        }
    }
    cmd_buf.append(captain->state->last_cmd);
    execute();
}
