#include "re_win32_win.h"
#include "backend.h"

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
