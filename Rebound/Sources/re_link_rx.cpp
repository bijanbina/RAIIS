#include <QThread>
#include "re_link_rx.h"
#include "backend.h"

ReLinkRx::ReLinkRx()
{
    createPipe();
}

#ifdef WIN32
void ReLinkRx::createPipe()
{
    while( 1 )
    {
        SECURITY_ATTRIBUTES sa;
        SECURITY_DESCRIPTOR sd;

        InitializeSecurityDescriptor(&sd,
                                     SECURITY_DESCRIPTOR_REVISION);
        SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);

        sa.nLength = sizeof(sa);
        sa.lpSecurityDescriptor = &sd;
        sa.bInheritHandle       = FALSE;

        // To create an instance of a named pipe by using CreateNamedPipe,
        // the user must have FILE_CREATE_PIPE_INSTANCE access to the named pipe object.
        hPipe = CreateNamedPipeA(RE_PIPE_LINKTX,
                                 PIPE_ACCESS_INBOUND,            // dwOpenMode. The flow of data in the pipe goes from client to server only
                                 PIPE_TYPE_BYTE | PIPE_WAIT,     // dwPipeMode
                                 1,                              // nMaxInstances
                                 PIPE_BUFFER_SIZE,               // nOutBufferSize
                                 PIPE_BUFFER_SIZE,               // nInBufferSize
                                 NMPWAIT_WAIT_FOREVER,           // nDefaultTimeOut
                                 &sa);                       // lpSecurityAttributes
        qDebug() << "ReLinkRx::createPipe" << hPipe;

        if( hPipe==INVALID_HANDLE_VALUE )
        {
            qDebug() << RE_PIPE_LINKTX << "Failed";
        }
        else
        {
            break;
        }
        QThread::msleep(500);
    }
}
#endif

void ReLinkRx::listenPipe()
{
    char buffer[PIPE_BUFFER_SIZE];
    DWORD dwRead;
    qDebug() << "ReLinkRx::listenPipe: hpipe" << hPipe;
    while( hPipe!=INVALID_HANDLE_VALUE )
    {
        // wait for someone to connect to the pipe
        if( ConnectNamedPipe(hPipe, nullptr)!=FALSE )
        {
            while( ReadFile(hPipe, buffer, sizeof(buffer)-1
                            , &dwRead, nullptr)!=FALSE )
            {
                // add terminating zero
                buffer[dwRead] = 0;
                QString input(buffer);

                QStringList lines = input.split
                                    ("\n", QString::
                                     SkipEmptyParts);

                for(int i=0 ; i<lines.length() ; i++)
                {
                    processLine(lines[i]);
                }
            }
        }

        qDebug() << "ReChannelW::Client Disconnected";
        DisconnectNamedPipe(hPipe);
    }
}

void ReLinkRx::processLine(QString line)
{
//    qDebug() << "ReLinkRx::processLine" << line;
    line = line.trimmed();
    QStringList fields = line.split(" ",
                               QString::SkipEmptyParts);

    QString cmd_type, cmd_data;
    if ( fields.length()>0 )
    {
        cmd_type = fields[0];
    }
    if ( fields.length()>1 )
    {
        cmd_data = fields[1];
    }

    processCmd(cmd_type, cmd_data);
}

void ReLinkRx::processCmd(QString cmd_type, QString cmd_data)
{
    if( cmd_type=="url" )
    {
        curr_url = cmd_data;
        qDebug() << "ReLinkRx::processUrl"
                 << "url_data" << cmd_data;
    }
    else if( cmd_type=="paste" )
    {
        putInClipboard(cmd_data);
    }
    else if( cmd_type=="click" )
    {
        QStringList data_s = cmd_data.split(",");
        int x = data_s[0].trimmed().toInt();
        int y = data_s[1].trimmed().toInt();
        int w = data_s[2].trimmed().toInt();
        int h = data_s[3].trimmed().toInt();
        SetCursorPos((x + w/2)*1.25, (y + h/2)*1.25 + 175);

        qDebug() << "ReLinkRx::click" << cmd_data
                 << x << w << data_s;
    }
    else if( cmd_type=="sms" )
    {
        qDebug() << "ReLinkRx::sms" << cmd_data;
        putInClipboard(cmd_data);
        ReKeyboard::pressKey(KEY_LEFTCTRL);
        ReKeyboard::sendKey(KEY_V);
        ReKeyboard::releaseKey(KEY_LEFTCTRL);
    }
    else
    {
        qDebug() << "ReLinkRx::processCmd"
                 << "cmd_type" << cmd_type
                 << "cmd_data" << cmd_data;
    }
}
