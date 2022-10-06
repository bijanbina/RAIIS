#include "re_thread_w.h"
#include "backend.h"

#define re_state_mode thread_data->state->i_mode

int counter = 0;
int child_num = 3;
int win_thread_debug = 0;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char buffer[128];
    ReThreadW *thread_w = (ReThreadW *)lParam;
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
void re_AddHwnd(HWND hwnd, ReThreadW *thread_w)
{
    char buffer[128];
    RECT rc;

    if(IsWindowVisible(hwnd))
    {
        int cloaked;
        DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, 4);
//        if(cloaked==0)
        if(1)
        {
            HWND shell_window = GetShellWindow();
            GetWindowRect(hwnd, &rc);
            int width = rc.right - rc.left;

            if((hwnd!=shell_window) && (width>100) ) //&& (rc.bottom>0)
            {
                int success = GetWindowTextA(hwnd, buffer, 128); //get title

                if ( success==0 )
                {
                    qDebug() << hwnd << "Failed to GetWindowTextA";
                }


                ReWindow current_win;
                current_win.hWnd = hwnd;
                current_win.title = buffer;
                current_win.pname = reGetPName(reGetPid(hwnd));
                current_win.verify = 1; //always new windows are verified
//                current_win.title = thread_w->cleanTitle(current_win.title);

                re_InsertWindow(thread_w, current_win);
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

void re_getType(ReWindow *win)
{
    char buffer[128];
    GetClassNameA(win->hWnd, buffer, 128);
    QString class_name = buffer;

    if( class_name.contains("Clover_WidgetWin") )
    {
        HWND ret = NULL;
        EnumChildWindows(win->hWnd, EnumChildProc, (LPARAM) &ret);
        win->hWnd = ret;
        win->type = RE_WIN_EXPLORER;

        if ( win->title.contains(" - Clover"))
        {
            QString title = "Explor: ";
            title += win->title.split(" - Clover").at(0);
            win->title = title;
        }
    }
    else if( class_name.contains("Qt") && class_name.contains("QWindowIcon") )
    {
        win->type = RE_WIN_QT;

        if ( win->title.contains(" - Qt Creator"))
        {
            QString title = "Qt Cre: ";
            title += win->title.split(" (").at(0);
            win->title = title;
        }
    }
    else if( class_name.contains("Chrome_WidgetWin") )
    {
        if ( win->pname.contains("Spotify.exe") )
        {
            win->type = RE_WIN_SPOTIFY;

            QString title = "Spotiy: ";
            title += win->title;
            win->title = title;
        }
        else if ( win->pname.contains("atom.exe") )
        {
            win->type = RE_WIN_TEXTEDITOR;

            QString title = "Atom : ";
            title += win->title.split("\ufffd").at(0);
            win->title = title;
        }
        else
        {
            win->type = RE_WIN_UNKNOWN;
            if( win_thread_debug )
            {
                qDebug() << class_name << win->pname;
            }
        }
    }
    else if( class_name.contains("MozillaWindowClass") )
    {
        win->type = RE_WIN_FIREFOX;
        if ( win->title.contains(" - YouTube"))
        {
            win->type = RE_WIN_YOUTUBE;
        }

        QString title = "Firef : ";
        title += win->title.split("\ufffd").at(0);
        win->title = title;
    }
    else if( class_name.contains("ConsoleWindowClass") )
    {
        win->type = RE_WIN_TERMINAL;

        QString title = "CMD  : ";
        title += win->title.split("\ufffd").at(0);
//        win->title = title;

    }
    else
    {
        win->type = RE_WIN_UNKNOWN;
        if( win_thread_debug )
        {
            qDebug() << class_name << win->pname;
        }
    }
}

void re_InsertWindow(ReThreadW *thread_w, ReWindow win)
{
    //Get clover child
    re_getType(&win);

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

QString ReThreadW::cleanTitle(QString app_title)
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

QString ReThreadW::renameAppName(QString app_name)
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

void ReThreadW::sortApp()
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

HWND ReThreadW::getHWND(QString appname)
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

QString ReThreadW::getWinTitle(int index)
{
    if( index<windows.size() )
    {
        return windows[index].title;
    }
    return "";
}

QString ReThreadW::getElemName(int index)
{
    if(index < elems_spec.size())
    {
        return elems_spec[index]->name;
    }
    return "";
}

ReThreadW::ReThreadW(threadStruct *thread_data)
{
    this->thread_data = thread_data;
}

//clear verify flag
void ReThreadW::clearWins()
{
    for( int i=0 ; i<windows.size() ; i++ )
    {
        windows[i].verify = 0;
    }
}

//clean-up windows
void ReThreadW::cleanWins()
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

void ReThreadW::syncWinsTitle()
{
    for(int i=0; i<windows.size(); i++)
    {
        if( i<thread_data->wins_title->size() )
        {
            (*(thread_data->wins_title))[i] = windows[i].title;
            thread_data->windows[i] = windows[i];
        }
        else
        {
            thread_data->wins_title->push_back(windows[i].title);
            thread_data->windows.push_back(windows[i]);
        }
    }

    for(int i=windows.size(); i<thread_data->wins_title->size(); i++)
    {
        thread_data->wins_title->removeAt(i);
        i--;
    }
}

void ReThreadW::updateActiveWindow()
{
    char buffer[128];
    win_active.hWnd = GetForegroundWindow();
    GetWindowTextA(win_active.hWnd, buffer, 128);

    win_active.title = buffer;
    re_getType(&win_active);

    win_active.pname = reGetPName(reGetPid(win_active.hWnd));
    thread_data->state->updateApp(win_active);

//    char class_name[128];
//    GetClassNameA(HwndA, class_name, 128);
//    QString class_a = class_name;
//    if ( class_a=="CabinetWClass" )
//    {
//        HWND parent = GetAncestor(HwndA, GA_PARENT);
//        HwndA = parent;
//        char buffer_p[128];
//        char class_name_p[128];
//        GetWindowTextA(HwndA, buffer_p, 128);
//        GetClassNameA(HwndA, class_name_p, 128);
//        qDebug() << "Active Window" << titleA.length() << titleA << class_name << buffer_p << class_name_p << parent;
//    }

}

void reRunThread(void *thread_struct_void)
{
    qDebug() << "thread start";
    int cntr = 0;
    threadStruct *thread_data = (threadStruct *)thread_struct_void;
    ReThreadW *priv = new ReThreadW(thread_data);
    CoUninitialize();
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    while( 1 )
    {
        if( re_state_mode==RE_MODE_HIDDEN )
        {
            //Get Active Window Name
            priv->updateActiveWindow();

            priv->clearWins();
            EnumWindows(EnumWindowsProc, (LPARAM) priv);
            priv->cleanWins();
            priv->syncWinsTitle();
        }
        Sleep(200);
    }
}
