#include "re_super.h"
#include "re_chess.h"
#include <QThread>

void ReSuper::castFrontCmd(CCommand *cmd)
{
    re_mouseMoveC(0, 0);

    cmd->is_ctrl = 1;
    cmd->val1    = RE_MOUSE_UP;

    cmd->val2 = getScrollVal();
    cmd->val3 = 1;
    cmd->type  = RE_COMMAND_MOUSE;
    cmd->state = RE_CSTATE_0;
}

void ReSuper::castLastCmd(CCommand *cmd)
{
    re_mouseMoveC(0, 0);

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
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        cmd->is_ctrl = 1;
        cmd->val1    = KEY_W;

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
    else if( ReState::app.pname==RE_PROC_VSCODE )
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
    }
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        re_mouseMoveW_tr(400, 120);
        re_mouseKey(1);
        QThread::msleep(10);
        re_mouseMoveW_tr(400, 400);
        cmd->val1    = KEY_END;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
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
    }
    else if( ReState::app.pname==RE_PROC_VSCODE )
    {
        re_mouseMoveW_tr(400, 120);
        re_mouseKey(1);
        QThread::msleep(10);
        re_mouseMoveW_tr(400, 400);
        cmd->val1    = KEY_END;

        cmd->val2  = 1;
        cmd->val3  = 1;
        cmd->type  = RE_COMMAND_NATO;
        cmd->state = RE_CSTATE_0;
    }
    else if( ReState::app.pname==RE_PROC_FIREFOX )
    {

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

        re_mouseMoveW_br(30, 30);
        QThread::msleep(100);
        re_mousePress(1);
        QThread::msleep(1000);
        re_mouseMoveW_br(30, 400);
        QThread::msleep(1000);
        re_mouseRelease(1);
    }
}

int  ReSuper::getScrollVal()
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
    if( ReState::app.pname==RE_PROC_FIREFOX )
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
}
