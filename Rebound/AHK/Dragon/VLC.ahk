arg1=%1%
arg2=%2%

;MsgBox, This command is not r hello %arg2%

if (arg1 = "1")
{
    Send, {Ctrl down}t{Ctrl up}
    Sleep, 100
    Send, {Right 3}{Delete 3}
    Sleep, 100
    Send, %arg2%
    Sleep, 100
    Send, {Enter}
}
