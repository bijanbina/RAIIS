#include "re_super.h"
#include "re_chess.h"
#include <QThread>

void ReSuper::castFrontCmd(CCommand *cmd)
{
    re_mouseMoveC(-50, 0);

    cmd->val1  = RE_MOUSE_UP;
    cmd->val2  = getScrollVal();
    cmd->val3  = 1;
    cmd->type  = RE_COMMAND_MOUSE;
    cmd->state = RE_CSTATE_0;
}

void ReSuper::castLastCmd(CCommand *cmd)
{
    re_mouseMoveC(-50, 0);

    cmd->is_ctrl = 1;
    cmd->val1    = RE_MOUSE_DOWN;

    cmd->val2 = getScrollVal();
    cmd->val3 = 1;
    cmd->type  = RE_COMMAND_MOUSE;
    cmd->state = RE_CSTATE_0;
}

void ReSuper::castRunCmd(CCommand *cmd)
{
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type = RE_COMMAND_NULL;

    qDebug() << "Run" << ReState::app.pname;
    if( ReState::app.pname==RE_PROC_QT )
    {
        cmd->val1 = KEY_F5;
        cmd->type = RE_COMMAND_DIRS;
    }
    if( ReState::app.pname==RE_PROC_INNOSETUP )
    {
        cmd->val1 = KEY_F9;
        cmd->type = RE_COMMAND_DIRS;
    }
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        cmd->is_ctrl = 1;
        cmd->val1    = KEY_H;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
}

void ReSuper::castDukeCmd(CCommand *cmd)
{
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type = RE_COMMAND_NULL;

    qDebug() << "Duke" << ReState::app.pname;

    if( ReState::app.pname==RE_PROC_QT )
    {
        cmd->is_ctrl = 1;
        cmd->val1    = KEY_W;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_VSCODE ||
             ReState::app.pname==RE_PROC_GIT )
    {
        cmd->is_ctrl = 1;
        cmd->val1    = KEY_W;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX )
    {
        ReKeyboard::pressKey(KEY_LEFTCTRL);
        ReKeyboard::sendKey(KEY_L);
        ReKeyboard::releaseKey(KEY_LEFTCTRL);
        QThread::msleep(200);

        ReKeyboard::pressKey(KEY_LEFTCTRL);
        ReKeyboard::sendKey(KEY_A);
        ReKeyboard::releaseKey(KEY_LEFTCTRL);
        QThread::msleep(200);

        ReKeyboard::pressKey(KEY_LEFTCTRL);
        ReKeyboard::sendKey(KEY_C);
        ReKeyboard::releaseKey(KEY_LEFTCTRL);
        QThread::msleep(200);

        ReKeyboard::pressKey(KEY_LEFTCTRL);
        ReKeyboard::sendKey(KEY_T);
        ReKeyboard::releaseKey(KEY_LEFTCTRL);
        QThread::msleep(200);

        ReKeyboard::pressKey(KEY_LEFTCTRL);
        ReKeyboard::sendKey(KEY_V);
        ReKeyboard::releaseKey(KEY_LEFTCTRL);
        QThread::msleep(200);

        cmd->val1    = KEY_ENTER;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
}

void ReSuper::castMediaCmd(CCommand *cmd)
{
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type = RE_COMMAND_NULL;

    qDebug() << "Media" << ReState::app.pname;

    QString url = "https://gemini.google.com/u/3/";

    ReKeyboard::pressKey(KEY_LEFTCTRL);
    ReKeyboard::sendKey(KEY_T);
    ReKeyboard::releaseKey(KEY_LEFTCTRL);
    QThread::msleep(1000);

    ReKeyboard::type(url);
    QThread::msleep(200);
    ReKeyboard::sendKey(KEY_ENTER);

    QThread::msleep(2000);

    ReKeyboard::pressKey(KEY_LEFTCTRL);
    ReKeyboard::pressKey(KEY_LEFTSHIFT);
    ReKeyboard::sendKey(KEY_R);
    ReKeyboard::releaseKey(KEY_LEFTSHIFT);
    ReKeyboard::releaseKey(KEY_LEFTCTRL);
    QThread::msleep(200);

    ReState::goToDictate();
    cmd->is_ctrl  = 1;
    cmd->is_shift = 1;
    cmd->val1     = KEY_R;

    cmd->val2  = 1;
    cmd->val3  = 1;
    cmd->type  = RE_COMMAND_NATO;
    cmd->state = RE_CSTATE_0;
}

void ReSuper::castGasCmd(CCommand *cmd)
{
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type = RE_COMMAND_NULL;

//    qDebug() << "Duke" << ReState::app.pname;

    if( ReState::app.pname==RE_PROC_QT )
    {
        ReChess::sendCmd("select");
        ReChess::setCount(2);
        ReChess::magic_mode = 1;
    }
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        ReChess::sendCmd("select");
        ReChess::setCount(2);
        ReChess::magic_mode = 1;
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX )
    {

    }
}

void ReSuper::castLaunchCmd(CCommand *cmd)
{
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type = RE_COMMAND_NULL;

//    qDebug() << "Duke" << ReState::app.pname;

    if( ReState::app.pname==RE_PROC_QT )
    {
        ReChess::sendCmd("open");
        ReChess::setCount(1);
        ReChess::magic_mode = 1;
    }
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        ReChess::sendCmd("open");
        ReChess::setCount(1);
        ReChess::magic_mode = 1;
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX )
    {
        cmd->is_ctrl  = 1;
        cmd->is_shift = 1;
        cmd->val1     = KEY_T;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
}

void ReSuper::castCarrotCmd(CCommand *cmd)
{
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type = RE_COMMAND_NULL;

    qDebug() << "Carrot" << ReState::app.pname;
    if( ReState::app.pname==RE_PROC_QT )
    {
        cmd->val1 = KEY_F4;
        cmd->type = RE_COMMAND_DIRS;
    }
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        cmd->val1 = KEY_F6;
        cmd->type = RE_COMMAND_DIRS;
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX )
    {
        re_mouseMoveW_tr(400, 100);
        re_mouseKey(1);
        QThread::msleep(10);
        ReKeyboard::pressKey(KEY_LEFTCTRL);
        QThread::msleep(10);
        ReKeyboard::sendKey(KEY_L);
        QThread::msleep(10);
        ReKeyboard::releaseKey(KEY_LEFTCTRL);
        QThread::msleep(10);
        ReKeyboard::pressKey(KEY_LEFTCTRL);
        QThread::msleep(10);
        ReKeyboard::sendKey(KEY_C);
        QThread::msleep(10);
        ReKeyboard::releaseKey(KEY_LEFTCTRL);

        cmd->val1     = KEY_ESC;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
}

void ReSuper::castJamesCmd(CCommand *cmd)
{
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type = RE_COMMAND_NULL;

//    qDebug() << "James" << ReState::app.pname;
    if( ReState::app.pname==RE_PROC_QT )
    {
        cmd->val1 = KEY_F8;
        cmd->type = RE_COMMAND_DIRS;
    }
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        cmd->is_ctrl = 1;
        cmd->val1    = KEY_O;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_SPOTIFY )
    {
        cmd->is_ctrl = 1;
        cmd->val1    = KEY_R;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX )
    {
        castJamesFF(cmd);
    }
}

void ReSuper::castJamesFF(CCommand *cmd)
{
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type = RE_COMMAND_NULL;

//    qDebug() << "James" << ReState::app.pname;
    if( ReState::app.title.contains("Confluence") )
    {
        if( ReState::app.title.contains("Edit") )
        {
            ReKeyboard::pressKey(KEY_LEFTCTRL);
            QThread::msleep(10);
            ReKeyboard::sendKey(KEY_ENTER);
            QThread::msleep(10);
            ReKeyboard::releaseKey(KEY_LEFTCTRL);
            QThread::msleep(100);

            cmd->val1     = KEY_ENTER;
            cmd->is_ctrl  = 1;

            cmd->val2  = 1;
            cmd->val3  = 1;
            cmd->type  = RE_COMMAND_NATO;
            cmd->state = RE_CSTATE_0;
        }
    }
    else if( ReState::app.title.contains("Gemini") )
    {
        ReState::goToRecord();
        cmd->is_ctrl  = 1;
        cmd->is_shift = 1;
        cmd->val1     = KEY_R;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
}

void ReSuper::castNextCmd(CCommand *cmd)
{
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type = RE_COMMAND_NULL;

    qDebug() << "Next" << ReState::app.pname;
    if( ReState::app.pname==RE_PROC_QT )
    {
        cmd->is_alt   = 1;
        cmd->is_shift = 1;
        cmd->val1 = KEY_RIGHT;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        cmd->is_alt   = 1;
        cmd->is_shift = 1;
        cmd->val1 = KEY_RIGHT;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX )
    {
        cmd->is_ctrl = 1;
        cmd->val1    = KEY_TAB;
        cmd->val2    = 1;
        cmd->val3    = 1;
        cmd->type    = RE_COMMAND_DIRS;
        cmd->state   = RE_CSTATE_0;
    }
}

void ReSuper::castWestCmd(CCommand *cmd)
{
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type = RE_COMMAND_NULL;

    qDebug() << "West" << ReState::app.pname;
    if( ReState::app.pname==RE_PROC_QT )
    {
        cmd->is_alt   = 1;
        cmd->is_shift = 1;
        cmd->val1 = KEY_RIGHT;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        cmd->is_alt   = 1;
        cmd->is_shift = 1;
        cmd->val1 = KEY_RIGHT;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_DIRS;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX )
    {
        cmd->is_ctrl  = 1;
        cmd->is_shift = 1;
        cmd->val1     = KEY_TAB;
        cmd->val2     = 1;
        cmd->val3     = 1;
        cmd->type     = RE_COMMAND_DIRS;
        cmd->state    = RE_CSTATE_0;
    }
}

void ReSuper::castNorthCmd(CCommand *cmd)
{
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type = RE_COMMAND_NULL;

    qDebug() << "North" << ReState::app.pname;
    if( ReState::app.pname==RE_PROC_QT )
    {
        re_mouseMoveC(200, 0);

        cmd->val1  = RE_MOUSE_UP;
        cmd->val2  = getScrollVal();
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_MOUSE;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        re_mouseMoveC(200, 0);

        cmd->val1  = RE_MOUSE_UP;
        cmd->val2  = getScrollVal();
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_MOUSE;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX )
    {
        re_mouseMoveW(100, 600);

        cmd->val1  = RE_MOUSE_UP;
        cmd->val2  = getScrollVal(1);
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_MOUSE;
        cmd->state = RE_CSTATE_0;
    }
}

void ReSuper::castSouthCmd(CCommand *cmd)
{
    cmd->val2 = 1;
    cmd->val3 = 1;
    cmd->type = RE_COMMAND_NULL;

    qDebug() << "South" << ReState::app.pname;
    if( ReState::app.pname==RE_PROC_QT )
    {
        re_mouseMoveC(200, 0);

        cmd->is_ctrl = 1;
        cmd->val1    = RE_MOUSE_DOWN;

        cmd->val2 = getScrollVal();
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOUSE;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        re_mouseMoveC(200, 0);

        cmd->is_ctrl = 1;
        cmd->val1    = RE_MOUSE_DOWN;

        cmd->val2 = getScrollVal();
        cmd->val3 = 1;
        cmd->type  = RE_COMMAND_MOUSE;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX )
    {
        re_mouseMoveW(100, 500);

        cmd->val1  = RE_MOUSE_DOWN;
        cmd->val2  = getScrollVal(1);
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_MOUSE;
        cmd->state = RE_CSTATE_0;
    }
}

// secondary is 1 for north and south
int  ReSuper::getScrollVal(int secondary)
{
    if( ReState::app.pname==RE_PROC_EDITOR )
    {
        return 10;
    }
    else if( ReState::app.pname==RE_PROC_QT ||
             ReState::app.pname==RE_PROC_VSCODE )
    {
        return 10;
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX &&
             secondary==1 )
    {
        return 3;
    }
#ifdef WIN32
    else if( ReState::app.pname==RE_PROC_SLACK )
    {
        return 5;
    }
#endif
    else
    {
        return 5;
    }
}

void ReSuper::castDiveSky(int cmd, int arg)
{
    if( isWinExplorer(ReState::app.title) )
    {
        re_mouseMoveW(100, 400);
        int count = 4;
        if( arg==-1 ) // default
        {
            count = 20;
        }

        if( cmd==RE_SUPER_DIVE )
        {
            for( int j=0 ; j<count ; j++ )
            {
                re_mouseKey(5);
                QThread::msleep(50);
            }
        }
        else if( cmd==RE_SUPER_SKY )
        {
            for( int j=0 ; j<count ; j++ )
            {
                re_mouseKey(4);
                QThread::msleep(50);
            }
        }
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX )
    {
        if( arg==-1 ) // default
        {
            ReState::enScroll(cmd, 2);
        }
        else if( (KEY_1<=arg && arg<=KEY_9) )
        {
            ReState::enScroll(cmd, arg-KEY_1+1);
        }
        else if( KEY_A<=arg && arg<=KEY_F )
        {
            ReState::enScroll(cmd, arg-KEY_A+10);
        }
    }
#ifdef WIN32
    else if( ReState::app.pname==RE_PROC_SLACK )
    {
        re_mouseMoveW(300, 400);
        int count = 5*(arg-KEY_1+1);
        if( arg==-1 ) // default
        {
            count = 5;
        }

        if( cmd==RE_SUPER_DIVE )
        {
            for( int j=0 ; j<count ; j++ )
            {
                re_mouseKey(5);
                QThread::msleep(50);
            }
        }
        else if( cmd==RE_SUPER_SKY )
        {
            for( int j=0 ; j<count ; j++ )
            {
                re_mouseKey(4);
                QThread::msleep(50);
            }
        }
    }
    else if( ReState::app.pname==RE_PROC_EXPLORER )
    {
        re_mouseMoveW(100, 400);
        int count = 10*(arg-KEY_1+1);
        if( arg==-1 ) // default
        {
            count = 20;
        }

        if( cmd==RE_SUPER_DIVE )
        {
            for( int j=0 ; j<count ; j++ )
            {
                re_mouseKey(5);
                QThread::msleep(50);
            }
        }
        else if( cmd==RE_SUPER_SKY )
        {
            for( int j=0 ; j<count ; j++ )
            {
                re_mouseKey(4);
                QThread::msleep(50);
            }
        }
    }
#endif
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        if( cmd==RE_SUPER_DIVE )
        {
            ReKeyboard::sendKey(KEY_F5);
        }
        else if( cmd==RE_SUPER_SKY )
        {
        }
    }
}
