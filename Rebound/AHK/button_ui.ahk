#NoTrayIcon

SnapActiveWindow(winPlaceVertical, winPlaceHorizontal, winSizeHeight) {
    WinGet activeWin, ID, A
    activeMon := GetMonitorIndexFromWindow(activeWin)

    SysGet, MonitorWorkArea, MonitorWorkArea, %activeMon%

    if (winSizeHeight == "half") {
        height := (MonitorWorkAreaBottom - MonitorWorkAreaTop)/2
    } else {
        height := (MonitorWorkAreaBottom - MonitorWorkAreaTop)/3
    }

    if (winPlaceHorizontal == "left") {
        posX  := MonitorWorkAreaLeft
        width := (MonitorWorkAreaRight - MonitorWorkAreaLeft)/2
    } else if (winPlaceHorizontal == "right") {
        posX  := MonitorWorkAreaLeft + (MonitorWorkAreaRight - MonitorWorkAreaLeft)/2
        width := (MonitorWorkAreaRight - MonitorWorkAreaLeft)/2
    } else {
        posX  := MonitorWorkAreaLeft
        width := MonitorWorkAreaRight - MonitorWorkAreaLeft
    }

    if (winPlaceVertical == "bottom") {
        posY := MonitorWorkAreaBottom - height
    } else if (winPlaceVertical == "middle") {
        posY := MonitorWorkAreaTop + height
    } else {
        posY := MonitorWorkAreaTop
    }

    WinMove,A,,%posX%,%posY%,%width%,%height%
}

GetMonitorIndexFromWindow(windowHandle) {
    ; Starts with 1.
    monitorIndex := 1

    VarSetCapacity(monitorInfo, 40)
    NumPut(40, monitorInfo)

    if (monitorHandle := DllCall("MonitorFromWindow", "uint", windowHandle, "uint", 0x2))
        && DllCall("GetMonitorInfo", "uint", monitorHandle, "uint", &monitorInfo) {
        monitorLeft   := NumGet(monitorInfo,  4, "Int")
        monitorTop    := NumGet(monitorInfo,  8, "Int")
        monitorRight  := NumGet(monitorInfo, 12, "Int")
        monitorBottom := NumGet(monitorInfo, 16, "Int")
        workLeft      := NumGet(monitorInfo, 20, "Int")
        workTop       := NumGet(monitorInfo, 24, "Int")
        workRight     := NumGet(monitorInfo, 28, "Int")
        workBottom    := NumGet(monitorInfo, 32, "Int")
        isPrimary     := NumGet(monitorInfo, 36, "Int") & 1

        SysGet, monitorCount, MonitorCount

        Loop, %monitorCount% {
            SysGet, tempMon, Monitor, %A_Index%

            ; Compare location to determine the monitor index.
            if ((monitorLeft = tempMonLeft) and (monitorTop = tempMonTop)
                and (monitorRight = tempMonRight) and (monitorBottom = tempMonBottom)) {
                monitorIndex := A_Index
                break
            }
        }
    }

    return %monitorIndex%
}

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
  Send, {Ctrl down}{Alt down}{Up}{Alt up}{Ctrl up}
}
else if (input = "button_right")
{
  Send, {Ctrl down}{Alt down}{Down}{Alt up}{Ctrl up}
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
