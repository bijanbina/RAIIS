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
    if(written && strlen(buffer) != 0 && strcmp(buffer, "Rebound") != 0)
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

int re_isVpnConnected()
{
    QString output = getStrCommand("netsh interface ipv4 show config | find \"MK2\"");

    if ( output.length() )
    {
        return 1;
    }
    else
    {
        return 0;
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
            thread_w->thread_data->state->updateApp(win);
        }
        else
        {
            thread_w->windows.push_front(win);
            thread_w->thread_data->state->updateApp(win);
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
        qDebug() << "New Window" << win.title;
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

void reListChildren(IAccessible *pAcc, QString path)
{
    QString pAcc_name = reGetAccName(pAcc, CHILDID_SELF);
    qDebug() << "####### getChildren - acc path : " + pAcc_name;

    long childCount;
    long returnCount;
    HRESULT hr = pAcc->get_accChildCount(&childCount);
    VARIANT* pArray = new VARIANT[childCount];
    hr = AccessibleChildren(pAcc, 0L, childCount, pArray, &returnCount);
    path += QString("/");

    for (int x = 0; x < returnCount; x++)
    {
        VARIANT vtChild = pArray[x];
        if (vtChild.vt == VT_DISPATCH)
        {
            IDispatch* pDisp = vtChild.pdispVal;
            IAccessible* pChild = NULL;
            hr = pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);
            if (hr == S_OK)
            {
                QString child_name = reGetAccName(pChild, CHILDID_SELF);
                long child_count = reGetChildCount(pChild);
                qDebug() << "-> acc path : " + pAcc_name +
                            " - child[" + QString::number(x) + "/" + QString::number(returnCount-1) + "], childname:" + child_name +
                            "child count" + QString::number(child_count) + " path:" + path + QString::number(x);
                if(child_count>0)
                {
                    reListChildren(pChild, path + QString::number(x));
                }
                pChild->Release();
            }
            pDisp->Release();
        }
        // Else it's a child element so we have to call accNavigate on the parent,
        //   and we do not recurse because child elements can't have children.
        else
        {
            qDebug() <<"-> acc path : " + pAcc_name +
                        " - child[" + QString::number(x) + "/" + QString::number(returnCount-1) +
                        "] ELEMENT - " + reGetAccName(pAcc, vtChild.lVal)
                        + " path:" + path + QString::number(x);
        }
    }
    delete[] pArray;
    qDebug() <<"####### Exit getChildren - acc path : " + pAcc_name;
}

QString reGetPName(long pid)
{
    HANDLE processHandle = NULL;
//    processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    processHandle = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if(processHandle == NULL)
    {
        qDebug() << "Warning: couldn't get process handle from pid" << pid;
        return "";
    }

    // get name of process handle
    char path_buff[MAX_PATH];
    if(GetProcessImageFileNameA(processHandle, path_buff, MAX_PATH) == 0)
    {
        qDebug() << "Error" << GetLastError() << " : Fail to get Pname of " << pid;
        return "";
    }

    QString path_q = path_buff; //process filename
    QStringList path_list = path_q.split("\\", QString::SkipEmptyParts);
    QString filename = path_list.last();
    filename.remove(".exe");

    return filename;
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

long reGetPid(HWND hWnd)
{
    // get allegro pid of window handle
    DWORD dwProcessId;
    GetWindowThreadProcessId(hWnd, &dwProcessId);
    if(long(dwProcessId) < 0)
    {
        qDebug() <<"Warning: couldn't get pid of allegro from window handle";
        return -1;
    }
    return dwProcessId;
}

long reGetChildCount(IAccessible *pAcc)
{
    long cc;
    pAcc->get_accChildCount(&cc);
    return cc;
}

IAccessible* reGetPAcc(HWND hWnd)
{
    IAccessible *pAcc;

    AccessibleObjectFromWindow(hWnd, OBJID_WINDOW,
                               IID_IAccessible, (void**) &pAcc);
    if(pAcc == NULL)
    {
        qDebug() <<"Error: window is not open now, open it and try again ... !";
        return pAcc;
    }
    return pAcc;
}

int ReThreadW::getIndex(QString app_name)
{
    for( int i=0 ; i<windows.size() ; i++ )
    {
        if(windows[i].pname.contains(app_name, Qt::CaseInsensitive))
        {
            return i;
        }
    }
    return -1;
}

QString reGetAccName(IAccessible *pAcc, long childId)
{
    BSTR bstrName;
    VARIANT varChild;
    varChild.vt = VT_I4;
    varChild.lVal = childId;
    /*HRESULT hr = */pAcc->get_accName(varChild, &bstrName);
    return QString::fromWCharArray(bstrName);
}

ReElemSpec* ReThreadW::getElemSpec(QString name)
{
    for(auto e: elems_spec)
    {
        if(e->name == name)
        {
            return e;
        }
    }
    return NULL;
}

ReWindow ReThreadW::getWinSpec(QString title)
{
    for(int i=0; i<windows.size(); i++)
    {
        if(title == windows[i].title)
        {
            return windows[i];
        }
    }

    ReWindow shit;
    return shit;
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

// return Acc specific chilren
IAccessible* reFindAcc(QString path, IAccessible *pAcc)
{
    VARIANT vtChild;
    if( path.size()>0 )
    {
        long childCount = reGetChildCount(pAcc);
        long returnCount;
        VARIANT* pArray = new VARIANT[childCount];

        AccessibleChildren(pAcc, 0L, childCount, pArray, &returnCount);

        int indx = QString(path.at(0)).toInt();
        vtChild = pArray[indx];

        qDebug() << QString("--path:") + path + " childCount:" + QString::number(childCount) + " " +
                 reGetAccName(pAcc, CHILDID_SELF) + " indx:" + QString::number(indx) + " " + QString::number(returnCount);

        // return if path is not correct
        if(indx > childCount)
        {
            qDebug() <<"path is not correct, index greater than child";
            return NULL;
        }

        if(vtChild.vt != VT_DISPATCH)
        {
            qDebug() <<"path is not correct, child is element, not Acc";
            return NULL;
        }

        IDispatch* pDisp = vtChild.pdispVal;
        IAccessible* pChild = NULL;
        pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);

        return reFindAcc(path.mid(1), pChild);
    }
    else
    {
        return pAcc;
    }
}

void ReThreadW::updateElements(QString app_name, QString parent_path,
                               QString child_path)
{
    qDebug() << "updateElements" << app_name;

    VARIANT vtChild;
    int index = getIndex(app_name);
    if( index<0 )
    {
        //Requested app_name not found
//        qDebug() << "Error: can not found" << app_name;
        return;
    }
    HWND app_hwnd = getHWND(app_name);
    if( app_hwnd==NULL )
    {
        qDebug() << "Error: getHWND return null, pName:" << app_name;
        return;
    }

    IAccessible *app_pacc = reGetPAcc(app_hwnd);
    if( app_pacc==NULL )
    {
        return;
    }

    IAccessible *parent_pacc = NULL;
    parent_pacc = reFindAcc(parent_path, app_pacc);
    if( parent_pacc==NULL )
    {
        return;
    }

    long returnCount, childCount = reGetChildCount(parent_pacc);
    VARIANT* pArray = new VARIANT[childCount];
    AccessibleChildren(parent_pacc, 0L, childCount, pArray, &returnCount);
    if(returnCount != childCount)
    {
        qDebug() << "Error: not found enough children when gathering them!";
        return;
    }
    for(int i=0; i<childCount; i++)
    {
        vtChild = pArray[i];
        if(vtChild.vt != VT_DISPATCH)
        {
            qDebug() <<"path is not correct, child is element, not Acc";
            continue;
        }
        IDispatch *pDisp = vtChild.pdispVal;
        IAccessible *pChild = NULL;
        pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);
        pChild = reFindAcc(child_path, pChild);
        if( pChild==NULL )
        {
            continue;
        }
        ReElemSpec *elem_spec = new ReElemSpec;
        elem_spec->pAcc = pChild;
        elem_spec->name = reGetAccName(pChild, CHILDID_SELF);
        elems_spec.push_back(elem_spec);
        elems_name.push_back(elem_spec->name);
    }
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
            qDebug() << "Remove Window" << windows[i].title;
            windows.remove(i);
            i--;
        }
    }
}

void ReThreadW::cleanElems()
{
    for(auto e : elems_spec)
    {
        delete e;
    }
    elems_spec.clear();
    elems_name.clear();
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

void ReThreadW::syncElemsName()
{
    for(int i=0; i<elems_name.size(); i++)
    {
        if(i < thread_data->elems_name->size())
        {
            (*(thread_data->elems_name))[i] = elems_name[i];
        }
        else
        {
            thread_data->elems_name->push_back(elems_name[i]);
        }
    }

    while( elems_name.size()<thread_data->elems_name->size() )
    {
        thread_data->elems_name->pop_front();
    }
}

void ReThreadW::updateActiveWindow()
{
    char buffer[128];
    win_active.hWnd = GetForegroundWindow();
    GetWindowTextA(win_active.hWnd, buffer, 128);

    win_active.title = buffer;

    if ( win_active.title.length()==0 ) //No active window
    {
        if ( windows.size()>0 )
        {
            win_active.hWnd = windows[0].hWnd; //Set last active window
        }
    }

    re_getType(&win_active);

    if( win_active.type==RE_WIN_YOUTUBE )
    {
        thread_data->state->utube_mode = 1;
    }
    else
    {
        thread_data->state->utube_mode = 0;
    }
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

    while(1)
    {
        if(cntr > 200)
        {
            if(re_state_mode == RE_MODE_HIDDEN)
            {
                //Get Active Window Name
                priv->updateActiveWindow();

                priv->clearWins();
                EnumWindows(EnumWindowsProc, (LPARAM) priv);
                priv->cleanWins();
                priv->syncWinsTitle();
            }
            else if(re_state_mode == RE_MODE_MAIN)
            {
                priv->cleanElems();
                priv->updateElements("spotifys", RE_SPOTIFY_ALBUM_PARENT,
                                     RE_SPOTIFY_ALBUM_CHILD);
//                priv->syncElemsName();
            }
            cntr = 0;
        }
        if(!thread_data->message.isEmpty())
        {
            if(thread_data->message == "Launch Nuclear missiles")
            {
                qDebug() << "Launched";
            }
            thread_data->message.clear();
        }
        cntr++;
        Sleep(5);
    }
}
