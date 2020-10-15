WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "firefox.exe")
{
  Send, ^{F4}
}
else if (WinProcessName = "Explorer.EXE")
{
  Send, ^{Tab}
}
else if (WinProcessName = "atom.exe")
{
  Send, ^w
}
else
{
  MsgBox, ProcessName = %WinProcessName%
}
Return
