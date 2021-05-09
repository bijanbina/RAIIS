arg1=%1%

if (arg1 = "headers")
{
    Send, !x ;Alt+x
    Sleep, 50
    Send, headers
    Sleep, 50
    Send, {Right}
    ;Send, {Down}
		;MsgBox, This command is not r hello %0%
}
else if (arg1 = "sources")
{
    Send, !x ;Alt+x
    Sleep, 50
    Send, sources
    Sleep, 50
    Send, {Right}
    ;Send, {Down}
}
else if (arg1 = "qml")
{
    Send, !x ;Alt+x
    Sleep, 50
    Send, qml
    Sleep, 50
    Send, {Right 2}
    ;WinActivate, ahk_exe BitTorrent.exe
}
else if (arg1 = "one")
{
    Run, O:\Projects\AccJoon\release\AccJoon.exe "AD" "4.1.3.2.1.2.2.1.1" "0" "0" "Headers", ,Min
}
else if (arg1 = "delta")
{
  	Send, {Ctrl down}{Shift down}{Alt down}4{Shift up}{Alt Up}{Ctrl Up}
}
else if (arg1 = "cute")
{
  	WinActivate, ahk_exe qtcreator.exe
}
else if (arg1 = "file")
{
  	WinActivate, ahk_exe clover.exe
}
else
{

}
;MsgBox, This command is not r hello %1%
;Send, {LWin Down}{Ctrl down}z{Ctrl Up}{LWin Up}
