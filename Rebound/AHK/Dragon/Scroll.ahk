#NoTrayIcon

arg1=%1%
arg2=%2%
wheel_speed := 0
wheeling := 1 ;always use colon
wheel_dir := 0

Send, {Esc}
sleep, 300

RegWrite, REG_SZ, HKEY_CURRENT_USER\Software\WBT\Rebound, Direction, %arg1%

if (arg1 = "down")
{
    wheel_dir := 1
    RegWrite, REG_SZ, HKEY_CURRENT_USER\Software\WBT\Rebound, Speed, %arg2%
}
else if (arg1 = "up")
{
    wheel_dir := -1
    RegWrite, REG_SZ, HKEY_CURRENT_USER\Software\WBT\Rebound, Speed, %arg2%
}
else if (arg1 = "stop")
{
  	wheeling := 0
}

if (arg2 = "one")
{
    wheel_speed := 14
}
else if (arg2 = "two")
{
    wheel_speed := 16
}
else if (arg2 = "three")
{
    wheel_speed := 20
}
else if (arg2 = "four")
{
    wheel_speed := 24
}
else if (arg2 = "five")
{
    wheel_speed := 30
}
else if (arg2 = "six")
{
    wheel_speed := 36
}
else if (arg2 = "seven")
{
    wheel_speed := 42
}
else if (arg2 = "eight")
{
    wheel_speed := 50
}
else if (arg2 = "nine")
{
    wheel_speed := 60
}
else if (arg2 = "ten")
{
    wheel_speed := 70
}
else
{
    MsgBox This command is not recognized %arg1% %arg2%.
}

WinGetPos, X, Y, Width, Height, ahk_exe firefox.exe
;height_half := Height/2

height_half = 600
width_half := Width - 100
mouse_diff := wheel_dir * wheel_speed
MouseMove, %width_half%, %height_half%
sleep, 200
MouseClick, middle
sleep, 200
MouseMove, 0, %mouse_diff%, , R
