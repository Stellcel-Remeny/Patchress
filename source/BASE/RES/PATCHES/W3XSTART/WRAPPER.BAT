@echo off
REM Copy W3XSTART.EXE and MSDOSSYS.INF to C:\ for write access...
cls
echo Copying W3XSTART.EXE to C:\
copy W3XSTART.EXE C:\
echo Copying MSDOSSYS.INF to C:\
copy MSDOSSYS.INF C:\
C:
cd C:\
W3XSTART.EXE
echo Cleaning..
del C:\W3XSTART.EXE
del C:\MSDOSSYS.INF