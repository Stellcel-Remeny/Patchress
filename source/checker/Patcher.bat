@echo off

REM
REM The following is a .BAT script that should be
REM able to detect whether the OS is MS-DOS,
REM Windows 95/98/ME, or Windows NT.
REM

if not "%PROCESSOR_ARCHITECTURE%"=="" goto WINNT
if not "%WINBOOTDIR%"=="" goto WIN9X
goto MSDOS

:WINNT
if exist %systemroot%\System32\user32.dll (
    REM NT4 or higher (GUI subsystem present)
    if not exist patchx32.exe goto PATCH_32_NOT_FOUND
    start "" "patchx32.exe" %*
) else (
    REM NT3.51 or lower
    echo Your version of Windows NT (NT < 4.0) does not have a dedicated application yet. Sorry!
)
goto END

:WIN9X
if not exist patchx32.exe goto PATCH_32_NOT_FOUND
start "" "patchx32.exe" %*
goto END

:MSDOS
if not exist patchx16.exe goto PATCH_16_NOT_FOUND
patchx16.exe %1 %2 %3 %4 %5 %6 %7 %8 %9
goto END

:PATCH_16_NOT_FOUND
echo.
echo The file 'patchx16.exe' could not be found in the current directory.
echo Therefore, ...cannot continue.
echo.
goto END

:PATCH_32_NOT_FOUND
echo.
echo The file 'patchx32.exe' could not be found in the current directory.
echo Therefore, ...cannot continue.
echo.
goto END

:END