WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "firefox.exe")
{
  Send, ^t
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
