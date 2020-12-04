#NoTrayIcon

WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "Spotify.exe")
{
  Send, ^{Right}
}
else if (WinProcessName = "firefox.exe")
{
  Send, {Right}
}
else if (WinProcessName = "Explorer.EXE")
{
  Send, !{Up}
}
else if (WinProcessName = "atom.exe")
{
  Send, ^{PgDn}
}
else if (WinProcessName = "Telegram.exe")
{
  Send, ^{PgDn}
}
else
{
  ; MsgBox, ProcessName = %WinProcessName%
  MsgBox, %1%, %2%
}
Return
