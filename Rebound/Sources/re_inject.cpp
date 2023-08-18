#include "re_inject.h"
#include <QDebug>
#include <QDir>
#include <tlhelp32.h>
#include <tchar.h>

ReInject::ReInject(QObject *parent) : QObject(parent)
{

}

void ReInject::inject(int pid)
{
//    if( isInjected(pid) )
//    {
//        return;
//    }

    qDebug() << ">>>>>>>>>>>>>>>inject" << pid;
    HANDLE process_h = OpenProcess(PROCESS_ALL_ACCESS,
                          false, pid);
    QString path = getDllPath();
    LPCSTR dll_path = getDllPath().toStdString().c_str();
//    LPCSTR dll_path = INJ_DLL_ADDRESS;
    // Allocate memory for the dllpath in the target process
    // length of the path string + null terminator
    LPVOID pDllPath = VirtualAllocEx(process_h, 0, strlen(dll_path) + 1,
        MEM_COMMIT, PAGE_READWRITE);

    // Write the path to the address of the memory we just allocated
    // in the target process
    WriteProcessMemory(process_h, pDllPath, (LPVOID)dll_path,
        strlen(dll_path) + 1, 0);

    HINSTANCE ker_h = GetModuleHandleA("Kernel32.dll");
    LPTHREAD_START_ROUTINE sr_addr = (LPTHREAD_START_ROUTINE)
            GetProcAddress(ker_h, "LoadLibraryA");

    // Create a Remote Thread in the target process which
    // calls LoadLibraryA as our dllpath as an argument -> program loads our dll
    HANDLE dll_thread = CreateRemoteThread(process_h, 0, 0,
        sr_addr, pDllPath, 0, 0);
    DWORD error = GetLastError();
    if( dll_thread==NULL )
    {
        qDebug() << "Failed to set the hook. Error code: "
                 << error;
    }

    // Wait for the execution of our loader thread to finish
    WaitForSingleObject(dll_thread, INFINITE);

    qDebug() << "path addr" << pDllPath
             << process_h << pid;

    qDebug() << "ker_h" << ker_h
             << (int *)sr_addr << dll_thread;

    apps_pid.push_back(pid);

    // Unload the dll, so we can run again if we choose
    // Get the handle of the now loaded module
    HANDLE dll_handle;
//    GetExitCodeThread(dll_thread, &dll_handle);
    dll_handle = getDllHandle(pid, path);
    if( dll_handle==NULL )
    {
        qDebug() << "I SAW NULL";
        return;
    }

//    LPTHREAD_START_ROUTINE fl_addr = (LPTHREAD_START_ROUTINE)
//            GetProcAddress(ker_h, "FreeLibrary");
//    HANDLE Free_thread = CreateRemoteThread(process_h, NULL, NULL,
//        fl_addr, (LPVOID)dll_handle, NULL, NULL);
//    WaitForSingleObject(Free_thread, INFINITE);
//    qDebug() << "KKKKKKKKKKKK" << dll_handle << (int *)fl_addr << Free_thread;
}

QString ReInject::getDllPath()
{
    QString dll_path = QDir::currentPath();
//    qDebug() << "getDllPath 1" << dll_path;
    QStringList dll_path_split = dll_path.split("/", Qt::SkipEmptyParts);
    dll_path_split.removeLast(); // rebound
    dll_path_split.removeLast(); // raiis
    dll_path = dll_path_split.join("/");
//    qDebug() << "getDllPath 2" << dll_path;
    dll_path += QDir::separator();
    dll_path += INJ_DLL_ADDRESS;
    dll_path.replace("/", "\\");
//    qDebug() << "getDllPath 3" << dll_path;
    return  dll_path;
}

// check input pid with all saved pids, to prevent repeatitve injection
int ReInject::isInjected(int pid)
{
    int len = apps_pid.size();
    for( int i=0 ; i<len ; i++ )
    {
        if( pid==apps_pid[i] )
        {
            return 1;
        }
    }
    return 0;
}

HANDLE ReInject::getDllHandle(int pid, QString path)
{
    BOOL bMore = FALSE;
    HANDLE handle;
    MODULEENTRY32 me = {sizeof(me)};
    handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    bMore = Module32First(handle, &me);
    for(; bMore; bMore = Module32Next(handle, &me))
    {
        QString module_name = QString::fromWCharArray(me.szModule);
        QString dll_path = QString::fromWCharArray(me.szExePath);
//        qDebug() << "==)) " << dll_path;
        if( path==dll_path )
        {
            return handle;
        }
    }
    return NULL;
}
