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
        URL := "https://www.amazon.com"
    }
    else if( arg2=="github" )
    {
        URL := "https://github.com/bijanbina"
    }
    else if( arg2=="bijan" )
    {
        URL := "http://bijan.binaee.com"
    }
    else if( arg2=="corona" )
    {
        URL := "https://www.worldometers.info/coronavirus"
    }
    else if( arg2=="thesaurus" )
    {
        URL := "https://www.thesaurus.com"
    }
    else if( arg2=="translate" )
    {
        URL := "https://translate.google.com"
    }

    Send, ^t
    Send, %URL%
    Send, {Enter}
}
if ( arg1=="PdfSetPage" )
{
    RegRead, Direction, HKEY_CURRENT_USER\Software\WBT\Rebound, Direction
    RegRead, Speed, HKEY_CURRENT_USER\Software\WBT\Rebound, Speed
    Send, {Escape}
    Sleep, 50

    Send, ^!g
    Sleep, 50
    arg2=%2%
    Send, %arg2%
    Sleep, 100
    Send, {Enter}
    Sleep, 100
    Click
    Sleep, 100

    if ( Direction!="stop" )
    {
        Run Scroll.ahk %Direction% %Speed%
    }
}
else if( arg1=="duplicate" )
{
    Send, ^!g
    Sleep, 100
    Send, ^c
    Sleep, 100
    page = %clipboard%
    Send, ^l
    Sleep, 100
    Send, ^c
    Sleep, 100
    Send, ^n
    Sleep, 400
    Send, {LWin Down}{LShift Down}{Left}{LShift Up}{LWin Up}
    Sleep, 100
    Send, ^v
    Sleep, 50
    Send, {Enter}
    Sleep, 500
    Send, ^!g
    Sleep, 100
    Send, %page%
    Sleep, 100
    Send, {Enter}
    Send, ^{= 5}
}
