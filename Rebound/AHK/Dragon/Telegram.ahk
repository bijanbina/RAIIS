#Include Functions.ahk

arg1=%1%

if (arg1 = "settings")
{
  MouseMove, 20, 50
  Sleep, 50
  Click
}
else if (arg1 = "search")
{
  MouseMove, 100, 50
  Sleep, 50
  Click
}
else if (arg1 = "contacts")
{
  MouseMove, 180, 430
  Sleep, 50
  Click
}
else if (arg1 = "chat")
{
  MouseMove, 600, 430
  Sleep, 50
  Click
}
else if (arg1 = "voice")
{
    TelegramHeight = 1050
    TelegramWidth  = 1050
    ;Click, 135, 825
    WinGetPos,  ,  ,  TelegramWidth, TelegramHeight, A
    TelegramHeightc := TelegramHeight - 25
    TelegramWidthc := TelegramWidth - 25

    MouseMove, %TelegramWidthc%, %TelegramHeightc%
  	Send % "{Click " . ( GetKeyState("LButton") ? "Up}" : "Down}" )
}
else if (arg1 = "voice")
{
  send, {Wheeldown 6}
}
else if (arg1 = "dive")
{
  send, {Wheeldown 6}
}
else if (arg1 = "sky")
{
  send, {Wheelup 6}
}
else if (arg1 = "bottom")
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
