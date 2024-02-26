#include "re_link.h"

ReLink::ReLink()
{
    connectPipe();
}

void ReLink::connectPipe()
{
    // 0: Default Wait Time
    int np_is_available = WaitNamedPipeA(RE_PIPE_LINK, 0);
    if( np_is_available )
    {
        hPipe = CreateFileA(RE_PIPE_LINK, GENERIC_WRITE, // dwDesiredAccess
                            0, nullptr,    // lpSecurityAttributes
                            OPEN_EXISTING,  // dwCreationDisposition
                            0, nullptr);    // hTemplateFile

        if( hPipe==INVALID_HANDLE_VALUE )
        {
            qDebug() << "Error 120: Cannot connect " RE_PIPE_LINK;
        }
    }
    else
    {
        hPipe = INVALID_HANDLE_VALUE;
        qDebug() << "Error 121: Pipe " RE_PIPE_LINK
                    " not found";
    }
}

void ReLink::sendPipe(const char *data)
{
    DWORD len = strlen(data);
    if( hPipe==INVALID_HANDLE_VALUE )
    {
        qDebug() << "Try to reconnect to"
                 << RE_PIPE_LINK;
        connectPipe();
        if( hPipe==INVALID_HANDLE_VALUE )
        {
            return;
        }
    }

    DWORD dwWritten;
    int success = WriteFile(hPipe, data, len, &dwWritten, NULL);
    if( !success )
    {
        qDebug() << "Error: NamedPipe writing failed," << GetLastError();
    }

    if( dwWritten!=len )
    {
        qDebug() << "Error: Wrong writing length."
                    "Try to revive channel";
        CloseHandle(hPipe);
        hPipe = INVALID_HANDLE_VALUE;
        sendPipe(data);
    }
}

void ReLink::scrollUp(int speed)
{
    sc_speed = speed-1;
    sc_dir = RE_META_SKY;
    QString cmd = "scroll: ";
    cmd += QString::number(-step_table[sc_speed]);
    cmd += " ";
    cmd += QString::number(speed_table[sc_speed]);
    sendPipe(cmd.toStdString().c_str());
}

void ReLink::scrollDown(int speed)
{
    sc_speed = speed-1;
    sc_dir = RE_META_DIVE;
    QString cmd = "scroll: ";
    cmd += QString::number(step_table[sc_speed]);
    cmd += " ";
    cmd += QString::number(speed_table[sc_speed]);
    sendPipe(cmd.toStdString().c_str());
}

void ReLink::scrollEscape()
{
    sc_dir = 0;
    QString cmd = "scroll: 0 0";
    sendPipe(cmd.toStdString().c_str());
}
