

Microsoft Windows Device Driver Library 	
Volume 1 

This package contains the items required to load new or updated device drivers to your Microsoft Windows operating environment.   Check to make sure you have each of the following items before proceeding:

1.	Device Driver List (page 2 of this document)
2.	Installation Instructions (page 3 of this document)
3.	Screen and Pointing Device Driver Disk 1
4.	Screen and Pointing Device Driver Disk 2
5.	Printer Device Driver Disk

Read through this entire document before proceeding with the installation of new drivers.

Device Driver List

Printers
This package contains drivers supporting the following PRINTERS.  All printer drivers are found on the Printer Device Driver Disk.

AMT Color InkJet	
Epson LQ 1500
HP ColorPro	
HP ColorPro with GEC	
HP LaserJet	
HP LaserJet Plus	
HP QuietJet		
HP 2603	
HP 7475A Plotter	
HP 7550A Plotter	
IBM ColorPrinter	
IBM 3812 Page Printer	
Toshiba P351

Display Devices
This package contains drivers supporting the following DISPLAY DEVICES.  

Conographics ConoVision 1440 *	
Moniterm Viking I	
Sigma Color 400	
STB HT Chauffer *
STB Multi Res *	
Tseng EVA	
Video-7 Vega Deluxe with NEC Multisync Enhanced Color display	
Vermont Microsystems Inc. Image Manager 1024	
Wyse WY-700 High Resolution Display Adapter	

* Drivers for these devices are found on the Screen and Pointing Device Driver Disk 2.  Drivers for all other display devices are found on the Screen and Pointing Device Driver Disk 1.

Pointing Devices
This package contains drivers supporting the following POINTING DEVICES.  All pointing device drivers are found on the Screen and Pointing Device Driver Disk 2 .

FTG Data Systems Lightpen and PXL-350 Single Pixel Board	
Maynard Electronics Mouse		
Mouse Systems PC Mouse
	
Microsoft Windows Device Driver Library
Volume 1

Installation instructions


IMPORTANT: DO NOT ATTEMPT to go through the install procedure before you make backup copies of the Windows SETUP and BUILD disks. It is of the utmost importance to backup the Windows original SETUP and BUILD disks before continuing. Please do not attempt to start the installation procedure before reading the entire Installation instructions.

Installation instructions for Microsoft Windows Device Drivers:

This first volume of the Microsoft Windows Device Driver Library contains the following printer and screen drivers, distributed on three disks:

Contents of disk 1 (Screen and pointing device drivers):

File name		device supported

DRVLIB1.LBL		disk label

SIGMA4.DRV		Sigma Color 400
SIGMA4.GRB
SIGMA4.LGO
SIGMA8.DRV
SIGMA8.GRB
SIGMA8.LGO

TSENG.DRV		Tseng EVA
TSENG.GRB
TSENG.LGO

VEGA640.DRV		Video-7 VEGA Deluxe
VEGA640.GRB
VEGA640.LGO
VEGA752.DRV
VEGA752.GRB
VEGA752.LGO

WY700.DRV		Wyse WY-700
WY700.GRB
WY700.LGO

VIKINGI.DRV		Moniterm Viking I
VIKINGI.GRB
VIKINGI.LGO
VIKINGI.FON

IM1024.DRV		Vermont Microsystems Inc. Image Manager 1024
IM1024.GRB
IM1024.LGO
VMILO.FON

FTG.DRV		FTG Lightpen

MEMOUSE1.DRV	Maynard Electronics Mouse
MEMOUSE2.DRV
MEMOUSE3.DRV

MSMOUSC1.DRV	Mouse Systems PC Mouse
MSMOUSC2.DRV

INSTALL.BAT		Installation program
YNC.EXE

README.TXT		ASCII file of printed matter

Contents of disk 2 (Screen and pointing device drivers):

File name		device supported

DRVLIB2.LBL		Disk label

STBHT.DRV		STB HT Chauffeur
STBHT.GRB
STBHT.LGO

STBMR832.DRV		STB Multires
STBMR752.DRV
STBMR480.DRV
STBMR400.DRV
STBMR400.GRB
STBMR400.LGO
STBMR480.GRB
STBMR480.LGO
STBMR752.GRB
STBMR752.LGO
STBMR832.GRB
STBMR832.LGO

VISION.DRV		Conographics ConoVision 1440
VISION.GRB
VISION.LGO
VISION.FON

INSTALL.BAT		Installation program
YNC.EXE

README.TXT		ASCII file of printed matter


Contents of disk 3 (Printer drivers):

File name		device supported

DRVLIB3.LBL		Disk label

AMT.DRV		AMT Color Inkjet
COLORPRO.DRV	HP Color Pro
CPROGEC.DRV		HP Color Pro with GEC
HPLASER.DRV		HP LaserJet
HPLASERP.DRV		HP LaserJet Plus
HP2603.DRV		HP 2603
HP7475A.DRV		HP 7475A Plotter
HP7550A.DRV		HP 7550A Plotter
IBMCOLOR.DRV		IBM ColorPrinter
IBM3812.DRV		IBM 3812 Page Printer
LQ1500.DRV		Epson LQ 1500
QUIETJET.DRV		HP Quiet Jet
TOSHP351.DRV		Toshiba P351
COMM.DRV		Windows COMM driver for IBM 3812 printer
README.TXT		ASCII file of printed matter

To Install printer drivers:

Locate the printer of your choice on the list above. Use the Windows control panel to install the printer driver of your choice. Instructions for using the Windows Control Panel can be found in the Windows User's Guide portion of the Windows documentation. 

To install screen and pointing device drivers:

You need to do the following, in exact order:

1. Prepare a Backup copy of the Windows SETUP and BUILD disks. This MUST be step one:
2. Pick the disk containing the screen or pointing device driver of your choice. You do that by looking through the list provided above. We'll refer to this disk as the INSTALLATION disk.

On the INSTALLATION disk, you will find the program INSTALL.BAT. You will be using this program to prepare the BACKUP copies of the Windows SETUP and BUILD disks to Re-Install Windows with the screen or pointing device driver of your choice. 

To run the Install program you need to do the following:

3. If your PC is equipped with a hard disk, put the INSTALLATION disk in drive A: and type the following from the DOS prompt:
	COPY A:INSTALL.BAT  C:
	C:
	INSTALL

If you have a machine equipped with two floppy drives (no hard disk), put the INSTALLATION disk in drive A and type:
	A:
	INSTALL

In either of the above cases, once running, INSTALL.BAT will prompt you through a series of questions regarding which screen or pointing device you wish to add to your Windows SETUP and BUILD disk. Be sure you are using the backup copies of SETUP and BUILD disks. The Install program will erase some files from these disks to make room for new files associated with the new device. If you are using your original disks (and not backup copies), they will be permanently damaged.

4. Once you have completed the install procedure, go through the Windows SETUP procedure as outlined in your Microsoft Windows User's Guide. You will need to go through the entire setup process, using all your Windows disks to ensure proper installation of the new drivers. When the Setup process is completed, you will be ready to run Windows with the new device configuration.

Notes:

* If you are installing the IBM 3812 driver, you will also find on that disk a program called COMM.DRV. This COMM.DRV should replace the COMM.DRV program on the Backup copy of the Setup disk. This new COMM.DRV is needed for proper operation of the 3812 driver. After copying the new COMM.DRV to the backup copy of the Setup disk, use that copy to re-install Windows. 

* The FTG driver needs the latest driver from FTG to function properly. If you notice upon installation that your light pen is not working, or not working properly, please contact FTG for the latest copy of their software.

* The VMI driver must use the board with on-board ROM's version 2.11 or later. The version number is typed on the ROM. Please contact VMI for more information.

* If you are using the hard disk install procedure, INSTALL will create a temporary directory on your hard disk, and copy some files to it. The files and directory will be deleted and your hard disk cleaned up after the install procedure is finished. If your system crashed, or INSTALL interrupted prior to completion, please re-run the entire procedure to make sure your hard disk is restored to its original order.

* These device drivers may be copied freely to other licensed Microsoft Windows users disks.

