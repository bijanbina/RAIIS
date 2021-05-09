#Include Functions.ahk

arg1=%1%
arg2=%2%

if ( arg1="ApplicationSwitcher" )
{
    if( arg2="atom" )
    {
        WinActivate, ahk_exe atom.exe
    }
    else if( arg2="BitTorrent" )
    {
        WinActivate, ahk_exe BitTorrent.exe
    }
    else if( arg2="spy" )
    {
        ;WinActivate, ahk_exe BitTorrent.exe
    }
    else if( arg2="VLC" )
    {
      	WinActivate, ahk_exe vlc.exe
    }
    else if( arg2="delta" )
    {
      	;Send, {Ctrl down}{Shift down}{Alt down}4{Shift up}{Alt Up}{Ctrl Up}
    }
    else if( arg2="cute" )
    {
      	WinActivate, ahk_exe qtcreator.exe
    }
    else if( arg2="file" )
    {
      	;WinActivate, ahk_exe explorer.exe
      	WinActivate, ahk_exe clover.exe
    }
    else if( arg2="telegram" )
    {
      	WinActivate, ahk_exe Telegram.exe
    }
    else if( arg2="spotify" )
    {
      	WinActivate, ahk_exe Spotify.exe
    }
}
else if( arg1="WorkspaceSwitcher" )
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
