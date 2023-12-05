#include "re_window_w.h"
#include "backend.h"
#include "mm_api.h"

#define re_state_mode thread_data->state->i_mode

int counter = 0;
int child_num = 3;
int win_thread_debug = 0;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char buffer[128];
    ReWindowW *thread_w = (ReWindowW *)lParam;
    int written = GetWindowTextA(hwnd, buffer, 128);
    if( written && strlen(buffer)!=0 )
    {
        re_AddHwnd(hwnd, thread_w);
    }
    return TRUE;
}

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
    char buffer[128];
    GetClassNameA(hwnd, buffer, 128);
    QString class_name = buffer;

    if ( class_name=="CabinetWClass" )
    {
        *(HWND*)lParam = hwnd;
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

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
//                current_win.title = thread_w->cleanTitle(current_win.title);

                re_InsertWindow(thread_w, current_win);

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
                    re_setWindowOpacity(hwnd, 255);
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

ReWindowW::ReWindowW(ReState *st)
{
    state = st;
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

QString ReWindowW::cleanTitle(QString app_title)
{
    QStringList title_split = app_title.split('-', QString::SkipEmptyParts);
    QString app_name = renameAppName(title_split.last().simplified());
    QStringList filename_split = title_split[0].split(" ", QString::SkipEmptyParts);
    app_title = app_name + ": " + title_split[0].simplified();
    if(filename_split.size()>1)
    {
        app_title += " " + filename_split[1].simplified();
    }
    return app_title;
}

QString ReWindowW::renameAppName(QString app_name)
{
    if(app_name.contains("qt", Qt::CaseInsensitive))
    {
        return "Qt";
    }
    else if(app_name.contains("foxit", Qt::CaseInsensitive))
    {
        return "Foxit";
    }
    else if(app_name.contains("firefox", Qt::CaseInsensitive))
    {
        return "firefox";
    }
    else if(app_name.contains("spotify", Qt::CaseInsensitive))
    {
        return "Spotify";
    }
    else if(app_name.contains("excel", Qt::CaseInsensitive))
    {//////
        return "Excel";
    }
    else if(app_name.contains("snip", Qt::CaseInsensitive))
    {
        return "Snip";
    }
    return app_name;
}

void ReWindowW::sortApp()
{
    QVector<ReWindow> sorted_apps, unsorted_apps;
    int clover_ind = 0, firefox_ind = 0, spotify_ind = 0;
    for( int i=0 ; i<windows.size() ; i++)
    {
        if(windows[i].pname.contains("Clover", Qt::CaseInsensitive))
        {
            sorted_apps.insert(clover_ind, windows[i]);
            clover_ind++; firefox_ind++; spotify_ind++;
        }
        else if(windows[i].pname.contains("firefox", Qt::CaseInsensitive))
        {
            sorted_apps.insert(firefox_ind, windows[i]);
            firefox_ind++; spotify_ind++;
        }
        else if(windows[i].pname.contains("Spotify", Qt::CaseInsensitive))
        {
            sorted_apps.insert(spotify_ind, windows[i]);
            spotify_ind++;
        }
        else
        {
            unsorted_apps.push_back(windows[i]);
        }
    }
    windows = sorted_apps + unsorted_apps;
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

QString ReWindowW::getElemName(int index)
{
    if(index < elems_spec.size())
    {
        return elems_spec[index]->name;
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
    state->updateApp(win_active);

    if( win_active.pname=="rustdesk" &&
        win_active.title!="RustDesk" )
    {
        if( state->remote_state==0 &&
            state->sleep_state==0 )
        {
            qDebug() << "win_active.title"
                     << win_active.title;
            state->goToRemote();
        }
    }
    else
    {
        if( state->remote_state==1 &&
            state->sleep_state==0 )
        {
            state->remote_state = 0;
            state->wakeUp();
        }
    }
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
