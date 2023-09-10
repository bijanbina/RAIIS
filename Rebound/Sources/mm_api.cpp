#include "mm_api.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <shobjidl.h>
#include <shlguid.h>
#include <dwmapi.h>
#include <psapi.h> //pname
#include <QThread> //sleep

HWND hwnd_g = NULL;

BOOL CALLBACK EnumWindowsApp(HWND hwnd, LPARAM lParam)
{
    MmApplication *app = (MmApplication *)lParam; // requested pname
    QString win_title = mm_getWinTitle(hwnd);

    // skip hidden window
    if( IsWindowVisible(hwnd)==0 )
    {
        return TRUE;
    }

    // skip windows bs windows
    if( win_title.isEmpty() )
    {
        return TRUE;
    }

    long pid = mm_getPid(hwnd);
    QString pname = mm_getPName(pid);
    pname = QFileInfo(pname).completeBaseName();
    if( pname==app->exe_name )
    {
        qDebug() << "EnumWindowsProc find HWND"
                 << pname << app->exe_name << hwnd
                 << win_title;

        if( win_title.contains(app->win_title) )
        {
            hwnd_g = hwnd;
            return FALSE;
        }
    }

    return TRUE;
}

void mm_getLinkPath(QString path, MmApplication *app)
{
    mm_getLinkPathUser(path, app);
    if( app->exe_path.isEmpty() )
    {
        mm_getLinkPathAll(path, app);
        if( app->exe_path.isEmpty() )
        {
            qDebug() << "Error 24: cannot find shortcut"
                     << path;
        }
    }
}

void mm_getLinkPathUser(QString path, MmApplication *app)
{
    QString lnk = getenv("APPDATA");
    lnk += "\\Microsoft\\Windows\\Start Menu\\Programs\\";
    lnk += path;

    QFile file(lnk);
    if( !(QFileInfo::exists(lnk)) )
    {
        return;
    }

    mm_ResolveIt(lnk.toStdString().c_str(), app);
}

//retreive link from ProgramData instead of user account
void mm_getLinkPathAll(QString path, MmApplication *app)
{
    QString lnk = getenv("PROGRAMDATA");
    lnk += "\\Microsoft\\Windows\\Start Menu\\Programs\\";
    lnk += path;

    mm_ResolveIt(lnk.toStdString().c_str(), app);
}

HRESULT mm_ResolveIt(LPCSTR lnk_path, MmApplication *app)
{
    HRESULT hr;
    IShellLink* psl;
    WCHAR szTargetPath[MAX_PATH];
    WCHAR szDirPath[MAX_PATH];
    WCHAR szDescription[MAX_PATH];
    WIN32_FIND_DATA wfd;

    app->exe_path = ""; // Assume failure

    // Get a pointer to the IShellLink interface. It is assumed that CoInitialize
    // has already been called.
    hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                            IID_IShellLink, (LPVOID*)&psl);
    if( hr )
    {
        qDebug() << "IID_IShellLink Failed" << hr;
        return hr;
    }

    IPersistFile* ppf;

    // Get a pointer to the IPersistFile interface.
    hr = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);
    if( hr )
    {
        qDebug() << "IID_IPersistFile Failed" << hr;
        return hr;
    }

    WCHAR wsz[MAX_PATH];

    // Ensure that the string is Unicode.
    MultiByteToWideChar(CP_ACP, 0, lnk_path, -1, wsz, MAX_PATH);

    // Add code here to check return value from MultiByteWideChar
    // for success.

    // Load the shortcut.
    hr = ppf->Load(wsz, STGM_READ);
    if( hr )
    {
        qDebug() << "ppf->Load Failed" << hr;
        return hr;
    }

    // Resolve the link.
    HWND hwnd = GetActiveWindow();
    hr = psl->Resolve(hwnd, 0);

    if( SUCCEEDED(hr) )
    {
        // Get the path to the link target.
        hr = psl->GetPath(szTargetPath, MAX_PATH, (WIN32_FIND_DATA*)&wfd, SLGP_SHORTPATH);
        hr = psl->GetWorkingDirectory(szDirPath, MAX_PATH);

        // Get the description of the target.
        hr = psl->GetDescription(szDescription, MAX_PATH);

        app->exe_path    = QString::fromStdWString(szTargetPath);
        app->working_dir = QString::fromStdWString(szDirPath);
    }

    // Release the pointer to the IPersistFile interface.
    ppf->Release();

    // Release the pointer to the IShellLink interface.
    psl->Release();

    return hr;
}

MmApplication mm_launchLnk(QString app_name, QString arg)
{
    app_name += ".lnk";
    MmApplication app;
    mm_getLinkPath(app_name, &app);
    QFileInfo fi(app.exe_path);
    app.exe_name = fi.completeBaseName();

    mm_launchApp(&app, arg);

    return app;
}

void mm_launchApp(MmApplication *app, QString arg)
{
    if( arg.length() )
    {
        app->exe_path += " " + arg;
    }

    PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
    STARTUPINFOA StartupInfo; //This is an [in] parameter

    ZeroMemory( &StartupInfo, sizeof(StartupInfo) );
    StartupInfo.cb = sizeof(StartupInfo);
    ZeroMemory( &ProcessInfo, sizeof(ProcessInfo) );

    char app_cmd[200];
    strcpy(app_cmd, app->exe_path.toStdString().c_str());

    int ret = CreateProcessA(NULL, app_cmd, NULL,
                             NULL, FALSE, 0, NULL,
                             app->working_dir.toStdString().c_str(),
                             &StartupInfo, &ProcessInfo);
    if( ret==0 )
    {
        long last_error = GetLastError();
        qDebug() << "Error 26: CreateProcess failed" << last_error
                 << "path" << app->exe_path
                 << "dir" << app->working_dir;
    }
}

void mm_launchScript(QString path, QString arg)
{
    QString cmd = path + arg;

    PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
    STARTUPINFOA StartupInfo; //This is an [in] parameter

    ZeroMemory( &StartupInfo, sizeof(StartupInfo) );
    StartupInfo.cb = sizeof(StartupInfo);
    ZeroMemory( &ProcessInfo, sizeof(ProcessInfo) );

    char app_cmd[200];
    strcpy(app_cmd, path.toStdString().c_str());

    int ret = CreateProcessA(NULL, app_cmd, NULL,
                             NULL, FALSE, 0, NULL,
                             NULL, &StartupInfo,
                             &ProcessInfo);
    if( ret==0 )
    {
        long last_error = GetLastError();
        qDebug() << "Error 25: CreateProcess failed" << last_error
                 << "path" << path;
    }
}

void mm_closeWindow()
{
    DWORD dwCurrentThread = GetCurrentThreadId();
    DWORD dwFGThread = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
    AttachThreadInput(dwCurrentThread, dwFGThread, TRUE);

    HWND hwnd = GetForegroundWindow();
    PostMessage(hwnd, WM_CLOSE, 0, 0);

    AttachThreadInput(dwCurrentThread, dwFGThread, FALSE);
}

void mm_focus(HWND hwnd)
{
    DWORD dwCurrentThread = GetCurrentThreadId();
    DWORD dwFGThread = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
    AttachThreadInput(dwCurrentThread, dwFGThread, TRUE);

    AllowSetForegroundWindow(ASFW_ANY);
    LockSetForegroundWindow(LSFW_UNLOCK);
    BringWindowToTop(hwnd);
    SetForegroundWindow(hwnd);
    SetActiveWindow(hwnd);

    // If window is minimzed
    if( IsIconic(hwnd) )
    {
        ShowWindow(hwnd, SW_RESTORE);
    }

    AttachThreadInput(dwCurrentThread, dwFGThread, FALSE);
}

void mm_focus(MmApplication app)
{
//    qDebug() << "app tit" << app.win_title;
    app.hwnd = mm_getHWND(&app);
    while( app.hwnd==NULL )
    {
//        qDebug() << "hwnd" << app.hwnd
//                 << "exe_name" << app.exe_name
//                 << "exe_path" << app.exe_path;
        QThread::msleep(200);
        app.hwnd = mm_getHWND(&app);
    }
    mm_focus(app.hwnd);
}

HWND mm_getHWND(MmApplication *app)
{
    hwnd_g = 0;
    EnumWindows(EnumWindowsApp, (LPARAM) app);
    return hwnd_g;
}

QString mm_getWinTitle(HWND hwnd)
{
    char buffer[MAX_TITLE_LEN];
    int written = GetWindowTextA(hwnd, buffer, MAX_TITLE_LEN);
    if( written==0 )
    {
        return "";
    }

    QString ret = buffer;
    return ret;
}

long mm_getPid(HWND hWnd)
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

QString mm_getPName(long pid)
{
    HANDLE processHandle = NULL;
//    processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
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
//        qDebug("Warning: couldn't get name of process handle");
        return "";
    }
    return QString(filename);
}
