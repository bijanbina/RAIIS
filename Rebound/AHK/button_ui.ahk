#NoTrayIcon
#Include %A_ScriptDir%\win_monitor.ahk

input = %1%
if (input = "a")
{
  WinActivate, ahk_exe Spotify.exe
}
else if (input = "b")
{
  MsgBox, b
}
else if (input = "x")
{
  Send, !{F4}
}
else if (input = "y")
{
  WinActivate, ahk_exe firefox.exe
}
else if (input = "button_select")
{
  Send, {Volume_Mute}
}
else if (input = "button_left")
{
  Send, {Ctrl down}{Shift down}{Alt down}1{Shift up}{Alt Up}{Ctrl Up}
}
else if (input = "button_up")
{
  Send, {Ctrl down}{Shift down}{Alt down}2{Shift up}{Alt Up}{Ctrl Up}
}
else if (input = "button_down")
{
  Send, {Ctrl down}{Shift down}{Alt down}3{Shift up}{Alt Up}{Ctrl Up}
}
else if (input = "button_right")
{
  Send, {Ctrl down}{Shift down}{Alt down}4{Shift up}{Alt Up}{Ctrl Up}
}
else if (input = "laxis_left")
{
  Send, {Win down}{Alt down}{Down}{Alt up}{Ctrl up}
}
else if (input = "laxis_right")
{
  Send, {Win down}{Alt down}{Down}{Alt up}{Ctrl up}
}
else if (input = "raxis_right")
{
  ; Send, {LWin down}{Right}{LWin up}

  WinGet activeWin, ID, A
  activeMon := GetMonitorIndexFromWindow(activeWin)

  SysGet, MonitorWorkArea, MonitorWorkArea, %activeMon%
  height := (MonitorWorkAreaBottom - MonitorWorkAreaTop)
  posX  := MonitorWorkAreaLeft + (MonitorWorkAreaRight - MonitorWorkAreaLeft)/2
  width := (MonitorWorkAreaRight - MonitorWorkAreaLeft)/2
  posY := MonitorWorkAreaTop
  WinMove,A,,%posX%,%posY%,%width%,%height%
  ; MsgBox, hello %activeMon%
}
else if (input = "raxis_left")
{
  ; Send, {LWin down}{Right}{LWin up}

  WinGet activeWin, ID, A
  activeMon := GetMonitorIndexFromWindow(activeWin)

  SysGet, MonitorWorkArea, MonitorWorkArea, %activeMon%
  height := (MonitorWorkAreaBottom - MonitorWorkAreaTop)
  posX  := MonitorWorkAreaLeft
  width := (MonitorWorkAreaRight - MonitorWorkAreaLeft)/2
  posY := MonitorWorkAreaTop
  WinMove,A,,%posX%,%posY%,%width%,%height%
    ; MsgBox, hello %input%
}
else if (input = "raxis_up")
{
  ; Send, {LWin down}{Right}{LWin up}

  WinGet activeWin, ID, A
  activeMon := GetMonitorIndexFromWindow(activeWin)

  SysGet, MonitorWorkArea, MonitorWorkArea, %activeMon%
  height := (MonitorWorkAreaBottom - MonitorWorkAreaTop)
  posX  := MonitorWorkAreaLeft
  width := (MonitorWorkAreaRight - MonitorWorkAreaLeft)
  posY := MonitorWorkAreaTop
  WinMove,A,,%posX%,%posY%,%width%,%height%
  ; MsgBox, hello %activeMon%
}
else if (input = "raxis_down")
{
  ; Send, {LWin down}{Right}{LWin up}

  WinGet activeWin, ID, A
  activeMon := GetMonitorIndexFromWindow(activeWin)

  if( activeMon = "1" )
  {
    activeMon := "2"
  }
  else
  {
    activeMon := "1"
  }

  SysGet, MonitorWorkArea, MonitorWorkArea, %activeMon%
  height := (MonitorWorkAreaBottom - MonitorWorkAreaTop)
  posX  := MonitorWorkAreaLeft
  width := (MonitorWorkAreaRight - MonitorWorkAreaLeft)
  posY := MonitorWorkAreaTop
  WinMove,A,,%posX%,%posY%,%width%,%height%
  ; MsgBox, hello %activeMon%
}
else
{
  MsgBox, hello %input%
}
Return
