WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "firefox.exe")
{
  Send, ^l
}
else
{
  Send, #{Right}
}
Return
