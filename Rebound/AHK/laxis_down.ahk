#NoTrayIcon

WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "firefox.exe")
{
  WinGetPos, X, Y, Width, Height, ahk_exe firefox.exe
  ;height_half := Height/2
  height_half = 600
  width_half := Width - 100
  MouseMove, %width_half%, %height_half%
  sleep, 200
  MouseClick, middle
  sleep, 200
  MouseMove, 0, 14, , R
}
else
{
  Send, #+{Left}
}
Return
