#NoTrayIcon

input = %1%
if (input = "a")
{
  WinActivate, ahk_exe Spotify.exe
}
else if (input = "b")
{
  MsgBox, b
}
else if (input = "x")
{
  Send, !{F4}
}
else if (input = "y")
{
  WinActivate, ahk_exe firefox.exe
}
else if (input = "l1")
{
  WinGetPos, X, Y, Width, Height, A
  height_half := Height/2
  width_half := Width/2
  MouseMove, %width_half%, %height_half%
  sleep, 200
  MouseClick, left
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
else if (input = "laxis_left")
{
  Send, {Win down}{Alt down}{Down}{Alt up}{Ctrl up}
}
else if (input = "laxis_right")
{
  Send, {Win down}{Alt down}{Down}{Alt up}{Ctrl up}
}
else
{
  MsgBox, hello %input%
}
Return
