WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "firefox.exe")
{
  Send, ^l
}
else
{
  WinGet MX, MinMax, A
  if (MX)
  {
    WinRestore A
  }
  else
  {
    WinMaximize A
  }
}
Return
