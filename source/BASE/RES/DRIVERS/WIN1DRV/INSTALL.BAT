echo off
set path=a:\
cls
echo	This is the installation batch file for the Windows Driver
echo	Library, Volume 1, Disk 1.  If you have only one floppy disk
echo	drive, you should be running this batch file from your hard
echo	disk.  See the file "readme.txt" for details. This batch file 
echo	installs only display and pointing device drivers.  To install 
echo	printer drivers, use the Windows Control Panel application.
echo	.
echo	To install a device driver from this volume, you will need
echo	to modify a copy of your Windows Setup and Build disks.  Make 
echo	copies of these two disks and store the originals in a safe 
echo	place.  Work only with your copies.
echo	.
ync /c "yn"	Have you made copies of your Windows Setup and Build disks?
if errorlevel 1 goto abortnotcopies
cls
echo	This disk contains drivers for the following displays:
echo			1)	Moniterm Viking I
echo			2)	Sigma Color 400
echo			3)	Tseng EVA
echo			4)	Video-7 VEGA Deluxe
echo			5)	Wyse WY-700 High Resolution Display Adapter
echo			6)	Image Manager 1024
echo	.
ync /c "yn"	Do you wish to install one of these display drivers?
if errorlevel 1 goto pointingdevice
echo	.
ync /c "123456"	Which display driver do you wish to install?
if errorlevel 5 goto 24install
if errorlevel 4 goto wyinstall
if errorlevel 3 goto veinstall
if errorlevel 2 goto tsinstall
if errorlevel 1 goto siinstall
if errorlevel 0 goto viinstall
goto pointingdevice

:24install
cls
echo	This procedure transfers the files required to set up Windows
echo	for the Image Manager 1024 display onto copies of the Windows Setup and 
echo	Build disks.
echo	You should make copies of your Setup and Build disks, and put
echo	the originals in a safe place.  Do not use the original disks
echo	in this procedure.  Work only with your duplicate copies.
pause

:24start
ync /c "yn" "Does your machine have two floppy disk drives?"
if errorlevel 1 goto h24start
cls
echo	Please insert Driver Library Disk #1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause
if exist a:drvlib1.lbl goto 24drvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto 24start

:24drvlibdisk
if exist b:setup.lbl goto 24setupdisk
echo	The disk in drive B does not appear to be the Windows Setup disk.  
pause
goto 24start

:24setupdisk
echo	Making room on the Setup disk for the new files . . .
if exist b:emm.pc del b:emm.pc
if exist b:emm.at del b:emm.at
if exist b:attdc.drv del b:attdc.drv
if exist b:attdeb.drv del b:attdeb.drv
if exist b:egahires.drv del b:egahires.drv
if exist b:egalores.drv del b:egalores.drv
if exist b:egahibw.drv del b:egahibw.drv
echo	Copying Image Manager 1024 drivers to the Setup disk . . .
copy a:IM1024.DRV b:
del B:LOFONTS.FON
ren VMILO.FON LOFONTS.FON
copy a:LOFONTS.FON b:
ren LOFONTS.FON VMILO.FON
if not exist b:IM1024.DRV goto abortcopyfailed
if not exist b:LOFONTS.FON goto abortcopyfailed

:24needbuild
pause
cls
echo	Please insert your duplicate of the Windows build disk in drive B.
pause
if exist b:build.lbl goto 24builddisk
echo	The disk in drive B does not appear to be the Windows build disk.  
goto 24needbuild

:24builddisk
echo	Making room on the build disk for the new files . . .
if exist b:att*.* del b:att*.*
if exist b:egahires.* del b:egahires.*
if exist b:egahibw.* del b:egahibw.*
echo	Copying Image Manager files to the build disk . . .
copy a:IM1024.GRB b:
copy a:IM1024.LGO b:
if not exist b:IM1024.GRB goto abortcopyfailed
if not exist b:IM1024.LGO goto abortcopyfailed
goto pointingdevice

:h24start
cls
echo	Please insert Driver Library Disk #1 into drive A.
pause
if exist a:drvlib1.lbl goto h24drvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto h24start

:h24drvlibdisk
echo	Copying Image Manager files to the hard disk . . .
copy a:ync.exe c:
copy a:IM1024.DRV c:
copy a:VMILO.FON c:
copy a:IM1024.GRB c:
copy a:IM1024.LGO c:
if not exist c:ync.exe goto abortcopyfailed
if not exist c:IM1024.DRV goto abortcopyfailed
if not exist c:VMILO.FON goto abortcopyfailed
if not exist c:IM1024.GRB goto abortcopyfailed
if not exist c:IM1024.LGO goto abortcopyfailed
pause

:h24getsetupdisk
cls
echo	Please insert a copy of the Windows Setup disk
echo	in drive A:.
pause
if exist a:setup.lbl goto h24setupdisk
echo	The disk in drive A: does not appear to be a copy of the
echo	Windows Setup disk.
pause
goto h24getsetupdisk

:h24setupdisk
echo	Making room on the Setup disk for the new files . . .
if exist a:emm.pc del a:emm.pc
if exist a:emm.at del a:emm.at
if exist a:attdc.drv del a:attdc.drv
if exist a:attdeb.drv del a:attdeb.drv
if exist a:egahires.drv del a:egahires.drv
if exist a:egalores.drv del a:egalores.drv
if exist a:egahibw.drv del a:egahibw.drv
echo	Copying Image Manager drivers to the Setup disk . . .
copy c:IM1024.DRV a:
del A:LOFONTS.FON
ren VMILO.FON LOFONTS.FON
copy c:LOFONTS.FON a:
ren LOFONTS.FON VMILO.FON
if not exist a:IM1024.DRV goto abortcopyfailed
if not exist a:LOFONTS.FON goto abortcopyfailed
del c:IM1024.DRV
del c:VMILO.FON

:h24getbuilddisk
cls
echo	Please insert a copy of the Windows Build disk
echo	in drive A:.
pause
if exist a:build.lbl goto h24builddisk
echo	The disk in drive A does not appear to be a copy of the
echo	Windows Build disk.
pause
goto h24getbuilddisk

:h24builddisk
echo	Making room on the build disk for the new files . . .
if exist a:att*.* del a:att*.*
if exist a:egahires.* del a:egahires.*
if exist a:egahibw.* del a:egahibw.*
echo	Copying Image Manager files to the build disk . . .
copy c:IM1024.GRB a:
copy c:IM1024.LGO a:
if not exist a:IM1024.GRB goto abortcopyfailed
if not exist a:IM1024.LGO goto abortcopyfailed
del c:IM1024.GRB
del c:IM1024.LGO
goto pointingdevice

REM End of 1024 install

:siinstall
cls
echo	This procedure transfers the files required to set up Windows
echo	for the Sigma 400 display onto copies of the Windows Setup and 
echo	Build disks.
echo	You should make copies of your Setup and Build disks, and put
echo	the originals in a safe place.  Do not use the original disks
echo	in this procedure.  Work only with your duplicate copies.
pause

:sistart
ync /c "yn" "Does your machine have two floppy disk drives?"
if errorlevel 1 goto hsistart
cls
echo	Please insert Driver Library Disk #1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause
if exist a:drvlib1.lbl goto sidrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto sistart

:sidrvlibdisk
if exist b:setup.lbl goto sisetupdisk
echo	The disk in drive B does not appear to be the Windows Setup disk.  
pause
goto sistart

:sisetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist b:emm.pc del b:emm.pc
if exist b:emm.at del b:emm.at
if exist b:attdc.drv del b:attdc.drv
if exist b:attdeb.drv del b:attdeb.drv
if exist b:egahires.drv del b:egahires.drv
if exist b:egalores.drv del b:egalores.drv
if exist b:egahibw.drv del b:egahibw.drv
echo	Copying Sigma drivers to the Setup disk . . .
copy a:sigma4.drv b:
copy a:sigma8.drv b:
if not exist b:sigma4.drv goto abortcopyfailed
if not exist b:sigma8.drv goto abortcopyfailed

:sineedbuild
pause
cls
echo	Please insert your duplicate of the Windows build disk in drive B.
pause
if exist b:build.lbl goto sibuilddisk
echo	The disk in drive B does not appear to be the Windows build disk.  
goto sineedbuild

:sibuilddisk
echo	Making room on the build disk for the new files . . .
if exist b:att*.* del b:att*.*
if exist b:egahires.* del b:egahires.*
if exist b:egahibw.* del b:egahibw.*
echo	Copying Sigma files to the build disk . . .
copy a:sigma4.lgo b:
copy a:sigma8.lgo b:
copy a:sigma4.grb b:
copy a:sigma8.grb b:
if not exist b:sigma4.lgo goto abortcopyfailed
if not exist b:sigma8.lgo goto abortcopyfailed
if not exist b:sigma4.grb goto abortcopyfailed
if not exist b:sigma8.grb goto abortcopyfailed
goto pointingdevice

:hsistart
cls
echo	Please insert Driver Library Disk #1 into drive A.
pause
if exist a:drvlib1.lbl goto hsidrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto hsistart

:hsidrvlibdisk
echo	Copying Sigma files to the hard disk . . .
copy a:ync.exe c:
copy a:sigma4.drv c:
copy a:sigma8.drv c:
copy a:sigma4.lgo c:
copy a:sigma8.lgo c:
copy a:sigma4.grb c:
copy a:sigma8.grb c:
if not exist c:sigma4.drv goto abortcopyfailed
if not exist c:sigma8.drv goto abortcopyfailed
if not exist c:sigma4.lgo goto abortcopyfailed
if not exist c:sigma8.lgo goto abortcopyfailed
if not exist c:sigma4.grb goto abortcopyfailed
if not exist c:sigma8.grb goto abortcopyfailed
pause

:hsigetsetupdisk
cls
echo	Please insert a copy of the Windows Setup disk
echo	in drive A:.
pause
if exist a:setup.lbl goto hsisetupdisk
echo	The disk in drive A: does not appear to be a copy of the
echo	Windows Setup disk.
pause
goto hsigetsetupdisk

:hsisetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist a:emm.pc del a:emm.pc
if exist a:emm.at del a:emm.at
if exist a:attdc.drv del a:attdc.drv
if exist a:attdeb.drv del a:attdeb.drv
if exist a:egahires.drv del a:egahires.drv
if exist a:egalores.drv del a:egalores.drv
if exist a:egahibw.drv del a:egahibw.drv
echo	Copying Sigma drivers to the Setup disk . . .
copy c:sigma4.drv a:
copy c:sigma8.drv a:
if not exist a:sigma4.drv goto abortcopyfailed
if not exist a:sigma8.drv goto abortcopyfailed
del c:sigma4.drv
del c:sigma8.drv

:hsigetbuilddisk
cls
echo	Please insert a copy of the Windows Build disk
echo	in drive A:.
pause
if exist a:build.lbl goto hsibuilddisk
echo	The disk in drive A does not appear to be a copy of the
echo	Windows Build disk.
pause
goto hsigetbuilddisk

:hsibuilddisk
echo	Making room on the build disk for the new files . . .
if exist a:att*.* del a:att*.*
if exist a:egahires.* del a:egahires.*
if exist a:egahibw.* del a:egahibw.*
echo	Copying Sigma files to the build disk . . .
copy c:sigma4.lgo a:
copy c:sigma8.lgo a:
copy c:sigma4.grb a:
copy c:sigma8.grb a:
if not exist a:sigma4.lgo goto abortcopyfailed
if not exist a:sigma8.lgo goto abortcopyfailed
if not exist a:sigma4.grb goto abortcopyfailed
if not exist a:sigma8.grb goto abortcopyfailed
del c:sigma4.lgo
del c:sigma8.lgo
del c:sigma4.grb
del c:sigma8.grb
goto pointingdevice

:tsinstall
cls
echo	This procedure file copies the files required to set up Windows
echo	for the Tseng display onto copies of the Windows Setup and 
echo	Build disks.
echo	You should make copies of your Setup and Build disks, and put
echo	the originals in a safe place.  Do not use the original disks
echo	in this procedure.  Work only with your duplicate copies.
pause

:tsstart
ync /c "yn" "Does your machine have two floppy disk drives?"
if errorlevel 1 goto htsstart
cls
echo	Please insert Driver Library Disk 1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause
if exist a:drvlib1.lbl goto tsdrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto tsstart

:tsdrvlibdisk
if exist b:setup.lbl goto tssetupdisk
echo	The disk in drive B does not appear to be the Windows Setup disk.  
pause
goto tsstart

:tssetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist b:emm.pc del b:emm.pc
if exist b:emm.at del b:emm.at
if exist b:attdc.drv del b:attdc.drv
if exist b:attdeb.drv del b:attdeb.drv
echo	Copying Tseng driver to the Setup disk . . .
copy a:tseng.drv b:
if not exist b:tseng.drv goto abortcopyfailed

:tsneedbuild
pause
cls
echo	Please insert your duplicate of the Windows build disk in drive B.
pause
if exist b:build.lbl goto tsbuilddisk
echo	The disk in drive B does not appear to be the Windows build disk.  
goto tsneedbuild

:tsbuilddisk
echo	Making room on the build disk for the new files . . .
if exist b:att*.* del b:att*.*
echo	Copying Tseng files to the build disk . . .
copy a:tseng.lgo b:
copy a:tseng.grb b:
if not exist b:tseng.lgo goto abortcopyfailed
if not exist b:tseng.grb goto abortcopyfailed
goto pointingdevice

:htsstart
cls
echo	Please insert Driver Library Disk #1 into drive A.
pause
if exist a:drvlib1.lbl goto htsdrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto htsstart

:htsdrvlibdisk
echo	Copying Tseng files to the hard disk . . .
copy a:ync.exe c:
copy a:tseng.drv c:
copy a:tseng.lgo c:
copy a:tseng.grb c:
if not exist c:tseng.drv goto abortcopyfailed
if not exist c:tseng.lgo goto abortcopyfailed
if not exist c:tseng.grb goto abortcopyfailed
pause

:htsgetsetupdisk
cls
echo	Please insert a copy of the Windows Setup disk
echo	in drive A:.
pause
if exist a:setup.lbl goto htssetupdisk
echo	The disk in drive A: does not appear to be a copy of the
echo	Windows Setup disk.
pause
goto htsgetsetupdisk

:htssetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist a:emm.pc del a:emm.pc
if exist a:emm.at del a:emm.at
if exist a:attdc.drv del a:attdc.drv
if exist a:attdeb.drv del a:attdeb.drv
if exist a:egahires.drv del a:egahires.drv
if exist a:egalores.drv del a:egalores.drv
if exist a:egahibw.drv del a:egahibw.drv
echo	Copying Tseng driver to the Setup disk . . .
copy c:tseng.drv a:
if not exist a:tseng.drv goto abortcopyfailed
del c:tseng.drv

:htsgetbuilddisk
cls
echo	Please insert a copy of the Windows Build disk
echo	in drive A:.
pause
if exist a:build.lbl goto htsbuilddisk
echo	The disk in drive A does not appear to be a copy of the
echo	Windows Build disk.
pause
goto htsgetbuilddisk

:htsbuilddisk
echo	Making room on the build disk for the new files . . .
if exist a:att*.* del a:att*.*
if exist a:egahires.* del a:egahires.*
if exist a:egahibw.* del a:egahibw.*
echo	Copying Tseng files to the build disk . . .
copy c:tseng.lgo a:
copy c:tseng.grb a:
if not exist a:tseng.lgo goto abortcopyfailed
if not exist a:tseng.grb goto abortcopyfailed
del c:tseng.lgo
del c:tseng.grb
goto pointingdevice


:veinstall
cls
echo	This procedure file copies the files required to set up Windows
echo	for the Video 7 VEGA Deluxe display onto copies of the Windows 
echo	Setup and Build disks.
echo	You should make copies of your Setup and Build disks, and put
echo	the originals in a safe place.  Do not use the original disks
echo	in this procedure.  Work only with your duplicate copies.
pause

:vestart
ync /c "yn" "Does your machine have two floppy disk drives?"
if errorlevel 1 goto hvestart
cls
echo	Please insert Driver Library Disk #1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause
if exist a:drvlib1.lbl goto vedrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto vestart

cls
echo	Please insert Driver Library Disk 1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause
if exist a:drvlib1.lbl goto vedrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto vestart

:vedrvlibdisk
if exist b:setup.lbl goto vesetupdisk
echo	The disk in drive B does not appear to be the Windows Setup disk.  
pause
goto vestart

:vesetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist b:emm.pc del b:emm.pc
if exist b:emm.at del b:emm.at
if exist b:attdc.drv del b:attdc.drv
if exist b:attdeb.drv del b:attdeb.drv
echo	Copying VEGA driver to the Setup disk . . .
copy a:vega640.drv b:
copy a:vega752.drv b:
if not exist b:vega640.drv goto abortcopyfailed
if not exist b:vega752.drv goto abortcopyfailed

:veneedbuild
pause
cls
echo	Please insert your duplicate of the Windows build disk in drive B.
pause
if exist b:build.lbl goto vebuilddisk
echo	The disk in drive B does not appear to be the Windows build disk.  
goto veneedbuild

:vebuilddisk
echo	Making room on the build disk for the new files . . .
if exist b:att*.* del b:att*.*
echo	Copying VEGA files to the build disk . . .
copy a:vega640.lgo b:
copy a:vega752.lgo b:
copy a:vega640.grb b:
copy a:vega752.grb b:
if not exist b:vega640.lgo goto abortcopyfailed
if not exist b:vega752.lgo goto abortcopyfailed
if not exist b:vega640.grb goto abortcopyfailed
if not exist b:vega752.grb goto abortcopyfailed
goto pointingdevice

:hvestart
cls
echo	Please insert Driver Library Disk #1 into drive A.
pause
if exist a:drvlib1.lbl goto hvedrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto hvestart

:hvedrvlibdisk
echo	Copying VEGA files to the hard disk . . .
copy a:ync.exe c:
copy a:vega640.drv c:
copy a:vega752.drv c:
copy a:vega640.lgo c:
copy a:vega752.lgo c:
copy a:vega640.grb c:
copy a:vega752.grb c:
if not exist c:vega640.drv goto abortcopyfailed
if not exist c:vega752.drv goto abortcopyfailed
if not exist c:vega640.lgo goto abortcopyfailed
if not exist c:vega752.lgo goto abortcopyfailed
if not exist c:vega640.grb goto abortcopyfailed
if not exist c:vega752.grb goto abortcopyfailed
pause

:hvegetsetupdisk
cls
echo	Please insert a copy of the Windows Setup disk
echo	in drive A:.
pause
if exist a:setup.lbl goto hvesetupdisk
echo	The disk in drive A: does not appear to be a copy of the
echo	Windows Setup disk.
pause
goto hvegetsetupdisk

:hvesetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist a:emm.pc del a:emm.pc
if exist a:emm.at del a:emm.at
if exist a:attdc.drv del a:attdc.drv
if exist a:attdeb.drv del a:attdeb.drv
if exist a:egahires.drv del a:egahires.drv
if exist a:egalores.drv del a:egalores.drv
if exist a:egahibw.drv del a:egahibw.drv
echo	Copying VEGA drivers to the Setup disk . . .
copy c:vega640.drv a:
copy c:vega752.drv a:
if not exist a:vega640.drv goto abortcopyfailed
if not exist a:vega752.drv goto abortcopyfailed
del c:vega640.drv
del c:vega752.drv

:hvegetbuilddisk
cls
echo	Please insert a copy of the Windows Build disk
echo	in drive A:.
pause
if exist a:build.lbl goto hvebuilddisk
echo	The disk in drive A does not appear to be a copy of the
echo	Windows Build disk.
pause
goto hvegetbuilddisk

:hvebuilddisk
echo	Making room on the build disk for the new files . . .
if exist a:att*.* del a:att*.*
if exist a:egahires.* del a:egahires.*
if exist a:egahibw.* del a:egahibw.*
echo	Copying VEGA files to the build disk . . .
copy c:vega640.lgo a:
copy c:vega752.lgo a:
copy c:vega640.grb a:
copy c:vega752.grb a:
if not exist a:vega640.lgo goto abortcopyfailed
if not exist a:vega752.lgo goto abortcopyfailed
if not exist a:vega640.grb goto abortcopyfailed
if not exist a:vega752.grb goto abortcopyfailed
del c:vega640.lgo
del c:vega752.lgo
del c:vega640.grb
del c:vega752.grb
goto pointingdevice

:wyinstall
cls
echo	This procedure file copies the files required to set up Windows
echo	for the Wyse WY-700 display onto copies of the Windows Setup and 
echo	Build disks.
echo	You should make copies of your Setup and Build disks, and put
echo	the originals in a safe place.  Do not use the original disks
echo	in this procedure.  Work only with your duplicate copies.
pause

:wystart
ync /c "yn" "Does your machine have two floppy disk drives?"
if errorlevel 1 goto hwystart
cls
echo	Please insert Driver Library Disk #1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause
if exist a:drvlib1.lbl goto wydrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto wystart

cls
echo	Please insert Driver Library Disk 1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause
if exist a:drvlib1.lbl goto wydrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto wystart

:wydrvlibdisk
if exist b:setup.lbl goto wysetupdisk
echo	The disk in drive B does not appear to be the Windows Setup disk.  
pause
goto wystart

:wysetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist b:emm.pc del b:emm.pc
if exist b:emm.at del b:emm.at
if exist b:attdc.drv del b:attdc.drv
if exist b:attdeb.drv del b:attdeb.drv
echo	Copying Wyse driver to the Setup disk . . .
copy a:wy700.drv b:
if not exist b:wy700.drv goto abortcopyfailed

:wyneedbuild
pause
cls
echo	Please insert your duplicate of the Windows build disk in drive B.
pause
if exist b:build.lbl goto wybuilddisk
echo	The disk in drive B does not appear to be the Windows build disk.  
goto wyneedbuild

:wybuilddisk
echo	Making room on the build disk for the new files . . .
if exist b:att*.* del b:att*.*
echo	Copying Wyse files to the build disk . . .
copy a:wy700.lgo b:
copy a:wy700.grb b:
if not exist b:wy700.lgo goto abortcopyfailed
if not exist b:wy700.grb goto abortcopyfailed
goto pointingdevice

:hwystart
cls
echo	Please insert Driver Library Disk #1 into drive A.
pause
if exist a:drvlib1.lbl goto hwydrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto hwystart

:hwydrvlibdisk
echo	Copying Wyse files to the hard disk . . .
copy a:ync.exe c:
copy a:wy700.drv c:
copy a:wy700.lgo c:
copy a:wy700.grb c:
if not exist c:wy700.drv goto abortcopyfailed
if not exist c:wy700.lgo goto abortcopyfailed
if not exist c:wy700.grb goto abortcopyfailed
pause

:hwygetsetupdisk
cls
echo	Please insert a copy of the Windows Setup disk
echo	in drive A:.
pause
if exist a:setup.lbl goto hwysetupdisk
echo	The disk in drive A: does not appear to be a copy of the
echo	Windows Setup disk.
pause
goto hwygetsetupdisk

:hwysetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist a:emm.pc del a:emm.pc
if exist a:emm.at del a:emm.at
if exist a:attdc.drv del a:attdc.drv
if exist a:attdeb.drv del a:attdeb.drv
if exist a:egahires.drv del a:egahires.drv
if exist a:egalores.drv del a:egalores.drv
if exist a:egahibw.drv del a:egahibw.drv
echo	Copying Wyse driver to the Setup disk . . .
copy c:wy700.drv a:
if not exist a:wy700.drv goto abortcopyfailed
del c:wy700.drv

:hwygetbuilddisk
cls
echo	Please insert a copy of the Windows Build disk
echo	in drive A:.
pause
if exist a:build.lbl goto hwybuilddisk
echo	The disk in drive A does not appear to be a copy of the
echo	Windows Build disk.
pause
goto hwygetbuilddisk

:hwybuilddisk
echo	Making room on the build disk for the new files . . .
if exist a:att*.* del a:att*.*
if exist a:egahires.* del a:egahires.*
if exist a:egahibw.* del a:egahibw.*
echo	Copying Wyse files to the build disk . . .
copy c:wy700.lgo a:
copy c:wy700.grb a:
if not exist a:wy700.lgo goto abortcopyfailed
if not exist a:wy700.grb goto abortcopyfailed
del c:wy700.lgo
del c:wy700.grb
goto pointingdevice

:viinstall
cls
echo	This procedure file copies the files required to set up Windows
echo	for the Viking display onto copies of the Windows Setup and 
echo	Build disks.
echo	You should make copies of your Setup and Build disks, and put
echo	the originals in a safe place.  Do not use the original disks
echo	in this procedure.  Work only with your duplicate copies.
pause

:vistart
ync /c "yn" "Does your machine have two floppy disk drives?"
if errorlevel 1 goto hvistart
cls
echo	Please insert Driver Library Disk #1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause
if exist a:drvlib1.lbl goto vidrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto vistart

cls
echo	Please insert Driver Library Disk 1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause
if exist a:drvlib1.lbl goto vidrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto vistart

:vidrvlibdisk
if exist b:setup.lbl goto visetupdisk
echo	The disk in drive B does not appear to be the Windows Setup disk.  
pause
goto vistart

:visetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist b:emm.pc del b:emm.pc
if exist b:emm.at del b:emm.at
if exist b:attdc.drv del b:attdc.drv
if exist b:attdeb.drv del b:attdeb.drv
echo	Copying Viking driver to the Setup disk . . .
copy a:vikingi.drv b:
if not exist b:vikingi.drv goto abortcopyfailed
if exist b:hifonts.fon del b:hifonts.fon
if exist b:fonts400.fon del b:fonts400.fon
echo	Copying Viking font to Setup disk . . .
copy a:vikingi.fon b:hifonts.fon

:vineedbuild
pause
cls
echo	Please insert your duplicate of the Windows build disk in drive B.
pause
if exist b:build.lbl goto vibuilddisk
echo	The disk in drive B does not appear to be the Windows build disk.  
goto vineedbuild

:vibuilddisk
echo	Making room on the build disk for the new files . . .
if exist b:att*.* del b:att*.*
echo	Copying Viking files to the build disk . . .
copy a:vikingi.lgo b:
copy a:vikingi.grb b:
if not exist b:vikingi.lgo goto abortcopyfailed
if not exist b:vikingi.grb goto abortcopyfailed
goto pointingdevice

:hvistart
cls
echo	Please insert Driver Library Disk #1 into drive A.
pause
if exist a:drvlib1.lbl goto hvidrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto hvistart

:hvidrvlibdisk
echo	Copying Viking files to the hard disk . . .
copy a:ync.exe c:
copy a:vikingi.drv c:
copy a:vikingi.lgo c:
copy a:vikingi.grb c:
copy a:vikingi.fon c:
if not exist c:vikingi.drv goto abortcopyfailed
if not exist c:vikingi.lgo goto abortcopyfailed
if not exist c:vikingi.grb goto abortcopyfailed
if not exist c:vikingi.fon goto abortcopyfailed
pause

:hvigetsetupdisk
cls
echo	Please insert a copy of the Windows Setup disk
echo	in drive A:.
pause
if exist a:setup.lbl goto hvisetupdisk
echo	The disk in drive A: does not appear to be a copy of the
echo	Windows Setup disk.
pause
goto hvigetsetupdisk

:hvisetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist a:emm.pc del a:emm.pc
if exist a:emm.at del a:emm.at
if exist a:attdc.drv del a:attdc.drv
if exist a:attdeb.drv del a:attdeb.drv
if exist a:egahires.drv del a:egahires.drv
if exist a:egalores.drv del a:egalores.drv
if exist a:egahibw.drv del a:egahibw.drv
if exist a:hifonts.fon del a:hifonts.fon
if exist a:fonts400.fon del a:fonts400.fon
echo	Copying Viking files to the Setup disk . . .
copy c:vikingi.drv a:
copy c:vikingi.fon a:hifonts.fon
if not exist a:vikingi.drv goto abortcopyfailed
if not exist a:hifonts.fon goto abortcopyfailed
del c:vikingi.drv
del c:vikingi.fon

:hvigetbuilddisk
cls
echo	Please insert a copy of the Windows Build disk
echo	in drive A:.
pause
if exist a:build.lbl goto hvibuilddisk
echo	The disk in drive A does not appear to be a copy of the
echo	Windows Build disk.
pause
goto hvigetbuilddisk

:hvibuilddisk
echo	Making room on the build disk for the new files . . .
if exist a:att*.* del a:att*.*
if exist a:egahires.* del a:egahires.*
if exist a:egahibw.* del a:egahibw.*
echo	Copying Viking files to the build disk . . .
copy c:vikingi.lgo a:
copy c:vikingi.grb a:
if not exist a:vikingi.lgo goto abortcopyfailed
if not exist a:vikingi.grb goto abortcopyfailed
del c:vikingi.lgo
del c:vikingi.grb
goto pointingdevice

:pointingdevice
pause
cls
echo	Volume 1 contains drivers for the following pointing devices:
echo			1)	FTG Lightpen
echo			2)	Maynard Mouse
echo			3)	Mouse Systems
echo	.
ync /c "yn"	Do you wish to install one of these pointing device drivers?
if errorlevel 1 goto done
echo	.
ync /c "123"	Which pointing device driver do you wish to install?
if errorlevel 2 goto msinstall
if errorlevel 1 goto mainstall
if errorlevel 0 goto ftinstall
goto done

:ftinstall
cls
echo	This procedure transfers the files required to set up Windows
echo	for the FTG Lightpen onto a copy of the Windows Setup disk. 
echo	You should have already made a copy of your Setup disk, and 
echo	put the original in a safe place.  Do not use the original disk
echo	in this procedure.  Work only with your duplicate copy.
echo	If you have already installed a display driver from the Driver
echo	Library, use the Setup disk you created during the display
echo	driver installation process.

:ftstart
ync /c "yn" "Does your machine have two floppy disk drives?"
if errorlevel 1 goto hftstart
cls
echo	Please insert Driver Library Disk #1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause
if exist a:drvlib1.lbl goto ftdrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto ftstart

pause
cls
echo	Please insert Driver Library Disk 1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause

if exist a:drvlib1.lbl goto ftdrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
goto ftstart

:ftdrvlibdisk
if exist b:setup.lbl goto ftsetupdisk
echo	The disk in drive B does not appear to be the Windows Setup disk.  
goto ftstart

:ftsetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist b:attmouse.drv del b:attmouse.drv
if exist b:joymouse.drv del b:joymouse.drv
if exist b:lmouse.drv del b:lmouse.drv
if exist b:lpc.drv del b:lpc.drv
if exist b:mouse.drv del b:mouse.drv
if exist b:msmouse1.drv del b:msmouse1.drv
if exist b:msmouse2.drv del b:msmouse2.drv
if exist b:ftg.drv del b:ftg.drv
echo	Copying FTG Lightpen driver to the Setup disk . . .
copy a:ftg.drv b:
if not exist b:ftg.drv goto abortcopyfailed
goto done

:hftstart
cls
echo	Please insert Driver Library Disk #1 into drive A.
pause
if exist a:drvlib1.lbl goto hftdrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto hftstart

:hftdrvlibdisk
echo	Copying FTG files to the hard disk . . .
copy a:ync.exe c:
copy a:ftg.drv c:
if not exist c:ftg.drv goto abortcopyfailed
pause

:hftgetsetupdisk
cls
echo	Please insert a copy of the Windows Setup disk
echo	in drive A:.
pause
if exist a:setup.lbl goto hftsetupdisk
echo	The disk in drive A: does not appear to be a copy of the
echo	Windows Setup disk.
pause
goto hftgetsetupdisk

:hftsetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist a:attmouse.drv del a:attmouse.drv
if exist a:joymouse.drv del a:joymouse.drv
if exist a:lmouse.drv del a:lmouse.drv
if exist a:lpc.drv del a:lpc.drv
if exist a:mouse.drv del a:mouse.drv
if exist a:msmouse1.drv del a:msmouse1.drv
if exist a:msmouse2.drv del a:msmouse2.drv
if exist a:ftg.drv del a:ftg.drv
echo	Copying FTG driver to the Setup disk . . .
copy c:ftg.drv a:
if not exist a:ftg.drv goto abortcopyfailed
del c:ftg.drv
goto done

:mainstall
cls
echo	This procedure transfers the files required to set up Windows
echo	for the Maynard Mouse onto a copy of the Windows Setup disk. 
echo	You should have already made a copy of your Setup disk, and 
echo	put the original in a safe place.  Do not use the original disk
echo	in this procedure.  Work only with your duplicate copy.
echo	If you have already installed a display driver from the Driver
echo	Library, use the Setup disk you created during the display
echo	driver installation process.

:mastart
ync /c "yn" "Does your machine have two floppy disk drives?"
if errorlevel 1 goto hmastart
cls
echo	Please insert Driver Library Disk #1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause
if exist a:drvlib1.lbl goto madrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto mastart

pause
cls
echo	Please insert Driver Library Disk 1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause

if exist a:drvlib1.lbl goto madrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
goto mastart

:madrvlibdisk
if exist b:setup.lbl goto masetupdisk
echo	The disk in drive B does not appear to be the Windows Setup disk.  
goto mastart

:masetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist b:attmouse.drv del b:attmouse.drv
if exist b:joymouse.drv del b:joymouse.drv
if exist b:lmouse.drv del b:lmouse.drv
if exist b:lpc.drv del b:lpc.drv
if exist b:mouse.drv del b:mouse.drv
if exist b:msmouse1.drv del b:msmouse1.drv
if exist b:msmouse2.drv del b:msmouse2.drv
if exist b:ftg.drv del b:ftg.drv
echo	Copying Maynard Mouse drivers to the Setup disk . . .
copy a:memouse1.drv b:
copy a:memouse2.drv b:
copy a:memouse3.drv b:
if not exist b:memouse1.drv goto abortcopyfailed
if not exist b:memouse2.drv goto abortcopyfailed
if not exist b:memouse3.drv goto abortcopyfailed
goto done

:hmastart
cls
echo	Please insert Driver Library Disk #1 into drive A.
pause
if exist a:drvlib1.lbl goto hmadrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto hmastart

:hmadrvlibdisk
echo	Copying Maynard files to the hard disk . . .
copy a:ync.exe c:
copy a:memouse1.drv c:
copy a:memouse2.drv c:
copy a:memouse3.drv c:
if not exist c:memouse1.drv goto abortcopyfailed
if not exist c:memouse2.drv goto abortcopyfailed
if not exist c:memouse3.drv goto abortcopyfailed
pause

:hmagetsetupdisk
cls
echo	Please insert a copy of the Windows Setup disk
echo	in drive A:.
pause
if exist a:setup.lbl goto hmasetupdisk
echo	The disk in drive A: does not appear to be a copy of the
echo	Windows Setup disk.
pause
goto hmagetsetupdisk

:hmasetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist a:attmouse.drv del a:attmouse.drv
if exist a:joymouse.drv del a:joymouse.drv
if exist a:lmouse.drv del a:lmouse.drv
if exist a:lpc.drv del a:lpc.drv
if exist a:mouse.drv del a:mouse.drv
if exist a:msmouse1.drv del a:msmouse1.drv
if exist a:msmouse2.drv del a:msmouse2.drv
if exist a:ftg.drv del a:ftg.drv
echo	Copying Maynard Mouse drivers to the Setup disk . . .
copy c:memouse1.drv a:
copy c:memouse2.drv a:
copy c:memouse3.drv a:
if not exist a:memouse1.drv goto abortcopyfailed
if not exist a:memouse2.drv goto abortcopyfailed
if not exist a:memouse3.drv goto abortcopyfailed
del c:memouse1.drv
del c:memouse2.drv
del c:memouse3.drv
goto done

:msinstall
cls
echo	This procedure transfers the files required to set up Windows
echo	for the Mouse Systems mouse onto a copy of the Windows Setup disk. 
echo	You should have already made a copy of your Setup disk, and 
echo	put the original in a safe place.  Do not use the original disk
echo	in this procedure.  Work only with your duplicate copy.
echo	If you have already installed a display driver from the Driver
echo	Library, use the Setup disk you created during the display
echo	driver installation process.

:msstart
ync /c "yn" "Does your machine have two floppy disk drives?"
if errorlevel 1 goto hmsstart
cls
echo	Please insert Driver Library Disk #1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause
if exist a:drvlib1.lbl goto msdrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto msstart

pause
cls
echo	Please insert Driver Library Disk 1 into drive A, and your 
echo	duplicate of the Windows Setup disk in drive B.
pause

if exist a:drvlib1.lbl goto msdrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
goto msstart

:msdrvlibdisk
if exist b:setup.lbl goto mssetupdisk
echo	The disk in drive B does not appear to be the Windows Setup disk.  
goto msstart

:mssetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist b:attmouse.drv del b:attmouse.drv
if exist b:joymouse.drv del b:joymouse.drv
if exist b:lmouse.drv del b:lmouse.drv
if exist b:lpc.drv del b:lpc.drv
if exist b:mouse.drv del b:mouse.drv
if exist b:msmouse1.drv del b:msmouse1.drv
if exist b:msmouse2.drv del b:msmouse2.drv
if exist b:ftg.drv del b:ftg.drv
echo	Copying Mouse Systems mouse drivers to the Setup disk . . .
copy a:msmousc1.drv b:
copy a:msmousc2.drv b:
if not exist b:msmousc1.drv goto abortcopyfailed
if not exist b:msmousc2.drv goto abortcopyfailed
goto done

:hmsstart
cls
echo	Please insert Driver Library Disk #1 into drive A.
pause
if exist a:drvlib1.lbl goto hmsdrvlibdisk
echo	The disk in drive A does not appear to be Windows Driver
echo	Library Disk #1.
pause
goto hmsstart

:hmsdrvlibdisk
echo	Copying Mouse Systems files to the hard disk . . .
copy a:ync.exe c:
copy a:msmousc1.drv c:
copy a:msmousc2.drv c:
if not exist c:msmousc1.drv goto abortcopyfailed
if not exist c:msmousc2.drv goto abortcopyfailed
pause

:hmsgetsetupdisk
cls
echo	Please insert a copy of the Windows Setup disk
echo	in drive A:.
pause
if exist a:setup.lbl goto hmssetupdisk
echo	The disk in drive A: does not appear to be a copy of the
echo	Windows Setup disk.
pause
goto hmsgetsetupdisk

:hmssetupdisk
echo	Making room on the Setup disk for the new files . . .
if exist a:attmouse.drv del a:attmouse.drv
if exist a:joymouse.drv del a:joymouse.drv
if exist a:lmouse.drv del a:lmouse.drv
if exist a:lpc.drv del a:lpc.drv
if exist a:mouse.drv del a:mouse.drv
if exist a:msmouse1.drv del a:msmouse1.drv
if exist a:msmouse2.drv del a:msmouse2.drv
if exist a:ftg.drv del a:ftg.drv
echo	Copying Mouse Systems Mouse drivers to the Setup disk . . .
copy c:msmousc1.drv a:
copy c:msmousc2.drv a:
if not exist a:msmousc1.drv goto abortcopyfailed
if not exist a:msmousc2.drv goto abortcopyfailed
del c:msmousc1.drv
del c:msmousc2.drv
goto done

:abortnotcopies
cls
echo	Please make copies of your Windows Setup and Build disks, and work
echo	only with your copies.  This installation procedure deletes some of
echo	the files from the copies to make room for the new files.  You may
echo	need the deleted files later, so MAKE COPIES NOW. 
goto end

:abortcopyfailed
cls
echo	Some files were not copied successfully.  Please make sure you are
echo	working with exact duplicates of the Windows Setup and Build disks,
echo	and re-run this installation batch file.
goto end

:done
cls
echo	Installation of the selected drivers is now complete.  You
echo	may now use your copies of the Windows Setup and Build disks 
echo	to set up Windows on your system.
echo	.
echo	To do so, insert the Setup disk in drive A, change to drive A, 
echo	and type "setup" at the DOS prompt.
:end
