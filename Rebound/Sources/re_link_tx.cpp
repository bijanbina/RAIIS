#include "re_link_tx.h"

ReLinkTx::ReLinkTx()
{
    connectPipe();
}

#ifdef WIN32
void ReLinkTx::connectPipe()
{
    // 0: Default Wait Time
    int np_is_available = WaitNamedPipeA(RE_PIPE_LINKRX, 0);
    if( np_is_available )
    {
        hPipe = CreateFileA(RE_PIPE_LINKRX,
                            GENERIC_WRITE,  // dwDesiredAccess
                            0, nullptr,     // lpSecurityAttributes
                            OPEN_EXISTING,  // dwCreationDisposition
                            0, nullptr);    // hTemplateFile

        if( hPipe==INVALID_HANDLE_VALUE )
        {
            qDebug() << "Error 120: Cannot connect "
                     << RE_PIPE_LINKRX;
        }
    }
    else
    {
        hPipe = INVALID_HANDLE_VALUE;
        qDebug() << "Error 121: Pipe " RE_PIPE_LINKRX
                    " not found";
    }
}
#endif

void ReLinkTx::sendPipe(const char *data)
{
#ifdef WIN32
    DWORD len = strlen(data);
    if( hPipe==INVALID_HANDLE_VALUE )
    {
        qDebug() << "Try to reconnect to"
                 << RE_PIPE_LINKRX;
        connectPipe();
        if( hPipe==INVALID_HANDLE_VALUE )
        {
            return;
        }
    }

    DWORD dwWritten;
    int success = WriteFile(hPipe, data, len, &dwWritten,
                            NULL);
    if( !success )
    {
        qDebug() << "Error: NamedPipe writing failed,"
                 << GetLastError();
    }

    if( dwWritten!=len )
    {
        qDebug() << "Error: Wrong writing length."
                    "Try to revive channel";
        CloseHandle(hPipe);
        hPipe = INVALID_HANDLE_VALUE;
        sendPipe(data);
    }
#else
    QString cmd = "dbus-send --session ";
    cmd += "--dest=" RE_PIPE_LINK " / " RE_PIPE_LINK ".exec string:\"";
    cmd += data;
    cmd += "\"";
    system(cmd.toStdString().c_str());
#endif
}

void ReLinkTx::scrollUp(int speed)
{
    sc_speed = speed-1;
    sc_dir = RE_SUPER_SKY;
    QString cmd = "scroll: ";
    cmd += QString::number(-step_table[sc_speed]);
    cmd += " ";
    cmd += QString::number(speed_table[sc_speed]);
    sendPipe(cmd.toStdString().c_str());
}

void ReLinkTx::scrollDown(int speed)
{
    sc_speed = speed-1;
    sc_dir = RE_SUPER_DIVE;
    QString cmd = "scroll: ";
    cmd += QString::number(step_table[sc_speed]);
    cmd += " ";
    cmd += QString::number(speed_table[sc_speed]);
    sendPipe(cmd.toStdString().c_str());
}

void ReLinkTx::scrollPos(QString pos)
{
    QString cmd = "scroll: ";
    cmd += pos;
    sendPipe(cmd.toStdString().c_str());
}

void ReLinkTx::scrollEscape()
{
    sc_dir = 0;
    QString cmd = "scroll: 0 0";
    sendPipe(cmd.toStdString().c_str());
}
