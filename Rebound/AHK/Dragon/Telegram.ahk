#Include Functions.ahk

arg1=%1%

if (arg1="settings")
{
  MouseMove, 20, 50
  Sleep, 50
  Click
}
else if (arg1="search")
{
  MouseMove, 100, 50
  Sleep, 50
  Click
}
else if (arg1="contacts")
{
  MouseMove, 180, 430
  Sleep, 50
  Click
}
else if (arg1="chat")
{
  MouseMove, 600, 430
  Sleep, 50
  Click
}
else if (arg1="voice")
{
    TelegramHeight = 1050
    TelegramWidth  = 1050
    ;Click, 135, 825
    WinGetPos,  ,  ,  TelegramWidth, TelegramHeight, A
    TelegramHeightA := TelegramHeight - 25
    TelegramWidthA := TelegramWidth - 25
    TelegramHeightB := TelegramHeight - 200

    MouseMove, %TelegramWidthA%, %TelegramHeightA%
    Sleep, 100
    Click down
    Sleep, 500
    TelegramHeightB := TelegramHeight - 100
    MouseMove, %TelegramWidthA%, %TelegramHeightB%
    Sleep, 100
    TelegramHeightB := TelegramHeightB - 50
    MouseMove, %TelegramWidthA%, %TelegramHeightB%
    Sleep, 100
    TelegramHeightB := TelegramHeightB - 50
    MouseMove, %TelegramWidthA%, %TelegramHeightB%
    Sleep, 500
    Click up
}
else if (arg1="dive")
{
  send, {Wheeldown 6}
}
else if (arg1="sky")
{
  send, {Wheelup 6}
}
else if (arg1="bottom")
{
  TelegramHeight = 1050
  TelegramWidth  = 1050
  ;Click, 135, 825
  WinGetPos,  ,  ,  TelegramWidth, TelegramHeight, A
  TelegramHeightc := TelegramHeight - 80
  TelegramWidthc := TelegramWidth - 40

  MouseMove, %TelegramWidthc%, %TelegramHeightc%
}
else
{
    count := re_getNum(arg1)
    position_y := count*65 + 30

    MouseMove, 180, %position_y%
    Sleep, 50
    Click
}
