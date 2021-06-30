#NoTrayIcon

#Include Functions.ahk

arg1=%1%

if ( arg1="big" )
{
    RegRead, Direction, HKEY_CURRENT_USER\Software\WBT\Rebound, Direction
    RegRead, Speed, HKEY_CURRENT_USER\Software\WBT\Rebound, Speed
    if ( Direction!="stop" )
    {
        Send, {Escape}
        Sleep, 200
    }

    Send, ^{=}
    Send, ^{=}

    if ( Direction!="stop" )
    {
        Run Scroll.ahk %Direction% %Speed%
    }
}
else if( arg1 =="small" )
{
    RegRead, Direction, HKEY_CURRENT_USER\Software\WBT\Rebound, Direction
    RegRead, Speed, HKEY_CURRENT_USER\Software\WBT\Rebound, Speed
    if ( Direction!="stop" )
    {
        Send, {Escape}
        Sleep, 200
    }

    Send, ^{-}
    Send, ^{-}

    if ( Direction!="stop" )
    {
        Run Scroll.ahk %Direction% %Speed%
    }
}
else if( arg1="change" )
{
    Send, {LAlt Down}{LShift Down}{LShift Up}{LAlt Up}
}
else if( arg1="copy" )
{
    Send, ^c
}
else if( arg1="cut" )
{
    Send, ^x
}
else if( arg1="paste" )
{
    Send, ^v
}
