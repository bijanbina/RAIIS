#include "re_pipe.h"

HANDLE RePipe::pipe_chess = NULL;
HANDLE RePipe::pipe_mom = NULL;

RePipe::RePipe()
{
}

void RePipe::init()
{
    pipe_chess = connectPipe(RE_PIPE_CHESS);
    pipe_mom   = connectPipe(RE_PIPE_MOM);
}

HANDLE RePipe::connectPipe(const char *pipe_name)
{
    // 0: Default Wait Time
    int ready = WaitNamedPipeA(pipe_name, 0);
    HANDLE hPipe;
    if( ready )
    {
        hPipe = CreateFileA(pipe_name, GENERIC_WRITE, // dwDesiredAccess
                            0, nullptr,    // lpSecurityAttributes
                            OPEN_EXISTING,  // dwCreationDisposition
                            0, nullptr);    // hTemplateFile

        if( hPipe==INVALID_HANDLE_VALUE )
        {
            qDebug() << "Error 120: Cannot connect"
                     << pipe_name;
        }
    }
    else
    {
        hPipe = INVALID_HANDLE_VALUE;
        qDebug() << "Error 121: Pipe "
                 << pipe_name << " not found";
    }

    return hPipe;
}

void RePipe::sendChess(const char *data)
{
    DWORD len = strlen(data);
    if( pipe_chess==INVALID_HANDLE_VALUE )
    {
        qDebug() << "Try to reconnect to"
                 << RE_PIPE_CHESS;

        pipe_chess = connectPipe(RE_PIPE_CHESS);
        if( pipe_chess==INVALID_HANDLE_VALUE )
        {
            return;
        }
    }

    DWORD dwWritten;
    int success = WriteFile(pipe_chess, data, len, &dwWritten, NULL);
    if( !success )
    {
        qDebug() << "Error: NamedPipe writing failed," << GetLastError();
    }

    if( dwWritten!=len )
    {
        qDebug() << "Error: Wrong writing length."
                    "Try to revive channel";
        CloseHandle(pipe_chess);
        pipe_chess = INVALID_HANDLE_VALUE;
        sendChess(data);
    }
}

void RePipe::sendMom(const char *data)
{
    DWORD len = strlen(data);
    if( pipe_mom==INVALID_HANDLE_VALUE )
    {
        qDebug() << "Try to reconnect to"
                 << RE_PIPE_MOM;

        pipe_mom = connectPipe(RE_PIPE_MOM);
        if( pipe_mom==INVALID_HANDLE_VALUE )
        {
            return;
        }
    }

    DWORD dwWritten;
    int success = WriteFile(pipe_mom, data, len, &dwWritten, NULL);
    if( !success )
    {
        qDebug() << "Error: NamedPipe writing failed," << GetLastError();
    }

    if( dwWritten!=len )
    {
        qDebug() << "Error: Wrong writing length."
                    "Try to revive channel";
        CloseHandle(pipe_mom);
        pipe_mom = INVALID_HANDLE_VALUE;
        sendChess(data);
    }
}
