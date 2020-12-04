#NoTrayIcon

WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "firefox.exe")
{
  WinGetPos, X, Y, Width, Height, A
  height_half := Height/2
  width_half := Width/2
  MouseMove, %width_half%, %height_half%
  sleep, 200
  ;MsgBox, ProcessName = %width_half% %height_half% %X% %Y%
  MouseClick, left
  sleep, 100
  MouseClick, left
}
else
{
  Send, {Escape}
}
Return
