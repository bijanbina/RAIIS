#include "re_execw.h"
#include <QThread>

ReExecW::ReExecW(QObject *item, QObject *parent) : QObject(parent)
{
    ui = item;
    chapar = new ReChapar(item);
    chapar->setMode(RE_MODE_APPLICATION);
}

void ReExecW::buttonAPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("a");
    }
    else
    {
        executeAhk("button_a");
    }
}

void ReExecW::buttonBPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("b");
    }
    else
    {
        executeAhk("button_b");
    }
}

void ReExecW::buttonXPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("x");
    }
    else
    {
        executeAhk("button_x");
    }
}

void ReExecW::buttonYPressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("y");
    }
    else
    {
        executeAhk("button_y");
    }
}

void ReExecW::buttonL1Pressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("l1");
    }
    else
    {
        executeAhk("button_l1");
    }
}

void ReExecW::buttonL2Pressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("l2");
    }
    else
    {
        executeAhk("button_l2");
    }
}

void ReExecW::buttonR1Pressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("r1");
    }
    else
    {
        executeAhk("button_r1");
    }
}

void ReExecW::buttonR2Pressed()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("r2");
    }
    else
    {
        executeAhk("button_r2");
    }
}

void ReExecW::buttonLAxisRight()
{
    executeAhk("laxis_right");
}

void ReExecW::buttonLAxisLeft()
{
    executeAhk("laxis_left");
}

void ReExecW::buttonLAxisUp()
{
    executeAhk("laxis_up");
}

void ReExecW::buttonLAxisDown()
{
    executeAhk("laxis_down");
}

void ReExecW::buttonRAxisRight()
{
    executeAhk("raxis_right");
}

void ReExecW::buttonRAxisLeft()
{
    executeAhk("raxis_left");
}

void ReExecW::buttonRAxisUp()
{
    executeAhk("raxis_up");
}

void ReExecW::buttonRAxisDown()
{
    executeAhk("raxis_down");
}

void ReExecW::buttonStartChanged()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("menu");
    }
    else
    {
        executeAhk("menu_button");
    }
}

void ReExecW::buttonGuideChanged()
{
    QMetaObject::invokeMethod(ui, "uiToggle");
}

void ReExecW::buttonSelectChanged()
{
    if( isUiVisible(ui) )
    {
         hideUI(ui);
         QThread::msleep(200);
         executeUi("select");
    }
    else
    {
        executeAhk("select_button");
    }
}

void ReExecW::buttonDownChanged()
{
    executeAhk("button_down");
}

void ReExecW::buttonUpChanged()
{
    executeAhk("button_up");
}

void ReExecW::buttonRightChanged()
{
    executeAhk("button_right");
}

void ReExecW::buttonLeftChanged()
{
    executeAhk("button_left");
}

void ReExecW::executeAhk(QString name)
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

void ReExecW::executeUi(QString name)
{
    PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
    STARTUPINFOA StartupInfo; //This is an [in] parameter

    ZeroMemory( &StartupInfo, sizeof(StartupInfo) );
    StartupInfo.cb = sizeof(StartupInfo);
    ZeroMemory( &ProcessInfo, sizeof(ProcessInfo) );

    QString command = "\"C:\\Program Files\\AutoHotkey\\AutoHotkey.exe\" AHK\\button_ui.ahk ";
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
