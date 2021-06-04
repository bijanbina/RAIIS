#Include Functions.ahk

arg1=%1%

if ( arg1=="not" ) ;not now
{
    ; CoordMode, Mouse, Relative
    MouseGetPos, FirstX, FirstY
    WinGetPos,  ,  ,  SpotifyWinW, SpotifyWinH, A
    TargetY := 190
    TargetX := SpotifyWinW - 100
    MouseMove, %TargetX%, %TargetY%
    Sleep, 50
    Click
    Sleep, 50
    MouseMove, %FirstX%, %FirstY%
}
else if( arg1=="open" )
{
    arg2=%2%

    if( arg2=="batman" )
    {
        URL := "https://trello.com/b/icTfBMEH/project-batman"
    }
    else if( arg2=="amazon" )
    {
        URL := "https://www.amazon.com/"
    }
    ;Send, {LCtrl Down}r{LCtrl Up}

    Send, ^t
    Send, %URL%
    Send, {Enter}
}
