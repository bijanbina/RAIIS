arg1=%1%

if( arg1=="atom" )
{
    WinActivate, ahk_exe atom.exe
}
else if( arg1=="torrent" )
{
    WinActivate, ahk_exe BitTorrent.exe
}
else if( arg1=="editor" )
{
    WinActivate, ahk_exe atom.exe
}
else if( arg1=="delta" )
{
  	;Send, {Ctrl down}{Shift down}{Alt down}4{Shift up}{Alt Up}{Ctrl Up}
}
else if( arg1=="cute" )
{
  	WinActivate, ahk_exe qtcreator.exe
}
else if( arg1=="file" )
{
  	;WinActivate, ahk_exe explorer.exe
  	WinActivate, ahk_exe clover.exe
}
else if( arg1=="telegram" )
{
  	WinActivate, ahk_exe Telegram.exe
}
else if( arg1=="spotify" )
{
  	WinActivate, ahk_exe Spotify.exe
}
else if( arg1=="spy" )
{
    ;WinActivate, ahk_exe BitTorrent.exe
}
else if( arg1=="VLC" )
{
  	WinActivate, ahk_exe vlc.exe
}
