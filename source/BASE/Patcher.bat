@echo off

REM
REM The following is a .BAT script that should be
REM able to detect whether the OS is MS-DOS,
REM Windows 95/98/ME, or Windows NT.
REM

if not "%WINDIR%"=="" goto WINGUI
REM Since windir is not set, we are probably in PURE MS-DOS.
REM
REM MSDOS:
if not exist patchx16.exe goto PATCH_16_NOT_FOUND
patchx16.exe %1 %2 %3 %4 %5 %6 %7 %8 %9
goto END

:WINGUI
REM System is running a windows GUI.
REM If system is Windows Vista or above, you chose the wrong house fool!
ver | find " 6." >nul
if not errorlevel 1 goto WINVISTA

ver | find " 10." >nul
if not errorlevel 1 goto WINVISTA

REM Since it is not Windows Vista+, this runs the 16-Bit VB4 app.
REM Hence, we neeeeed to check if the user has Runtime installed.
if not exist %WINDIR%\SYSTEM\VSHARE.386 goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\STKIT416.DLL goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\VB40016.DLL goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\OC25.DLL goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\OLE2.DLL goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\TYPELIB.DLL goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\OLE2DISP.DLL goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\OLE2PROX.DLL goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\OLE2CONV.DLL goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\STORAGE.DLL goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\COMPOBJ.DLL goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\OLE2.REG goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\OLE2NLS.DLL goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\STDOLE.TLB goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\SCP.DLL goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\VAEN21.OLB goto VBRUNTIME
if not exist %WINDIR%\SYSTEM\CTL3DV2.DLL goto VBRUNTIME
REM So now that we have that out of the way, let's check if our buddy is running Windows NT or not.
if not "%PROCESSOR_ARCHITECTURE%"=="" goto WINNT
REM That was easy. Now we know for sure, this is Win3.1 or 9x.
REM
REM Windows 95/98/ME:
REM Windows 3.1 will also try this, but it will likely fail to run the GUI app.
REM In my case, it tries to relaunch WIN.COM, and it fails.
if not exist patchg16.exe goto PATCH_GUI16_NOT_FOUND
patchg16.exe %1 %2 %3 %4 %5 %6 %7 %8 %9
echo If you are using Windows 3.1, run PATCHG32.EXE.
goto END

:WINNT
REM Assume all NT versions in this group are Windows XP or below. NTVDM will handle this 16bit app.
if not exist patchg16.exe goto PATCH_GUI16_NOT_FOUND
patchg16.exe %1 %2 %3 %4 %5 %6 %7 %8 %9
goto END

:WINVISTA
REM Windows Vista+ - uses 32bit gui app.
if not exist patchg32.exe goto PATCH_GUI32_NOT_FOUND
patchg32.exe %1 %2 %3 %4 %5 %6 %7 %8 %9
goto END

:VBRUNTIME
REM Executes vbruntime setup
if not exist RUNTIME\VB4\SETUP.EXE GOTO VBRUNTIME_NOT_FOUND
RUNTIME\VB4\SETUP.EXE
REM Skip to end, since if we go back to WINGUI, it will execute BEFORE runtime setup finishes.
goto END

REM File not found error stuffs:

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

:VBRUNTIME_NOT_FOUND
echo.
echo The file 'runtime\vb4\setup.exe' could not be found in the current directory.
echo Please install the VisualBasic 4.0 16-bit Runtime manually.
echo.
goto END

:END