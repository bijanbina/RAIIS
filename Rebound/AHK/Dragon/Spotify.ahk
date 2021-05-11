#Include Functions.ahk

arg1=%1%
EnvGet, ReboundPath, RE_PATH

WinGet, current_ID, ID, A
WinActivate, ahk_exe Spotify.exe
Sleep, 200

if (arg1 = "like") ; add to liked songs
{
    Run, %ReboundPath%\..\..\AccJoon\release\AccJoon.exe "L" "4.1.2.1.1.1.2.1.1.3.1.1.4", ,Min
}
else if (arg1 = "ads")
{
    Click, 923, 171
}
else if (arg1 = "repeat")
{
    Click, 500, 30
    Sleep, 200
    Click, 500, 30
    Send, {LCtrl Down}r{LCtrl Up}
    Sleep, 500
    ;WinMinimize, A
}
else if (arg1 = "songs") ; play liked songs
{
    Run, %ReboundPath%\..\..\AccJoon\release\AccJoon.exe "D" "4.1.2.1.1.1.2.1.1.2.2.2.2", ,Min
}
else
{
    count := re_getNum(arg1)
    acc_path = 4.1.2.1.1.1.2.1.1.2.2.4.2.1.1.1.%count%.1.1
		; MsgBox, %acc_path%
    Run, %ReboundPath%\..\..\AccJoon\release\AccJoon.exe "D" "%acc_path%", ,Min
}

Sleep, 200
WinActivate ahk_id %current_ID%
