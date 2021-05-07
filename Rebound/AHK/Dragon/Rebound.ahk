;
; Window Spy
;

#NoEnv
#NoTrayIcon
#SingleInstance Ignore
EnvGet, ReboundPath, RE_PATH
SetWorkingDir, %ReboundPath%\AHK\Dragon

;MsgBox This command is AHK
Run %1% %2% %3%

return
