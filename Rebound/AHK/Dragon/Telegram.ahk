arg1=%1%

if (arg1 = "one")
{
  MouseMove, 180, 100
  Sleep, 50
  Click
}
else if (arg1 = "two")
{
  MouseMove, 180, 165
  Sleep, 50
  Click
}
else if (arg1 = "three")
{
  MouseMove, 180, 230
  Sleep, 50
  Click
}
else if (arg1 = "four")
{
  MouseMove, 180, 300
  Sleep, 50
  Click
}
else if (arg1 = "five")
{
  MouseMove, 180, 365
  Sleep, 50
  Click
}
else if (arg1 = "six")
{
  MouseMove, 180, 430
  Sleep, 50
  Click
}
else if (arg1 = "seven")
{
  MouseMove, 180, 500
  Sleep, 50
  Click
}
else if (arg1 = "eight")
{
  MouseMove, 180, 560
  Sleep, 50
  Click
}
else if (arg1 = "nine")
{
  MouseMove, 180, 620
  Sleep, 50
  Click
}
else if (arg1 = "ten")
{
  MouseMove, 180, 680
  Sleep, 50
  Click
}
else if (arg1 = "eleven")
{
  MouseMove, 180, 740
  Sleep, 50
  Click
}
else if (arg1 = "twelve")
{
  MouseMove, 180, 800
  Sleep, 50
  Click
}
else if (arg1 = "thirteen")
{
  MouseMove, 180, 860
  Sleep, 50
  Click
}
else if (arg1 = "fourteen")
{
  MouseMove, 180, 920
  Sleep, 50
  Click
}
else if (arg1 = "settings")
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

}
