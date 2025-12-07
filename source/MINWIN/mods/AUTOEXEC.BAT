@ECHO OFF

REM Made by Wengier and Roy. China DOS Union.
REM All rights reserved. 2002-2003.
REM Modified for MultiPatcher

CD MINWIN
SET PATH=%PATH%;A:\MINWIN

SET DIRCMD=/OGN /4
SET PROMPT=$P$G
TM /R=30 /D=250
LH KILLER
SET LFN=
WBAT BOX "Enable Long File Names(LFN) support?",Yes,No #1,5
IF ERRORLEVEL 1 IF NOT ERRORLEVEL 2 SET LFN=1
IF %LFN%#==1# LH DOSLFN /Z:CP437UNI.TBL
LH SHSUCDX /D:IDE-CD
LH DOSKEY
LH CTMOUSE
::Note: The following line is for compatibility on some systems.
LH CTMOUSE>NUL
LH SHARE
LH ZENO /Q
ECHO.
ECHO Now you're in MS-DOS 7.10 prompt.
ECHO Made by Wengier and Roy, China DOS Union.
ECHO.
WBAT BOX "Launch Mini-Windows right now?",Yes,No #1,5
IF ERRORLEVEL 2 IF NOT ERRORLEVEL 3 GOTO NOWIN
LH ESCAPE
CALL WIN.BAT
GOTO END
:NOWIN
CLS
ECHO Mini-Windows 3.11 by China DOS Union
ECHO Made by Wengier and Roy. All rights reserved.
WRITEXT 0+ 1 "Any comments, please come to the forum at: " -f15 http://dosbbs.2ya.com/ -f7
ECHO.
ECHO.
ECHO Type "WIN" to start Mini-Windows!
ECHO.
:END
