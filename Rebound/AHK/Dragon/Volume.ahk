#Include Functions.ahk

#NoTrayIcon
arg1=%1%
val1=0
if (arg1 = "lower")
{
    Send, {Volume_Down}
    sleep, 200
    Send, {Volume_Down}
    sleep, 200
    Send, {Volume_Down}
    sleep, 200
    Send, {Volume_Down}
}
else if (arg1 = "higher")
{
    Send, {Volume_Up}
    sleep, 200
    Send, {Volume_Up}
    sleep, 200
    Send, {Volume_Up}
    sleep, 200
    Send, {Volume_Up}
}
else
{
    count := re_getNum(arg1)

    val1 := count*10
  	SoundSet, %val1%
}
