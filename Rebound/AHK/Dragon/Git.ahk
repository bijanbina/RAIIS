#Include Functions.ahk

arg1=%1%
EnvGet, ReboundPath, RE_PATH

if( arg1="comment" )
{
    Send, {Ctrl down}{Shift down}M{Shift up}{Ctrl Up}
}
else if( arg1="pull" )
{
    Send, {Ctrl down}p{Ctrl up}
    Sleep, 100
    Send, pull
    Sleep, 500
    Send, {Enter}
}
else if( arg1="push" )
{
    Send, {Ctrl down}p{Ctrl up}
    Sleep, 100
    Send, push
    Sleep, 500
    Send, {Enter}
}
else if( arg1="stage" )
{
    Send, {Ctrl down}p{Ctrl up}
    Sleep, 100
    Send, stage
    Sleep, 500
    Send, {Enter}
    Sleep, 500
    Send, {Ctrl down}{Shift down}M{Shift up}{Ctrl Up}
}
else if( arg1="commit" )
{
    Send, {Ctrl down}{Enter}{Ctrl Up}
}
