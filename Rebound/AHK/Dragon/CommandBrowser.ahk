#Include Functions.ahk
#Include FTP.ahk

CoordMode, Mouse, Relative
arg1=%1%

if ( arg1="export" )
{
    EnvGet, ReboundPath, RE_PATH
    Run, %ReboundPath%\..\..\AccJoon\release\AccJoon.exe "L" "4.33.4.1", ,Min
    Sleep, 700 ;wait for run to finish
    Click, 400, 200

    Send, {Home}
    Sleep, 400
    Send, {Shift down}{End}{Shift up}
    Sleep, 400
    Send, {Ctrl down}{x}{Ctrl up}
    Sleep, 400
    Send, %ReboundPath%\AHK\Dragon\Commands.dat
    Sleep, 1000
    Send, {Enter}
    Sleep, 500
    Send, {Enter}
}
else if ( arg1="import" )
{
    Send, {Ctrl down}{i}{Ctrl up}
    Sleep, 500
    EnvGet, ReboundPath, RE_PATH
    Send, %ReboundPath%\AHK\Dragon\Commands.dat
    Sleep, 1000
    Send, {Enter}
    Sleep, 500
    Send, {Enter}
    Sleep, 500
    Send, {Right}
    Sleep, 500
    Send, {Enter}
    Sleep, 1800
    Send, {Enter}
}
else if ( arg1="upload" )
{
    EnvGet, ReboundPath, RE_PATH
    FilePath = %ReboundPath%\AHK\Dragon\Commands.dat
    hFTP := FTP.Open("AHK-FTP")
    hSession := FTP.Connect(hFTP, "ftp.drivehq.com", 21, "bijanbina", "betocheA4")
    ; Automatically always overwrite
    FTP.PutFile(hSession, FilePath, "Commands.dat")
    FTP.Disconnect(hSession)
    FTP.Close(hFTP)

    SplashTextOn, 200 , 20, Upload Finished, Upload Finished
    Sleep 2000
}
else if ( arg1="download" )
{
    EnvGet, ReboundPath, RE_PATH
    FilePath = %ReboundPath%\AHK\Dragon\Commands.dat
    hFTP := FTP.Open("AHK-FTP")
    hSession := FTP.Connect(hFTP, "ftp.drivehq.com", 21, "bijanbina", "betocheA4")
    ; OverWrite=1
    FTP.GetFile(hSession, "Commands.dat", FilePath, 1)
    FTP.Disconnect(hSession)
    FTP.Close(hFTP)

    SplashTextOn, 200 , 20, Download Completed, Download Completed
    Sleep 2000
}
else if ( arg1="editor" )
{
    Send, {Enter}
    Sleep, 500
    Send, {Alt down}{m}{Alt up}
    Sleep, 500
    MouseMove, 130, 125
    Sleep, 500
    Click, 2
}
else
{
    count := re_getNum(arg1)

    if( count>0 )
    {
        position_y := count*50 + 200
        ; MsgBox, This command is not r hello %position_y%
        Click, 400, %position_y%
    }
    else
    {
        Click, 400, 200
    }
}
