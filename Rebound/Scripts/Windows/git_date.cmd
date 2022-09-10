ECHO OFF

set mydate=%date:~7,2%
set day=%mydate%
set mydate=%date:~4,2%
set mon=%mydate%
set mydate=%date:~10,4%
set yer=%mydate%

reg add HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\W32Time\Parameters /f /v Type /t REG_SZ /d NoSync
net stop w32time 
reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\DateTime\Servers /f /v 1 /t REG_SZ /d 1
reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\DateTime\Servers /f /v 2 /t REG_SZ /d 2
:loop
SET /P D=Enter day:
if %D%==q (
	echo
	reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\DateTime\Servers /f /v 1 /t REG_SZ /d time.windows.com
	reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\DateTime\Servers /f /v 2 /t REG_SZ /d time.nist.gov
	call :delay50
	reg add HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\W32Time\Parameters /f /v Type /t REG_SZ /d NTP
	call :delay50
	net start w32time
	::w32tm /query /peers
	w32tm /resync /nowait
	goto end
	)
if %D% LEQ %day% (
	call :ChangeDay
	)
if %D% GTR %day% if %mon% GTR 01 (
	call :ChangeMon
	)
if %D% GTR %day% if %mon% LEQ 01 (
	call :ChangeMonYer
	)
goto loop

:end
EXIT /B %ERRORLEVEL%

:ChangeDay
::date %mon%-%D%-%yer%
date 9-%D%-%yer%
EXIT /B 0

:ChangeMon
set new_mon=1%mon%
set /A new_mon=%new_mon%-101
echo month changed to %new_mon%
date %new_mon%-%D%-%yer%
EXIT /B 0

:ChangeMonYer
set /A new_mon=12
set /A new_yer=%yer%-1
echo 1 : %new_yer%
echo year changed to %new_yer%
date %new_mon%-%D%-%new_yer%
EXIT /B 0

:delay50
ping 127.0.0.1 -n 1 -w 50> nul
EXIT /B 0