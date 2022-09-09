#include "backend.h"
#include <QFile>

int getIntCommand(char *command)
{
    FILE *fp;
    int returnData;

    char path[1035];

    /* Open the command for reading. */
    fp = popen(command, "r");

    if (fp == NULL)
    {
        printf("Failed to run command\n" );
        return -1;
    }

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL)
    {
        returnData = atoi(path);
    }

    /* close */
    pclose(fp);
    return returnData;
}

QString getStrCommand(QString command)
{
    FILE *fp;
    QString returnData;

    char path[1035];

    /* Open the command for reading. */
    fp = popen(command.toStdString().c_str(), "r");

    if (fp == NULL)
    {
        printf("Failed to run command\n" );
        return returnData;
    }

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL)
    {
        returnData += QString(path);
    }

    // Remove last \n
    returnData.remove(returnData.length()-1,1);

    /* close */
    pclose(fp);
    return returnData;
}

screen_pos getPrimaryScreen()
{
    FILE *fp;
    screen_pos returnData;
    returnData.x = -1;
    returnData.y = -1;
    returnData.x = getIntCommand("xrandr --current | grep primary | awk '{print $4}' | awk -F '+' '{print $2}'");
    returnData.y = getIntCommand("xrandr --current | grep primary | awk '{print $4}' | awk -F '+' '{print $3}'");
    return returnData;
}

void updateScreenInfo(QObject *item)
{

    //    screen_pos PrimaryScreen = getPrimaryScreen();
    //    QQmlProperty::write(item, "x_base", PrimaryScreen.x);
    //    QQmlProperty::write(item, "y_base", PrimaryScreen.y);

    //    int minimumWidth = QQmlProperty::read(item, "minimumWidth");
    //    int minimumHeight = QQmlProperty::read(item, "minimumHeight");
    //    x:x_base + (Screen.width  - minimumWidth)  / 2
    //    y:y_base + (Screen.height - minimumHeight) / 2

#ifdef __linux__
    QQmlProperty::write(item, "minimumHeight", 400);
    //    QQmlProperty::write(item, "visible", 1);
#endif

#ifdef _WIN32
    //    QQmlProperty::write(item, "minimumHeight", 400);
    QQmlProperty::write(item, "minimumHeight", 300);
#endif

    //    QMetaObject::invokeMethod(item, "show");
}

int isItemVisible(QObject *item)
{
    if ( item != NULL )
    {
        int visible = QQmlProperty::read(item, "visible").toInt();
        return visible;
    }
    else
    {
        return 0;
    }
}

#ifdef WIN32

void executeAhk(QString name)
{
    PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
    STARTUPINFOA StartupInfo; //This is an [in] parameter

    ZeroMemory( &StartupInfo, sizeof(StartupInfo) );
    StartupInfo.cb = sizeof(StartupInfo);
    ZeroMemory( &ProcessInfo, sizeof(ProcessInfo) );

    QString command = "\"C:\\Program Files\\AutoHotkey\\AutoHotkey.exe\" AHK\\" + name + ".ahk";
    char app_cmd[200];
    strcpy(app_cmd, command.toStdString().c_str());

    int ret = CreateProcessA(NULL, app_cmd, NULL,
                             NULL, FALSE, 0, NULL,
                             NULL, &StartupInfo,
                             &ProcessInfo);
    if( ret == 0 )
    {
        long last_error = GetLastError();
        qDebug() << "CreateProcess failed" << last_error;
    }
}

void executScript(QString name, int id)
{
    PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
    STARTUPINFOA StartupInfo; //This is an [in] parameter

    ZeroMemory( &StartupInfo, sizeof(StartupInfo) );
    StartupInfo.cb = sizeof(StartupInfo);
    ZeroMemory( &ProcessInfo, sizeof(ProcessInfo) );

    QString command = "\"C:\\Program Files\\AutoHotkey\\AutoHotkey.exe\" AHK\\";

    if ( id==RE_SCR_YOUTUBE )
    {
        command += "button_youtube.ahk ";
    }
    else if ( id==RE_SCR_UI )
    {
        command += "button_ui.ahk ";
    }
    else if ( id==RE_SCR_SPOTIFY )
    {
        command += "button_spotify.ahk ";
    }
    else
    {
        qDebug() << "Unknown execute script ID";
    }
    command += name;
    char app_cmd[200];
    strcpy(app_cmd, command.toStdString().c_str());

    int ret = CreateProcessA(NULL, app_cmd, NULL,
                             NULL, FALSE, 0, NULL,
                             NULL, &StartupInfo,
                             &ProcessInfo);
    if( ret == 0 )
    {
        long last_error = GetLastError();
        qDebug() << "CreateProcess failed" << last_error;
    }
}

#endif
