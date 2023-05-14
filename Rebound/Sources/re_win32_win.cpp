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
    if(GetModuleFileNameExA(processHandle, NULL, path_buff, MAX_PATH) == 0)
    {
        qDebug() << "Error" << GetLastError() << " : Fail to get Pname of " << pid;
        return "";
    }

    // resolve short 8.3 format and get rid of ~
    char path_r[MAX_PATH];
    if( GetLongPathNameA(path_buff, path_r, MAX_PATH)==0 )
    {
        qDebug() << "Error" << GetLastError();
    }

    QString path_q = path_r; //process filename
    QStringList path_list = path_q.split("\\", QString::SkipEmptyParts);
    QString filename = path_list.last();
    filename.remove(".exe");
//    qDebug() << "path_buff" << path_q;

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
