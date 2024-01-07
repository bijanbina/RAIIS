#include "re_window_w.h"
#include "backend.h"
#include "re_mouse.h"
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

    updateRemoteID(win);
    applyOpacity(win);
}

void ReWindowW::applyOpacity(ReWindow win)
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
    if( win_active.hWnd==win.hWnd )
    {
        re_setWindowOpacity(win.hWnd, 255);
    }
    else
    {
        re_setWindowOpacity(win.hWnd, 200);
    }

}

void ReWindowW::updateRemoteID(ReWindow win)
{
#ifndef RE_REMOTE
    if( win.pname=="rustdesk" && // to exclude main
        win.title.contains("Remote") )// rustdesk window
    {
        int r_id = re_cleanRemoteId(win.title);
        ReState::remote_id = r_id;
    }
#endif
}

void ReWindowW::handleNewWin(ReWindow win)
{
    windows.push_back(win);
//        qDebug() << "New Window" << win.title;
    if( win.pname=="NLClientApp" )
    {
        re_mouseMoveW(200, 300);
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

#ifndef RE_REMOTE
    if( win_active.pname=="rustdesk" &&
        win_active.title!="RustDesk" )
    {
        if( ReState::remote_state==0 &&
            ReState::sleep_state==0 )
        {
            int r_id = re_cleanRemoteId(win_active.title);
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
#endif
}
