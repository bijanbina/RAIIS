#include "re_preprocessor.h"
#include <unistd.h>

RePreProcessor::RePreProcessor(ReCaptain *cpt, QObject *parent) : QObject(parent)
{
    captain = cpt;
    special_c = 0;
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

//        if( commands_str=="jordan arch" )
//        {
//            qDebug() << "exec" << cmd_buf.length()
//                     << cmd_buf.first().type;
//        }
        commands_str.clear();

        captain->execute(cmd_buf);
        cmd_buf.clear();
    }
}

void RePreProcessor::nato(const QString &text)
{
    int val = text.toInt();
    if( ReState::ch_count )
    {
        ReChess::nato(text);
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
    else if( ReState::link->sc_dir &&
             KEY_A<=val && val<=KEY_F )
    {
        CCommand cmd;
        cmd.val1 = ReState::link->sc_dir;
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
            ReState::goToSleep();
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
    if( ReState::ch_count )
    {
        ReChess::digit(text);
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
    else if( ReState::link->sc_dir )
    {
        CCommand cmd;
        cmd.val1 = ReState::link->sc_dir;
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
        if( ReState::sleep_state )
        {
            return;
        }
        re_qtDigitProc(&cmd_buf, text);

        int key_code = text.toInt();
        ReKeyboard::sendKey(key_code);
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

// direction keys
void RePreProcessor::dirs(const QString &text)
{
    if( ReState::ch_count )
    {
        ReChess::dirs(text);
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
    else if( ReState::app.pname==RE_PROC_QT )
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
    if( ReState::ch_count )
    {
        ReChess::dirs(text);
        return;
    }
    else if( re_isLastMod(cmd_buf) &&
        ReState::sleep_state==false )
    {
        int last_i = cmd_buf.count()-1; //last index
        if( cmd_buf[last_i].val1==0 )
        {
            re_modApplyVal(&cmd_buf[last_i], text.toInt());
            return;
        }
    }

//    qDebug() << "modifier re_isLastMod";
    CCommand cmd = re_modCreate(text);
    cmd_buf.append(cmd);
    ReState::last_cmd.type = RE_COMMAND_NULL;
}

void RePreProcessor::meta(const QString &text)
{
    if( ReState::ch_count )
    {
        ReChess::meta(text);
        return;
    }
    else if( re_isLastQt(cmd_buf) )
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
    else if( ReState::app.pname==RE_PROC_QT )
    {
        int val = text.toInt();

        if( ReState::sleep_state ) // ignore sleep
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
    ReState::last_cmd.type = RE_COMMAND_NULL;
}

void RePreProcessor::spex(const QString &text)
{
    (void)text; // to suppress unused warning

    if( !ReState::sleep_state )
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
    if( ReState::sleep_state )
    {
        return;
    }

    if( ReState::ch_count )
    {
        ReChess::sendChessKey(text);
        return;
    }
    else if( re_isLastMeta(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index
        cmd_buf[last_i].val2 = text.toInt();
        execute();
        return;
    }
    ReChess::super(text, cmd_buf);

    if( ReState::ch_count )
    {
        // no need to process super mode while in
        // chess mode
        return;
    }

    if( re_isLastMod(cmd_buf) )
    {
        int last_i = cmd_buf.count()-1; //last index

        cmd_buf[last_i].type = RE_COMMAND_SUPER;
        cmd_buf[last_i].val1 = text.toInt();
        ReSuper::cast(text.toInt(), &cmd_buf[last_i]);
        execute();
        return;
    }

    CCommand cmd;
    cmd.val1 = text.toInt();
    cmd.val2 = 1;
    cmd.val3 = 1;
    cmd.type = RE_COMMAND_SUPER;

    cmd_buf.append(cmd);
    execute();
}

void RePreProcessor::type(const QString &text)
{
    (void)text; // to suppress unused warning

    ReState::last_cmd.type     = RE_COMMAND_NATO;
    ReState::last_cmd.is_alt   = 0;
    ReState::last_cmd.is_ctrl  = 0;
    ReState::last_cmd.is_shift = 0;
    ReState::last_cmd.is_super = 0;
}

void RePreProcessor::debug(const QString &text)
{
    if( ReState::ch_count )
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
    if( ReState::last_cmd.type==RE_COMMAND_META )
    {
        if( ReState::last_cmd.state==RE_CSTATE_0 )
        {
            ReState::last_cmd.state = RE_CSTATE_1;
            ReState::last_cmd.val3 = input-1;
        }
        else if( ReState::last_cmd.state==RE_CSTATE_1 )
        {
            ReState::last_cmd.state = RE_CSTATE_2;
            int l_count = ReState::last_cmd.val3+1; //last count
            ReState::last_cmd.val3  = l_count*10;
            ReState::last_cmd.val3 += input;
            ReState::last_cmd.val3 -= l_count;
        }
        else
        {
            qDebug() << "digit unsupported handleLastRepeatable";
        }
    }
    else // not meta command
    {
        if( ReState::last_cmd.state==RE_CSTATE_0 )
        {
            ReState::last_cmd.state = RE_CSTATE_1;
            ReState::last_cmd.val2  = input-1;
        }
        else if( ReState::last_cmd.state==RE_CSTATE_1 )
        {
            ReState::last_cmd.state = RE_CSTATE_2;
            int l_count = ReState::last_cmd.val2+1; //last count
            ReState::last_cmd.val2  = l_count*10;
            ReState::last_cmd.val2 += input;
            ReState::last_cmd.val2 -= l_count;
        }
        else
        {
            qDebug() << "digit unsupported handleLastRepeatable";
        }
    }
    cmd_buf.append(ReState::last_cmd);
    execute();
}
