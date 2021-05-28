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
  	WinActivate, ahk_exe clover.exe
    Sleep, 500
    Click, 400, 200
}
else if( arg1=="github" )
{
  	WinActivate, ahk_exe gitkraken.exe
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
else if( arg1=="vlc" )
{
  	WinActivate, ahk_exe vlc.exe
}
else if( arg1=="words" )
{
  	WinActivate, ahk_exe gallery.exe
}
