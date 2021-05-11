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
    Sleep, 100

    Run, %ReboundPath%\..\..\AccJoon\release\AccJoon.exe "D" "4.1.4.2.4" 0 0 "Header Control", ,Min
    Sleep, 500

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
