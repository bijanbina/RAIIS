#NoTrayIcon

WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "Spotify.exe")
{
  Send, ^{Up}
}
else if (WinProcessName = "firefox.exe")
{
  Send, u
}
else if (WinProcessName = "Explorer.EXE")
{
  Send, !{Up}
}
else if (WinProcessName = "atom.exe")
{
  Send, {PgUp}
}
else if (WinProcessName = "Telegram.exe")
{
  Send, {PgUp}
}
else if (WinProcessName = "qtcreator.exe")
{
  Send, {PgUp}
}
else if (WinProcessName = "gallery.exe")
{
  Send, {Up}
}
else
{
  MsgBox, ProcessName = %WinProcessName%
}
Return
