#NoTrayIcon

WinGet, WinProcessName, ProcessName, A
if ( WinProcessName="firefox.exe" )
{
  Send, {Escape}
}
else
{

}

Return
