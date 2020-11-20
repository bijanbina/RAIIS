#NoTrayIcon

WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "firefox.exe")
{
  Send, ^l
}
else if (WinProcessName = "Explorer.EXE")
{
  Send, ^+{Tab}
}
else
{
  MsgBox, ProcessName = %WinProcessName%
}
Return
