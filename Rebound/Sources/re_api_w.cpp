#include "re_api_w.h"
#include <QtDebug>
#include <QPair>

int counter = 0;
int child_num = 3;

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
    char buffer[128];
    /*int written = */GetWindowTextA(hwnd, buffer, 128);
    QString log_buffer = QString("0x%1").arg((quintptr)hwnd,
                                             6, 16, QChar('0'));
    ReWinSpec *app = (ReWinSpec *)lParam;
    qDebug() <<log_buffer + QString(":") + buffer + " appname :<" + QString(app->title) + ">";
    if (counter < child_num)
    {
        counter++;
        return TRUE; //skip first occurance, more info on top
    }
    return FALSE;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char buffer[128];
    ReApiW *rebound_api_win = (ReApiW *)lParam;
    int written = GetWindowTextA(hwnd, buffer, 128);
    if(written && strlen(buffer) != 0 && strstr(buffer, "Rebound") == NULL)
    {
        if(IsWindowVisible(hwnd))
        {
            int cloaked;
            DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, 4);
            if(cloaked == 0)
            {
                HWND shell_window = GetShellWindow();
                if(hwnd != shell_window)
                {
                    QString pname = rebound_api_win->reGetPName(rebound_api_win->reGetPid(hwnd));

                    ReWinSpec *new_win_spec = new ReWinSpec;
                    new_win_spec->hWnd = hwnd;
                    new_win_spec->title = buffer;
                    // spotify title doesnt include "spotify" so we add it :D
                    if(pname.contains("spotify", Qt::CaseInsensitive))
                    {
                        new_win_spec->title += " - spotify";
                    }
                    new_win_spec->title = rebound_api_win->reMakeTitleTidy(new_win_spec->title);
                    rebound_api_win->wins_spec.push_back(new_win_spec);

                    rebound_api_win->win_title.push_back(new_win_spec->title);
                }
            }
        }
    }
    return TRUE;
}

ReApiW::ReApiW(QObject *parent) : QObject(parent)
{
    EnumWindows(EnumWindowsProc, (LPARAM) this);
    bijSortTitles();
//    qDebug() << reGetPNameA();
//    HWND app_hwnd = getHWND(win_title.at(2));
//    HWND child_hWnd = NULL;
//    ReWinSpec *app = getWinSpec(win_title.at(2));
//    IAccessible *app_pacc = reGetPAcc(app_hwnd);
//    reListChildren(app_pacc, "");

//    for(int i=0; i<win_title.size(); i++)
//    {
//        qDebug() << win_title.at(i);
//    }
//    QStringList spotify_list = listAllElements(win_title.at(2), "301000000201201", "0000");
//    qDebug() << "--------------";
//    for(int i=0; i<spotify_list.size(); i++)
//    {
//        qDebug() << i << spotify_list.at(i);
//    }

//    VARIANT varChild;
//    varChild.vt = VT_I4;
//    varChild.lVal = CHILDID_SELF;
//    int selector = 0;
//    long cmd_x, cmd_y, cmd_w, cmd_h;

//    counter = 0;
//    child_num = 0;
//    SetForegroundWindow(app_hwnd);
//    SetActiveWindow(app_hwnd);

//    elems_spec[selector]->pAcc->accDoDefaultAction(varChild);
//    elems_spec.at(selector)->pAcc->accLocation(&cmd_x, &cmd_y, &cmd_w, &cmd_h, varChild);
//    SetCursorPos(cmd_x + cmd_w/2, cmd_y + cmd_h/2);
//    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
//    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

long ReApiW::reGetPid(HWND hWnd)
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

void ReApiW::reListChildren(IAccessible *pAcc, QString path)
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

QString ReApiW::reGetPNameA()
{
    return reGetPName(reGetPid(GetActiveWindow())).split("\\").last();
}

QString ReApiW::reMakeTitleTidy(QString app_title)
{
    QStringList app_title_split = app_title.split('-', QString::SkipEmptyParts);
    QString app_name = reRenameAppName(app_title_split.last().simplified());
    QStringList file_name_split = app_title_split[0].split(" ", QString::SkipEmptyParts);
    app_title = app_name + ": " + file_name_split[0].simplified();
    if(file_name_split.size()>1)
    {
        app_title += " " + file_name_split[1].simplified();
    }
    return app_title;
}

QString ReApiW::reRenameAppName(QString app_name)
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
    return app_name;
}

QString ReApiW::reGetPName(long pid)
{
    HANDLE processHandle = NULL;
    processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if(processHandle == NULL)
    {
        qDebug() << "Warning: couldn't get process handle from pid" << pid;
        return "";
    }

    // get name of process handle
    char filename[MAX_PATH];
    if(GetModuleFileNameExA(processHandle, NULL, filename, MAX_PATH) == 0)
    {
        qDebug("Warning: couldn't get name of process handle");
        return "";
    }
    return QString(filename);
}

IAccessible* ReApiW::reGetPAcc(HWND hWnd)
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

long ReApiW::reGetChildCount(IAccessible *pAcc)
{
    long cc;
    pAcc->get_accChildCount(&cc);
    return cc;
}

QString ReApiW::reGetAccName(IAccessible *pAcc, long childId)
{
    BSTR bstrName;
    VARIANT varChild;
    varChild.vt = VT_I4;
    varChild.lVal = childId;
    /*HRESULT hr = */pAcc->get_accName(varChild, &bstrName);
    return QString::fromWCharArray(bstrName);
}

// return Acc specific chilren
IAccessible* ReApiW::reFindAcc(QString path, IAccessible *pAcc)
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

//        qDebug() << QString("--path:") + path + " childCount:" + QString::number(childCount) + " " +
//                 reGetAccName(pAcc, CHILDID_SELF) + " indx:" + QString::number(indx) + " " + QString::number(returnCount);

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

HWND ReApiW::getHWND(QString title)
{
    for(int i=0; i<wins_spec.size(); i++)
    {
        if(title == wins_spec.at(i)->title)
        {
            return wins_spec.at(i)->hWnd;
        }
    }
    return NULL;
}

ReWinSpec* ReApiW::getWinSpec(QString title)
{
    for(int i=0; i<wins_spec.size(); i++)
    {
        if(title == wins_spec.at(i)->title)
        {
            return wins_spec.at(i);
        }
    }
    return NULL;
}

void ReApiW::bijSortTitles()
{
    QStringList sorted_apps, unsorted_apps;
    int clover_ind = 0, firefox_ind = 0, spotify_ind = 0;
    for(int i=0; i<win_title.size(); i++)
    {
        if(win_title.at(i).contains("Clover", Qt::CaseInsensitive))
        {
            sorted_apps.insert(clover_ind, win_title.at(i));
            clover_ind++; firefox_ind++; spotify_ind++;
        }
        else if(win_title.at(i).contains("Firefox", Qt::CaseInsensitive))
        {
            sorted_apps.insert(firefox_ind, win_title.at(i));
            firefox_ind++; spotify_ind++;
        }
        else if(win_title.at(i).contains("Spotify", Qt::CaseInsensitive))
        {
            sorted_apps.insert(spotify_ind, win_title.at(i));
            spotify_ind++;
        }
        else
        {
            unsorted_apps.push_back(win_title.at(i));
        }
    }
    unsorted_apps.sort(Qt::CaseInsensitive);
    win_title = sorted_apps + unsorted_apps;
}

QStringList ReApiW::listAllElements(QString title, QString parent_path, QString child_path)
{
    VARIANT vtChild;
    QStringList ret_list;
    HWND app_hwnd = getHWND(title);
    if(app_hwnd == NULL)
    {
        qDebug() << "Error: can not found hWnd from titles";
        return ret_list;
    }
    IAccessible *app_pacc = reGetPAcc(app_hwnd);
    if(app_pacc == NULL)
    {
        return ret_list;
    }
    IAccessible *parent_pacc = reFindAcc(parent_path, app_pacc);
    if(parent_pacc == NULL)
    {
        return ret_list;
    }

    long returnCount, childCount = reGetChildCount(parent_pacc);
    VARIANT* pArray = new VARIANT[childCount];
    AccessibleChildren(parent_pacc, 0L, childCount, pArray, &returnCount);
    if(returnCount != childCount)
    {
        qDebug() << "Error: not found enough children when gathering them!";
        return ret_list;
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
        ret_list.push_back(elem_spec->name);
    }
    return ret_list;
}
