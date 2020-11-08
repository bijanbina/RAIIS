#include "re_api_w.h"

ReApiW::ReApiW(QObject *parent) : QObject(parent)
{

}

long ReApiW::getPid(HWND hWnd)
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

QString ReApiW::getPNameA()
{
    long active_pid = getPid(GetForegroundWindow());
    QString app_path = getPName(active_pid);
    QString app_name = app_path.split("\\").last();

    return app_name;
}

QString ReApiW::getPName(long pid)
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
//        qDebug("Warning: couldn't get name of process handle");
        return "";
    }
    return QString(filename);
}

QString ReApiW::getElemName(int index)
{
    if(index < elems_name.size())
    {
        return elems_name[index];
    }
    return "";
}

QString ReApiW::getWinTitle(int index)
{
    if(index < wins_title.size())
    {
        return wins_title[index];
    }
    return "";
}

QString ReApiW::getAccName(IAccessible *pAcc, long childId)
{
    BSTR bstrName;
    VARIANT varChild;
    varChild.vt = VT_I4;
    varChild.lVal = childId;
    /*HRESULT hr = */pAcc->get_accName(varChild, &bstrName);
    return QString::fromWCharArray(bstrName);
}
