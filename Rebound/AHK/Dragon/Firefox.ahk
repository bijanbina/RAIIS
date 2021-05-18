#Include Functions.ahk

arg1=%1%

if ( arg1="not" )
{
  CoordMode, Mouse, Relative
  SpotifyWinHeight = 1050
  ;Click, 135, 825
  WinGetPos,  ,  ,  SpotifyWinW, SpotifyWinH, A
  TargetY := 100
  TargetX := SpotifyWinW - 50
  MouseMove, %TargetX%, %TargetY%
  Sleep, 50
  ;Click
}
else if ( arg1="router" )
{
    Run, "C:\Softwares\AudioRouter\Audio.exe", ,
}
