#NoTrayIcon

WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "Spotify.exe")
{
  Send, ^{Down}
}
else if (WinProcessName = "firefox.exe")
{
  Send, d
}
else if (WinProcessName = "Explorer.EXE")
{
  Send, !{Down}
}
else if (WinProcessName = "atom.exe")
{
  Send, ^{PgDn}
}
else if (WinProcessName = "Telegram.exe")
{
  Send, {PgDn}
}
else if (WinProcessName = "qtcreator.exe")
{
  Send, {PgDn}
}
else
{
  MsgBox, ProcessName = %WinProcessName%
}
Return
