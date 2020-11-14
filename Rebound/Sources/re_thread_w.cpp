#include "re_thread_w.h"

#define re_state_mode *(thread_data->mode)

int counter = 0;
int child_num = 3;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char buffer[128];
    ReThreadW *thread_win = (ReThreadW *)lParam;
    int written = GetWindowTextA(hwnd, buffer, 128);
    if(written && strlen(buffer) != 0 && strcmp(buffer, "Rebound") != 0)
    {
        re_AddHwnd(hwnd, thread_win);
    }
    return TRUE;
}

//Add a new Hwnd to wins_title vector
void re_AddHwnd(HWND hwnd, ReThreadW *thread_win)
{
    char buffer[128];
    RECT rc;

    if(IsWindowVisible(hwnd))
    {
        int cloaked;
        DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, 4);
        if(cloaked)
        {
            HWND shell_window = GetShellWindow();
            GetWindowRect(hwnd, &rc);
            int width = rc.right - rc.left;

            if((hwnd!=shell_window) && (rc.bottom>0) && (width>100) )
            {
                int success = GetWindowTextA(hwnd, buffer, 128); //get title

                if ( success==0 )
                {
                    qDebug() << hwnd << "Failed to GetWindowTextA";
                }

                QString pname = reGetPName(reGetPid(hwnd));

                ReWinSpec win_spec;
                win_spec.hWnd = hwnd;
                win_spec.title = buffer;
                // spotify title doesnt include "spotify" so we add it :D
                if(pname.contains("spotify", Qt::CaseInsensitive))
                {
                    win_spec.title += " - spotify";
                }
                win_spec.title = thread_win->cleanTitle(win_spec.title);
                thread_win->wins_spec.push_back(win_spec);

                thread_win->wins_title.push_back(win_spec.title);

                int a = 0;
                DwmGetWindowAttribute(hwnd, DWMWA_DISALLOW_PEEK, &a, 4);


                qDebug() << win_spec.title;
            }
        }
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
        return "Firefox";
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

void ReThreadW::sortTitles()
{
    QStringList sorted_apps, unsorted_apps;
    int clover_ind = 0, firefox_ind = 0, spotify_ind = 0;
    for(int i=0; i<wins_title.size(); i++)
    {
        if(wins_title.at(i).contains("Clover", Qt::CaseInsensitive))
        {
            sorted_apps.insert(clover_ind, wins_title.at(i));
            clover_ind++; firefox_ind++; spotify_ind++;
        }
        else if(wins_title.at(i).contains("Firefox", Qt::CaseInsensitive))
        {
            sorted_apps.insert(firefox_ind, wins_title.at(i));
            firefox_ind++; spotify_ind++;
        }
        else if(wins_title.at(i).contains("Spotify", Qt::CaseInsensitive))
        {
            sorted_apps.insert(spotify_ind, wins_title.at(i));
            spotify_ind++;
        }
        else
        {
            unsorted_apps.push_back(wins_title.at(i));
        }
    }
    unsorted_apps.sort(Qt::CaseInsensitive);
    wins_title = sorted_apps + unsorted_apps;
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
    char filename[MAX_PATH];
    if(GetProcessImageFileNameA(processHandle, filename, MAX_PATH) == 0)
    {
        qDebug() << "Error" << GetLastError() << " : Fail to get Pname of " << pid;
        return "";
    }
    return QString(filename);
}

HWND ReThreadW::getHWND(QString title)
{
    for(int i=0; i<wins_spec.size(); i++)
    {
        if(title == wins_spec[i].title)
        {
            return wins_spec[i].hWnd;
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
    for(int i=0; i<wins_title.size(); i++)
    {
        if(wins_title[i].contains(app_name, Qt::CaseInsensitive))
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

ReWinSpec ReThreadW::getWinSpec(QString title)
{
    for(int i=0; i<wins_spec.size(); i++)
    {
        if(title == wins_spec[i].title)
        {
            return wins_spec[i];
        }
    }

    ReWinSpec shit;
    return shit;
}

QString ReThreadW::getWinTitle(int index)
{
    if(index < wins_title.size())
    {
        return wins_title[index];
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
    VARIANT vtChild;
    int index = getIndex(app_name);
    if(index < 0)
    {
        qDebug() << "Error: can not found" << app_name;
        return;
    }
    HWND app_hwnd = getHWND(wins_title[index]);
    if(app_hwnd == NULL)
    {
        qDebug() << "Error: can not found hWnd from titles";
        return;
    }
    IAccessible *app_pacc = reGetPAcc(app_hwnd);
    if(app_pacc == NULL)
    {
        return;
    }
    IAccessible *parent_pacc = reFindAcc(parent_path, app_pacc);
    if(parent_pacc == NULL)
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
        if(pChild == NULL)
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

void ReThreadW::selectButton(QString name)
{
    ReElemSpec *elem_spec = getElemSpec(name);
    HWND app_hwnd = getHWND(wins_title[2]);
    HWND child_hWnd = NULL;
    ReWinSpec app = getWinSpec(wins_title[2]);
    IAccessible *app_pacc = reGetPAcc(app_hwnd);
    reListChildren(app_pacc, "");

    for(int i=0; i<wins_title.size(); i++)
    {
        qDebug() << wins_title[i];
    }
    updateElements(wins_title[2],
                   RE_SPOTIFY_ALBUM_PARENT, RE_SPOTIFY_ALBUM_CHILD);


    VARIANT varChild;
    varChild.vt = VT_I4;
    varChild.lVal = CHILDID_SELF;
    int selector = 0;
    long cmd_x, cmd_y, cmd_w, cmd_h;

    counter = 0;
    child_num = 0;
    SetForegroundWindow(app_hwnd);
    SetActiveWindow(app_hwnd);

    elems_spec[selector]->pAcc->accDoDefaultAction(varChild);
    elems_spec[selector]->pAcc->accLocation(&cmd_x, &cmd_y, &cmd_w, &cmd_h, varChild);
    SetCursorPos(cmd_x + cmd_w/2, cmd_y + cmd_h/2);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

ReThreadW::ReThreadW(threadStruct *thread_data)
{
    this->thread_data = thread_data;
}

void ReThreadW::cleanWins()
{
    wins_title.clear();
    wins_spec.clear();
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
    for(int i=0; i<wins_title.size(); i++)
    {
        if(i < thread_data->wins_title->size())
        {
            (*(thread_data->wins_title))[i] = wins_title[i];
        }
        else
        {
            thread_data->wins_title->push_back(wins_title[i]);
        }
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
        if(cntr == 200)
        {
            if(re_state_mode == RE_MODE_HIDDEN)
            {
                priv->cleanWins();
                EnumWindows(EnumWindowsProc, (LPARAM) priv);
                priv->sortTitles();
                priv->syncWinsTitle();
            }
            else if(re_state_mode == RE_MODE_MAIN)
            {
                priv->cleanElems();
                priv->updateElements("spotify", RE_SPOTIFY_ALBUM_PARENT,
                                     RE_SPOTIFY_ALBUM_CHILD);
                priv->syncElemsName();
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
