ECHO OFF

for /F "tokens=3 delims=: " %%H in ('sc query "w32time" ^| findstr "        STATE"') do (
	echo %%H
	if /I "%%H" NEQ "RUNNING" (
		call :UpdateTime
		goto end
	) ELSE (
		call :EnterDate
		goto end
	)
)

:EnterDate
set mydate=%date:~7,2%
set day=%mydate%
set mydate=%date:~4,2%
set mon=%mydate%
set mydate=%date:~10,4%
set yer=%mydate%

rem Remove leading zeros from the zero-extended number
for /f "tokens=* delims=0" %%a in ("%day%") do set "day=%%a"

reg add HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\W32Time\Parameters /f /v Type /t REG_SZ /d NoSync
net stop w32time
sc config w32time start= disabled
reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\DateTime\Servers /f /v 1 /t REG_SZ /d 1
reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\DateTime\Servers /f /v 2 /t REG_SZ /d 2
SET /P D=Enter date(mm-d): 
if not x%D:-=%==x%D% (
	call :ChangeMonDay
	goto end
	)
if %D% LEQ %day% (
	call :ChangeDay
	goto end
	)
if %D% GTR %day% if %mon% GTR 01 (
	call :ChangeMon
	goto end
	)
if %D% GTR %day% if %mon% LEQ 01 (
	call :ChangeMonYer
	goto end
	)

:end
EXIT /B %ERRORLEVEL%

:ChangeDay
echo day changed to %D%
date %mon%-%D%-%yer%
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

:ChangeMonDay
echo month and day changed to %D%
date %D%-%yer%
EXIT /B 0

:UpdateTime
reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\DateTime\Servers /f /v 1 /t REG_SZ /d time.windows.com
reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\DateTime\Servers /f /v 2 /t REG_SZ /d time.nist.gov
call :delay50
reg add HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\W32Time\Parameters /f /v Type /t REG_SZ /d NTP
call :delay50
sc config w32time start= demand
call :delay50
net start w32time
::w32tm /query /peers
w32tm /resync /nowait
EXIT /B 0

:delay50
ping 127.0.0.1 -n 1 -w 50> nul
EXIT /B 0