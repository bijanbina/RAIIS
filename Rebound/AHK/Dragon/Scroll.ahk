#NoTrayIcon

#Include Functions.ahk

arg1=%1%
arg2=%2%
wheel_speed := 0
wheeling := 1 ;always use colon
wheel_dir := 0
change_gear := 0

RegRead, Direction, HKEY_CURRENT_USER\Software\WBT\Rebound, Direction
RegRead, Speed, HKEY_CURRENT_USER\Software\WBT\Rebound, Speed
if ( Direction!="stop" )
{
    change_gear := re_getWheelSpeed(Speed)
}

RegWrite, REG_SZ, HKEY_CURRENT_USER\Software\WBT\Rebound, Direction, %arg1%

if( arg1=="down" )
{
    wheel_dir := 1
    RegWrite, REG_SZ, HKEY_CURRENT_USER\Software\WBT\Rebound, Speed, %arg2%
}
else if( arg1=="up" )
{
    wheel_dir := -1
    RegWrite, REG_SZ, HKEY_CURRENT_USER\Software\WBT\Rebound, Speed, %arg2%
}
else if( arg1=="stop" )
{
  	wheeling := 0
}

wheel_speed := re_getWheelSpeed(arg2)
if( wheel_speed==-1 )
{
    MsgBox This command is not recognized %arg1% %arg2%.
}

WinGetPos, X, Y, Width, Height, ahk_exe firefox.exe
;height_half := Height/2

height_half  = 600
width_ofset := Width - 50
mouse_diff  := wheel_dir * wheel_speed

if( change_gear==0 )
{
    Send, {Escape}
    Sleep, 200
    MouseMove, %width_ofset%, %height_half%
    sleep, 200
    MouseClick, middle
    sleep, 200
    MouseMove, 0, %mouse_diff%, , R
}
else
{
    c_dir := 0
    if( Direction=="down" )
    {
        c_dir := 1
    }
    else if( Direction=="up" )
    {
        c_dir := -1
    }

    mouse_last := c_dir * change_gear
    mouse_diff := mouse_diff-mouse_last

    MouseMove, 0, %mouse_diff%, , R
}
