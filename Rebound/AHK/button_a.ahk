#NoTrayIcon

WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "Spotify.exe")
{
  Send, ^{Right}
}
else if (WinProcessName = "firefox.exe")
{
  Send, ^t
}
else if (WinProcessName = "Explorer.EXE")
{
  Send, {Enter}
}
else if (WinProcessName = "atom.exe")
{
  Send, ^{PgDn}
}
else
{
  MsgBox, ProcessName = %WinProcessName%
}
Return
