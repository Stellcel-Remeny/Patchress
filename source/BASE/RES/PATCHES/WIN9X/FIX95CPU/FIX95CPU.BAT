@ECHO OFF
ECHO [0;31;40m
CLS
ECHO.
REM MS win95 logo removed due to syntax errors

ECHO                               Microsoft Windows 95
ECHO.
ECHO                         High-Speed Processor Support Setup
ECHO                            Version 3.0 by LoneCrusader
ECHO                            (BAT file modified for MPC)
ECHO.
ECHO                            Press Any Key To Continue...
PAUSE > NUL
CLS
ECHO.
ECHO                               FIX95CPU Version 3.0
ECHO                       Supporting All Versions of Windows 95
ECHO.
ECHO              This disk will install the necessary files for running
ECHO           Windows 95 RTM, Windows 95 A, Windows 95 B, or Windows 95 C
ECHO           in AMD systems with processor speeds greater than 350MHz, and
ECHO           in Intel systems with processor speeds greater than 2.1GHz.
ECHO.
ECHO              This update is intended for use during a new installation
ECHO           of Windows 95, but can be used on pre-existing installations.
ECHO.
ECHO              Be sure you have read the README.TXT file that accompanies
ECHO           this disk so you may fully understand the issues involved and
ECHO           the process for making this work!
ECHO.
ECHO                  NOTE:  Requires MSDOS.SYS available on C:\ Drive
ECHO.
ECHO              Pressing CTRL-C at any time will terminate this program.
ECHO.
ECHO.

CHOICE View the README file? (Recommended!) 
IF ERRORLEVEL 2 GOTO BYPASS
MORE README.TXT
ECHO.
ECHO.
ECHO.
ECHO.
ECHO              Pressing CTRL-C at any time will terminate this program.

:BYPASS
ECHO.
ECHO.
ECHO.
ECHO Ready to install Windows 95 High-Speed Processor Support.
PAUSE

IF EXIST C:\MSDOS.SYS GOTO DETECT
CLS
ECHO [1;33;40m
ECHO.
ECHO.
ECHO                 !!!!!!!!!!!!!!!!!!!! ERROR !!!!!!!!!!!!!!!!!!!!
ECHO.
ECHO                          NO OPERATING SYSTEM DETECTED!
ECHO.
ECHO                               PATCHING ABORTED!!!
ECHO.
ECHO                 !!!!!!!!!!!!!!!!!!!! ERROR !!!!!!!!!!!!!!!!!!!!
ECHO.
ECHO.
ECHO [0;31;40m
ECHO.
ECHO.
ECHO                         MSDOS.SYS was not found in C:\.
GOTO QUIT

:DETECT
FIND.EXE < C:\MSDOS.SYS > C:\!W95DIR.ARG /I "WINDIR"
COPY SET.ARG + C:\!W95DIR.ARG C:\!W95VARS.BAT
CALL C:\!W95VARS.BAT

GR /V:0 /1234 C:\!W95VARS.BAT "WinDir=" "RegDir="
GR /V:0 /1234 C:\!W95VARS.BAT \ \\
CALL C:\!W95VARS.BAT

DEL C:\!W95DIR.ARG
DEL C:\!W95VARS.BAT

IF NOT EXIST %WINDIR%\WUPDMGR.EXE GOTO W95
CLS
ECHO [1;33;40m
ECHO.
ECHO.
ECHO                 !!!!!!!!!!!!!!!!!!!! ERROR !!!!!!!!!!!!!!!!!!!!
ECHO.
ECHO                        WINDOWS 98, 98 SE, OR ME DETECTED!
ECHO.
ECHO                               PATCHING ABORTED!!!
ECHO.
ECHO                 !!!!!!!!!!!!!!!!!!!! ERROR !!!!!!!!!!!!!!!!!!!!
ECHO.
ECHO.
ECHO [0;31;40m
ECHO.
ECHO.
ECHO                       This update is for Windows 95 only.
GOTO QUIT

:W95
ECHO Copying new files...
COPY /Y W95BOTH\SYSTEM\*.* %WINDIR%\SYSTEM
COPY /Y W95BOTH\SYSTEM\IOSUBSYS\*.* %WINDIR%\SYSTEM\IOSUBSYS
COPY /Y W95BOTH\SYSTEM\VMM32\*.* %WINDIR%\SYSTEM\VMM32
IF EXIST %WINDIR%\FILEXFER.EXE GOTO OSR2
COPY /Y W95RTM\*.* %WINDIR%
COPY /Y W95RTM\SYSTEM\IOSUBSYS\*.* %WINDIR%\SYSTEM\IOSUBSYS
ECHO Updating system registry...
COPY W95RTM.REG %WINDIR%\FIX95CPU.REG
GR /V:0 /1234 %WINDIR%\FIX95CPU.REG "C:\\WINDOWS" %REGDIR%
COPY %WINDIR%\REGEDIT.EXE %WINDIR%\REG95RTM.EXE
CALL %WINDIR%\REG95RTM.EXE /L:%WINDIR%\SYSTEM.DAT /R:%WINDIR%\USER.DAT %WINDIR%\FIX95CPU.REG
DEL %WINDIR%\REG95RTM.EXE
GOTO W95POST

:OSR2
COPY /Y W95OSR2\SYSTEM\IOSUBSYS\*.* %WINDIR%\SYSTEM\IOSUBSYS
COPY /Y W95OSR2\SYSTEM\VMM32\*.* %WINDIR%\SYSTEM\VMM32
ECHO Updating system registry...
COPY W95OSR2.REG %WINDIR%\FIX95CPU.REG
GR /V:0 /1234 %WINDIR%\FIX95CPU.REG "C:\\WINDOWS" %REGDIR%
CALL %WINDIR%\REGEDIT.EXE /L:%WINDIR%\SYSTEM.DAT /R:%WINDIR%\USER.DAT %WINDIR%\FIX95CPU.REG

:W95POST
DEL %WINDIR%\FIX95CPU.REG
%WINDIR%\WININIT.EXE
COPY /Y W95BOTH\SYSTEM\VMM32\POST\*.* %WINDIR%\SYSTEM\VMM32
CLS
ECHO [1;32;40m
ECHO.
ECHO.
ECHO                !!!!!!!!!!!!!!!!!!!! SUCCESS !!!!!!!!!!!!!!!!!!!!
ECHO.
ECHO.
ECHO                    FIX95CPU HAS BEEN INSTALLED SUCCESSFULLY!
ECHO.
ECHO.
ECHO                !!!!!!!!!!!!!!!!!!!! SUCCESS !!!!!!!!!!!!!!!!!!!!
ECHO.
ECHO.
ECHO [0;31;40m
ECHO.
ECHO               Windows 95 Setup will continue normally upon restart.
ECHO.
ECHO             Remember to follow the further instructions in README.TXT.
ECHO.
ECHO                         Long Live Windows 95! Good Luck!
ECHO.
ECHO.

:QUIT
