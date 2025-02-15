#include "re_window_w.h"
#include "backend.h"
#include "re_mouse.h"
#include "re_chess.h"
#include "mm_api.h"

ReWindowW::ReWindowW()
{
}

void ReWindowW::start()
{
    CoUninitialize();
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    while( 1 )
    {
        updateActiveWindow();

        clearWins();
        EnumWindows(EnumWindowsProc, (LPARAM) this);
        cleanWins();
        Sleep(200);
    }
}

//Add a new Hwnd
void ReWindowW::addHwnd(HWND hwnd)
{
    ReWindow win = re_readWindow(hwnd);

    // add to list
    int existed = 0;
    for( int i=0 ; i<windows.size() ; i++ )
    {
        if ( windows[i].hWnd==win.hWnd )
        {
            windows[i].verify = 1;
            windows[i].title = win.title;
//            qDebug() << "Ver Window" << i << win.title;
            existed = 1;
            break;
        }
    }

    if ( existed==0 )
    {
        handleNewWin(win);
    }

    applyOpacity(win);
    checkSize(win);
}

void ReWindowW::applyOpacity(ReWindow win)
{
    if( win.pname=="Chess" ||
        win.pname=="rustdesk" ||
        win.title=="Qt Creator" ||
        win.pname=="AnyDesk" ||
        win.pname=="VirtualBoxVM" ||
        win.pname=="NLClientApp" ||
        win.pname.contains("gimp") )
    {
        return;
    }
//    qDebug() << "process" << win.pname
//             << win.title;
    if( win_active.hWnd==win.hWnd )
    {
        re_setWindowOpacity(win.hWnd, 255);
    }
    else
    {
        re_setWindowOpacity(win.hWnd, 230);
//        re_setWindowOpacity(win.hWnd, 255);
    }
}

void ReWindowW::checkSize(ReWindow win)
{
    if( win.pname=="Chess" ||
        win.pname=="rustdesk" ||
        win.title=="Qt Creator" ||
        win.pname=="AnyDesk" ||
        win.pname=="NLClientApp" )
    {
        return;
    }
//                qDebug() << "process" << current_win.pname
//                         << current_win.title;
//    if( win_active.hWnd==win.hWnd )
//    {
//        re_setWindowOpacity(win.hWnd, 255);
//    }
}

void ReWindowW::updateRemoteID(ReWindow win)
{
    if( win.pname=="rustdesk" && // to exclude main
        win.title.contains("Remote") )// rustdesk window
    {
        int r_id = re_getRemoteId(win.title);
        ReState::remote_id = r_id;
    }
}

void ReWindowW::handleNewWin(ReWindow win)
{
    windows.push_back(win);
//        qDebug() << "New Window" << win.title;
    if( win.pname=="NLClientApp" )
    {
        mm_focus(win.hWnd);
        QThread::msleep(400);
        re_mouseMoveW(250, 330);
        QThread::msleep(100);
        re_mouseKey(1);

        if( ReState::sleep_state==0 )
        {
            ReChess::showChess(RE_SUPER_KICK);
            QThread::msleep(200);
            ReChess::nato(QString::number(KEY_END));
            ReChess::dirs(QString::number(KEY_RIGHT));
        }
    }
}

//clear verify flag
void ReWindowW::clearWins()
{
    for( int i=0 ; i<windows.size() ; i++ )
    {
        windows[i].verify = 0;
    }
}

//clean-up non existed windows
void ReWindowW::cleanWins()
{
    for( int i=0 ; i<windows.size() ; i++ )
    {
        if( windows[i].verify==0 )
        {
//            qDebug() << "Remove Window" << windows[i].title;
            windows.remove(i);
            i--;
        }
    }
}

void ReWindowW::updateActiveWindow()
{
    char buffer[128];
    win_active.hWnd = GetForegroundWindow();
    GetWindowTextA(win_active.hWnd, buffer, 128);

    win_active.title = buffer;
    win_active.pid = mm_getPid(win_active.hWnd);
    win_active.pname = mm_getPName(win_active.pid);
    ReState::updateApp(win_active);

    if( win_active.pname=="rustdesk" &&
        win_active.title!="RustDesk" )
    {
        if( ReState::remote_state==0 &&
            ReState::sleep_state==0 )
        {
            int r_id = re_getRemoteId(win_active.title);
            qDebug() << "goToRemote"
                     << win_active.title << r_id;
            ReState::goToRemote(r_id);
        }
    }
    else
    {
        if( ReState::remote_state==1 &&
            ReState::sleep_state==0 )
        {
            ReState::remote_state = 0;
            ReState::wakeUp();
        }
    }
}
