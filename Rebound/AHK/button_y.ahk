#NoTrayIcon

WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "firefox.exe")
{
  Send, ^t
}
else if (WinProcessName = "Explorer.EXE")
{
  Send, ^+{Tab}
}
else if (WinProcessName = "Spotify.exe")
{
  Send, ^r
}
else
{
  MsgBox, ProcessName = %WinProcessName%
}
Return
