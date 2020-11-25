#NoTrayIcon

WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "Spotify.exe")
{
  Send, ^{Right}
}
else if (WinProcessName = "firefox.exe")
{
  Send, ^{Tab}
}
else if (WinProcessName = "Explorer.EXE")
{
  Send, !{Up}
}
else if (WinProcessName = "atom.exe")
{
  Send, ^{PgDown}
}
else
{
  ; MsgBox, ProcessName = %WinProcessName%
  MsgBox, %1%, %2%
}
Return
