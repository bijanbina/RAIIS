#include "re_console.h"
#include <QDebug>
#include <QDir>
#include <QThread>
#include "re_keyboard_w.h"
#include "re_state.h"

ReConsole::ReConsole(QObject *parent) : QObject(parent)
{
    std_out = new ReConsoleHandle(RE_CONSOLE_NORML);
    out_thread = new QThread;
    std_out->moveToThread(out_thread);
    out_thread->start();
    std_err = new ReConsoleHandle(RE_CONSOLE_ERROR);
    err_thread = new QThread;
    std_err->moveToThread(err_thread);
    err_thread->start();

    connect(this, SIGNAL(startRead()),
            std_err, SLOT(readData()));
    connect(std_err, SIGNAL(readyData(QString,int)),
            this, SLOT(readyData(QString,int)));
    connect(this, SIGNAL(startRead()),
            std_out, SLOT(readData()));
    connect(std_out, SIGNAL(readyData(QString,int)),
            this, SLOT(readyData(QString,int)));
}

ReConsole::~ReConsole()
{
    qDebug() << "Terminating Process";
    TerminateProcess(piProcInfo.hProcess, 255);
    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);
    CloseHandle(proc_in_h);
    CloseHandle(handle_in);
}

void ReConsole::stopApp()
{
    qDebug() << "Terminating Process";
    TerminateProcess(piProcInfo.hProcess, 255);
    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);
    CloseHandle(proc_in_h);
    CloseHandle(handle_in);
}

void ReConsole::startConsole(QString wsl_path)
{
    is_ready = 0;
    QString current_dir = QDir::currentPath();
    QDir::setCurrent(wsl_path);
    QDir dir_info(wsl_path);

    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    // stdout
    if( !CreatePipe(&(std_out->handle), &proc_out_h, &saAttr, 0) )
    {
       qDebug() << "StdoutRd CreatePipe failed";
    }
    if( !SetHandleInformation(std_out->handle, HANDLE_FLAG_INHERIT, 0) )
    {
       qDebug() << "Stdout SetHandleInformation failed";
    }

    // stdin
    if( !CreatePipe(&proc_in_h, &handle_in, &saAttr, 0) )
    {
       qDebug() << "Stdin CreatePipe failed";
    }
    if( !SetHandleInformation(handle_in, HANDLE_FLAG_INHERIT, 0) )
    {
       qDebug() << "Stdin SetHandleInformation failed";
    }

    // stderr
    if( !CreatePipe(&std_err->handle, &proc_err_h, &saAttr, 0) )
    {
       qDebug() << "Stderr CreatePipe failed";
    }
    if( !SetHandleInformation(std_err->handle, HANDLE_FLAG_INHERIT, 0) )
    {
       qDebug() << "Stderr SetHandleInformation failed";
    }

    CreateCmdProcess();
    QDir::setCurrent(current_dir);

    emit startRead();
}

void ReConsole::CreateCmdProcess()
{
   BOOL ret;
   ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

   STARTUPINFO siStartInfo;
   ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
   siStartInfo.cb = sizeof(STARTUPINFO);
   siStartInfo.hStdError  = proc_err_h;
   siStartInfo.hStdOutput = proc_out_h;
   siStartInfo.hStdInput  = proc_in_h;
   // STARTF_USESHOWWINDOW prevent from showing cmd window
   siStartInfo.dwFlags   |= STARTF_USESTDHANDLES;
   siStartInfo.dwFlags   |= STARTF_USESHOWWINDOW;

   QString cmd = "stream.exe";
   wchar_t cmd_a[200];
   cmd.toWCharArray(cmd_a);
   ret = CreateProcess(NULL,
      cmd_a,              // command line
      NULL,               // process security attributes
      NULL,               // primary thread security attributes
      TRUE,               // handles are inherited
      CREATE_NEW_CONSOLE, // creation flags
      NULL,               // use parent's environment
      NULL,               // use parent's current directory
      &siStartInfo,       // STARTUPINFO pointer
      &piProcInfo);       // receives PROCESS_INFORMATION

   if ( ret==0 )
   {
       qDebug() << "CreateProcess failed";
   }
}

void ReConsole::processLine(QString line)
{
//    qDebug() << "line_fmt" << line;
    if ( !line.contains("\n") )
    {
        ReKeyboard::type(line);
    }
}

void ReConsole::readyData(QString line, int flag)
{
    QStringList lines = line.split("\r");
    int count = lines.count();
    int new_line = 0;
    if( line.back()=="\n" )
    {
        new_line = 1;
    }

    for( int i=0; i<count ; i++)
    {
        if( lines[i].contains("[Start speaking]") )
        {
            is_ready = 1;
            ReState::goToDictate();
        }
        if( lines[i]=="\r" || lines[i].isEmpty() ||
            lines[i].contains(":") ||
            lines[i].contains("\u001B") ||
            lines[i].contains("[") || lines[i].contains("]") ||
            lines[i].contains("(") || lines[i].contains(")") )
        {
            continue;
        }
        else if( is_ready==0 )
        {
            continue;
        }
        qDebug() << i << "line_fmt" << lines[i];

//        if( i<count-1 || new_line )
//        {
//            AbUI::setConsoleLineBuf(lines[i]+"\n");
//            AbUI::addConsoleLine();
//        }
//        else
//        {
//            AbUI::setConsoleLineBuf(lines[i]);
//            AbUI::addConsoleText();
//        }

        if ( lines[i].contains("\n") )
        {
            if( last_line.length() )
            {
                processLine(last_line);
                last_line = "";
            }
        }
        else
        {
            last_line = lines[i];
        }
    }
}
