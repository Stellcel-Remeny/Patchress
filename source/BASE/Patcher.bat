@echo off

REM
REM The following is a .BAT script that should be
REM able to detect whether the OS is MS-DOS,
REM Windows 95/98/ME, or Windows NT.
REM

if not "%PROCESSOR_ARCHITECTURE%"=="" goto WINNT
if not "%WINDIR%"=="" goto WIN9X
goto MSDOS

:WINNT
REM Windows NT
ver | find " 6." >nul && goto WINVISTA
ver | find " 10." >nul && goto WINVISTA
REM Assume all other NT versions are Windows XP or below. NTVDM will handle this 16bit app.
if not exist patchg16.exe goto PATCH_GUI16_NOT_FOUND
patchg16.exe %1 %2 %3 %4 %5 %6 %7 %8 %9
goto END

:WINVISTA
REM Windows Vista+ - uses 32bit gui app.
if not exist patchg32.exe goto PATCH_GUI32_NOT_FOUND
patchg32.exe %1 %2 %3 %4 %5 %6 %7 %8 %9
goto END

:WIN9X
REM Windows 3.1/95/98/ME
if not exist patchg16.exe goto PATCH_GUI16_NOT_FOUND
patchg16.exe %1 %2 %3 %4 %5 %6 %7 %8 %9
goto END

:MSDOS
REM Pure MS-DOS
if not exist patchx16.exe goto PATCH_16_NOT_FOUND
patchx16.exe %1 %2 %3 %4 %5 %6 %7 %8 %9
goto END

:PATCH_16_NOT_FOUND
echo.
echo The file 'patchx16.exe' could not be found in the current directory.
echo Try launching the appropriate application for your system manually.
echo.
goto END

:PATCH_GUI16_NOT_FOUND
echo.
echo The file 'patchg16.exe' could not be found in the current directory.
echo Try launching the appropriate application for your system manually.
echo.
goto END

:PATCH_GUI32_NOT_FOUND
echo.
echo The file 'patchg32.exe' could not be found in the current directory.
echo Try launching the appropriate application for your system manually.
echo.
goto END

:END