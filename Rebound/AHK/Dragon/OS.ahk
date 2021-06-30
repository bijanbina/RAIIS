#Include Functions.ahk

arg1=%1%
arg2=%2%
EnvGet, ReboundPath, RE_PATH

if( arg1="WorkspaceSwitcher" )
{
    if( arg2="work" )
    {
        Send, {LWin Down}{Ctrl down}z{Ctrl Up}{LWin Up}
    }
    else if( arg2="arch" )
    {
        Send, {Ctrl down}{Shift down}{Alt down}1{Shift up}{Alt Up}{Ctrl Up}
    }
    else if( arg2="bravo" )
    {
      	Send, {Ctrl down}{Shift down}{Alt down}2{Shift up}{Alt Up}{Ctrl Up}
    }
    else if( arg2="catalina" )
    {
      	Send, {Ctrl down}{Shift down}{Alt down}3{Shift up}{Alt Up}{Ctrl Up}
    }
    else if( arg2="delta" )
    {
      	Send, {Ctrl down}{Shift down}{Alt down}4{Shift up}{Alt Up}{Ctrl Up}
    }
}
else if( arg1="FoxClose" )
{
    count := re_getNum(arg2)
    Send, {Ctrl down}{w %count%}{Ctrl up}
}
else if( arg1="PdfSetPage" )
{
    Send, {Ctrl down}g{Ctrl up}
    Send, %arg2%
    Send, {Enter}
}
else if( arg1="OpenSound" )
{
    Run, C:\Windows\System32\mmsys.cpl sounds,/e`
    Sleep, 1000
    Click, 100, 50
    Sleep, 500

    Run, %ReboundPath%\..\..\AccJoon\release\AccJoon.exe "D" "4.1.4.2.4" 0 0 "Header Control", ,Min
    Sleep, 1000

    MouseMove, 135, 50
    Click

    Sleep, 500
    ControlGet, AgcValue, Checked,, AGC, Microphone
    if ErrorLevel
        MsgBox There was a problem.
    else if (AgcValue = 1)
    {
        ;MsgBox Tab #%AgcValue% is active.
    }
    if (AgcValue = 0)
    {
        Send, {Space}
    }
    Sleep, 500
    Send, {Enter}
    Sleep, 500
    Send, {Enter}
}
else if( arg1="Numbers" )
{
    Send, %arg2%
}
else if( arg1="PutLeft" )
{
    WinGetClass, vWinClass, A
    if (vWinClass = "CabinetWClass")
    {
    	WinActivate, ahk_exe clover.exe
      Sleep, 200
      Send, {LWin Down}{LShift Down}{Left}{LShift Up}{LWin Up}
    }
    else
    {
      Send, {LWin Down}{LShift Down}{Left}{LShift Up}{LWin Up}
    }
}
else if( arg1="PutRight" )
{
    WinGetClass, vWinClass, A
    if (vWinClass = "CabinetWClass")
    {
    	WinActivate, ahk_exe clover.exe
      Sleep, 200
      Send, {LWin Down}{LShift Down}{Right}{LShift Up}{LWin Up}
    }
    else
    {
      Send, {LWin Down}{LShift Down}{Right}{LShift Up}{LWin Up}
    }
}
else if( arg1="WinLeft" )
{
    Send, {LWin Down}{Left}{LWin Up}
}
else if( arg1="WinRight" )
{
    Send, {LWin Down}{Right}{LWin Up}
}
else if( arg1="Explorer" )
{
    Run, %ReboundPath%\..\..\AccJoon\Tools\AccExplorer32.exe
    Sleep, 1000
    Click, 70, 60
    Sleep, 1000
    MouseMove, 260, 60
}
else if( arg1=="vpn" )
{
    if( arg2=="off" )
    {
        Run, C:\Windows\System32\rasdial.exe /DISCONNECT
    }
    else if( arg2=="on" )
    {
        Run, C:\Windows\System32\rasdial.exe "MK2" km93057 48868
    }
}
