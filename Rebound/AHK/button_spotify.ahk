#NoTrayIcon
#Include %A_ScriptDir%\win_monitor.ahk

input = %1%
if (input = "x")
{
  Send, {Media_Play_Pause}
}
else if (input = "y")
{
  WinActivate, ahk_exe firefox.exe
}
else if (input = "a")
{
  WinActivate, ahk_exe Spotify.exe
}
else if (input = "b")
{
  Send, {Media_Stop}
}
else if (input = "l1")
{
  Send, {Media_Prev}
}
else if (input = "l2")
{
  Send, {Volume_Down}
}
else if (input = "r1")
{
  Send, {Media_Next}
}
else if (input = "r2")
{
  Send, {Volume_Up}
}
else if (input = "button_select")
{
  Send, {Volume_Mute}
}
else if (input = "button_left")
{
  Send, {Ctrl down}{Alt down}{1}{Alt up}{Ctrl up}
}
else if (input = "button_up")
{
  Send, {Ctrl down}{Alt down}{2}{Alt up}{Ctrl up}
}
else if (input = "button_down")
{
  Send, {Ctrl down}{Alt down}{3}{Alt up}{Ctrl up}
}
else if (input = "button_right")
{
  Send, {Ctrl down}{Alt down}{4}{Alt up}{Ctrl up}
}
else if (input = "laxis_up")
{
  Send, {Volume_Down 20}
}
else if (input = "laxis_right")
{
  Send, {Volume_Down 15}
}
else if (input = "laxis_left")
{
  Send, {Volume_Down 10}
}
else if (input = "laxis_down")
{
  Send, {Volume_Down 5}
}
else if (input = "raxis_up")
{
  Send, {Volume_Up 20}
}
else if (input = "raxis_right")
{
  Send, {Volume_Up 15}
}
else if (input = "raxis_left")
{
  Send, {Volume_Up 10}
}
else if (input = "raxis_down")
{
  Send, {Volume_Up 5}
}
else
{
  MsgBox, hello %input%
}
Return
