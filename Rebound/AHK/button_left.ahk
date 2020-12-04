#NoTrayIcon

WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "Spotify.exe")
{
  Send, ^{Left}
}
else if (WinProcessName = "firefox.exe")
{
  Send, {Left}
}
else if (WinProcessName = "Explorer.EXE")
{
  Send, !{Up}
}
else if (WinProcessName = "atom.exe")
{
  Send, ^{PgUp}
}
else if (WinProcessName = "Telegram.exe")
{
  Send, ^{PgUp}
}
else
{
  MsgBox, ProcessName = %WinProcessName%
}
Return
