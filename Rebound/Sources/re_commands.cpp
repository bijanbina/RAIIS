#include "re_commands.h"

bool re_isLastCmdFunction(QVector<CCommand> commands)
{
    if( commands.count()==0 )
    {
        return false;
    }
    int last_i = commands.count()-1; //last index
    int key_code = commands[last_i].val1;
    int cmd_type = commands[last_i].type;

    if( cmd_type==RE_COMMAND_NATO )
    {
        if( key_code>=RE_KEY_FMIN &&
            key_code <RE_KEY_FMAX )
        {
            return true;
        }
    }

    return false;
}

bool re_isLastMeta(QVector<CCommand> commands)
{
    if( commands.count()==0 )
    {
        return false;
    }

    int last_i = commands.count()-1; //last index
    int cmd_type = commands[last_i].type;
    int cmd_val2 = commands[last_i].val2;

    if( cmd_type==RE_COMMAND_META )
    {
        if( cmd_val2==0 )
        {
            return true;
        }
    }

    return false;
}

bool re_isLastMod(QVector<CCommand> commands)
{
    if( commands.count()==0 )
    {
        return false;
    }

    int last_i = commands.count()-1; //last index
    int cmd_type = commands[last_i].type;

    if( cmd_type==RE_COMMAND_MOD )
    {
        return true;
    }

    return false;
}

bool re_isLastQt(QVector<CCommand> commands)
{
    if( commands.count()==0 )
    {
        return false;
    }

    int last_i = commands.count()-1; //last index
    int cmd_type = commands[last_i].type;

    if( cmd_type==RE_COMMAND_QDIGIT )
    {
        return true;
    }

    return false;
}

int re_keyCode2Digit(QString key_code)
{
    int code = key_code.toInt();

    return re_keyCode2Digit(code);
}

#ifdef WIN32
int re_keyCode2Digit(int code)
{
    return code-'0';
}
#else
int re_keyCode2Digit(int code)
{
    if( code==11 )
    {
        return 0;
    }
    else
    {
        return code-1;
    }
}
#endif
