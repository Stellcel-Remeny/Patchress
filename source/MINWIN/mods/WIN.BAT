@echo off

rem Made by Wengier and Roy, China DOS Union.
rem All rights reserved. 2002-2003.
rem (modified for mpc)

if %1.==_next_. goto nextstep
if %1.==_quit_. goto quit
xmsdsk 4096 /y > nul
findramd>nul
if %ramdrive%#==# echo Error: Can't create RAM disk!
if %ramdrive%#==# goto shut
if not exist %ramdrive%\temp\nul md %ramdrive%\temp
set temp=%ramdrive%\temp
set tmp=%ramdrive%\temp
echo y|lock %ramdrive%>nul

:start
cls
echo.
echo Starting Mini-Windows 3.11...
echo Now extracting Mini-Windows and applications...
echo.
copy a:\win.bat %ramdrive%\ > nul
if not exist %ramdrive%\win.bat goto copyerr
%ramdrive%\win.bat _next_
goto nextstep

:SHUT
WBAT BOX "Please enter your choice:",Stay on DOS,Shutdown the computer,Restart the computer #1,60
IF NOT ERRORLEVEL 4 GOTO ANS
WBAT BOX (RED ON YELLOW) "Note: Please make a choice!",OK
GOTO SHUT
:ANS
IF NOT ERRORLEVEL 2 GOTO END
IF ERRORLEVEL 3 GOTO RES
ECHO Now trying to shutdown the computer..
ECHO.
SHUTDOWN S
ECHO.
ECHO Shutdown failed. Your computer may not have an ATX power.
:RES
ECHO Now restarting the computer...
ECHO.
SHUTDOWN R
GOTO END

:nextstep
pkunzjr -o a:\mwfw3.zip %RAMDRIVE%\
copy a:\command.com %ramdrive%\ > nul
if not exist %ramdrive%\win.com goto copyerr
echo.
echo MiniWindows has been extracted successfully.
set comspec=%ramdrive%\command.com
set path=%ramdrive%\;%PATH%

echo Copying system settings...
echo.
copy a:\MWCONFIG\*.* %ramdrive%\ /y > nul

if %lfn%#==1# inifile %ramdrive%\system.ini [boot] network.drv=fmlfn.drv
if not %lfn%#==1# inifile %ramdrive%\system.ini [boot] network.drv=;
%ramdrive%
win.com

a:\win.bat _quit_
goto continue

:copyerr
cls
echo Error!!!
echo
wbat box "Failed to extract MiniWindows properly",Retry,Quit #1,5
if errorlevel 2 a:\win.bat _quit_
goto start

:quit
cls
echo.
echo Removing Mini-Windows from memory... please wait...
set comspec=a:\command.com
set path=a:\;%CDROM%:\DOSINS;%CDROM%:\
xmsdsk /u /y > nul
echo Now Mini-Windows has been successfully removed from the memory.
echo Made by Wengier and Roy, China DOS Union.
goto shut

:end
cls
echo Thanks for using Mini-Windows 3.11!
echo By Wengier and Roy, China DOS Union. All rights reserved.
writext 0+ 1 "Any comments, please come to the forum at: " -f15 http://dosbbs.2ya.com/ -f7
echo.
echo Type "WIN" to start Mini-Windows again if you want!
echo Type "patcher" to start MultiPatcher!
echo.
