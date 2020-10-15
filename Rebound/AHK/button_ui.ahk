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
else if (input = "select")
{
  Send, {Volume_Mute}
}
else
{
  MsgBox, hello %input%
}
Return
