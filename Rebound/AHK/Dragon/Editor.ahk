#Include Functions.ahk

arg1=%1%
arg2=%2%

if ( arg1="CopyLeft" )
{
    count := re_getNum(arg2)
    Send, {Ctrl down}{Shift down}{Left %count%}{Shift up}{Ctrl up}
    Send, {Ctrl down}c{Ctrl up}
}
else if (arg1 = "CopyRight")
{
    count := re_getNum(arg2)
    Send, {Ctrl down}{Shift down}{Right %count%}{Shift up}{Ctrl up}
    Send, {Ctrl down}c{Ctrl up}
}
else if (arg1 = "CopyFromLine")
{
    count := re_getNum(arg2)
    Send, {Home}
    Send, {Shift down}{End}{Shift up}
    Send, {Ctrl down}c{Ctrl up}
    Send, {End}{Up %count%}{Enter}
    Send, {Ctrl down}v{Ctrl up}
}
else if (arg1 = "GoEndOfLine")
{
    count := re_getNum(arg2)

    if ( count>10 )
    {
        count := count - 10
        Send, {Up %count%}{End}
    }
    else
    {
        Send, {Down %count%}{End}
    }
}
