#include "re_window_w.h"
#include "backend.h"
#include "mm_api.h"

//Add a new Hwnd to wins_title vector
void re_AddHwnd(HWND hwnd, ReWindowW *thread_w)
{
    char buffer[128];
    RECT rc;

    if(IsWindowVisible(hwnd))
    {
        int cloaked;
        DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, 4);
        if(cloaked==0)
//        if(1)
        {
            HWND shell_window = GetShellWindow();
            GetWindowRect(hwnd, &rc);
            int width = rc.right - rc.left;
            int height = rc.bottom - rc.top;
            int opacity = re_getWindowOpacity(hwnd);

            if( (hwnd!=shell_window) && (width>MM_MINWIN_WIDTH) &&
                (height>MM_MINWIN_HEIGHT) && (opacity>MM_MINWIN_OPACITY)  ) //&& (rc.bottom>0)
            {
                int success = GetWindowTextA(hwnd, buffer, 128); //get title

                if ( success==0 )
                {
                    qDebug() << hwnd << "Failed to GetWindowTextA";
                }

                ReWindow current_win;
                current_win.hWnd = hwnd;
                current_win.title = buffer;
                current_win.pname = mm_getPName(mm_getPid(hwnd));
                current_win.verify = 1; //always new windows are verified

                re_InsertWindow(thread_w, current_win);

#ifndef RE_REMOTE
                if( current_win.pname=="rustdesk" && // to exclude main
                    current_win.title.contains("Remote") )// rustdesk window
                {
                    int r_id = re_cleanRemoteId(current_win.title);
                    ReState::remote_id = r_id;
                }
#endif

                if( current_win.pname=="Chess" ||
                    current_win.pname=="rustdesk" ||
                    current_win.title=="Qt Creator" ||
                    current_win.pname=="AnyDesk" ||
                    current_win.pname=="NLClientApp" )
                {
                    return;
                }
//                qDebug() << "process" << current_win.pname
//                         << current_win.title;
                if( thread_w->win_active.hWnd==hwnd )
                {
                    re_setWindowOpacity(hwnd, 255);
                }
                else
                {
                    re_setWindowOpacity(hwnd, 200);
                }
            }
            else
            {
//                int success = GetWindowTextA(hwnd, buffer, 128); //get title
//                qDebug() << "----------" << buffer << rc.bottom << width;
            }
        }
    }
    else
    {
//        int success = GetWindowTextA(hwnd, buffer, 128); //get title
//        qDebug() << "not vis" << buffer << IsWindowVisible(hwnd);
    }
}

ReWindowW::ReWindowW()
{
}

void ReWindowW::start()
{
    CoUninitialize();
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    while( 1 )
    {
        //Get Active Window Name
        updateActiveWindow();

        clearWins();
        EnumWindows(EnumWindowsProc, (LPARAM) this);
        cleanWins();
        Sleep(200);
    }
}

void re_InsertWindow(ReWindowW *thread_w, ReWindow win)
{
    //push active window to front
    if( win.hWnd==thread_w->win_active.hWnd )
    {
        if( thread_w->windows.size()>0 )
        {
            if( thread_w->windows[0].hWnd!=win.hWnd )
            {
                thread_w->windows.push_front(win);
                qDebug() << "Active Changed" << win.title;
            }
            else
            {
                thread_w->windows[0].verify = 1;
                thread_w->windows[0].title = win.title;
            }
        }
        else
        {
            thread_w->windows.push_front(win);
            qDebug() << "First Time" << win.title;
            return;
        }
    }

    for( int i=1 ; i<thread_w->windows.size() ; i++ )
    {
        if ( thread_w->windows[i].hWnd==thread_w->win_active.hWnd )
        {
            thread_w->windows.remove(i);
            i--;
        }
        else if ( thread_w->windows[i].hWnd==win.hWnd )
        {
            thread_w->windows[i].verify = 1;
            thread_w->windows[i].title = win.title;
//            qDebug() << "Ver Window" << i << win.title;
            return;
        }
    }

    if ( win.hWnd != thread_w->win_active.hWnd )
    {
        thread_w->windows.push_back(win);
//        qDebug() << "New Window" << win.title;
    }

}

int re_cleanRemoteId(QString title)
{
    QStringList split = title.split('-');
    QStringList id_split = split[0].split(" ");

    return id_split[0].toInt();
}

HWND ReWindowW::getHWND(QString appname)
{
    for(int i=0; i<windows.size(); i++)
    {
        if(appname == windows[i].pname)
        {
            return windows[i].hWnd;
        }
    }
    return NULL;
}

QString ReWindowW::getWinTitle(int index)
{
    if( index<windows.size() )
    {
        return windows[index].title;
    }
    return "";
}

//clear verify flag
void ReWindowW::clearWins()
{
    for( int i=0 ; i<windows.size() ; i++ )
    {
        windows[i].verify = 0;
    }
}

//clean-up windows
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
