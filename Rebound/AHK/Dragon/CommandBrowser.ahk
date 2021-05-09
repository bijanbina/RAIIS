CoordMode, Mouse, Relative
arg1=%1%

if (arg1 = "1")
{
    EnvGet, ReboundPath, RE_PATH
    Run, %ReboundPath%\release\AccJoon.exe "L" "4.33.4.1", ,Min
    Sleep, 100
}

if (arg1 = "one")
{
    Click, 400, 250
}
else if (arg1 = "two")
{
    Click, 400, 300
}
else if (arg1 = "three")
{
    Click, 400, 350
}
else if (arg1 = "four")
{
    Click, 400, 400
}
else if (arg1 = "five")
{
    Click, 400, 450
}
else if (arg1 = "six")
{
    Click, 400, 500
}
else if (arg1 = "seven")
{
    Click, 400, 550
}
else if (arg1 = "eight")
{
    Click, 400, 600
}
else if (arg1 = "nine")
{
    Click, 400, 650
}
else if (arg1 = "ten")
{
    Click, 400, 750
}
else
{
    Click, 400, 200
}
