

                  <LG CD-ROM DRIVE Installation Manual>

============================CONTENT===========================================
                1. DOS & Win 3.xx         2. Win 95

                3. Windows NT             4. Solaris

                5. OS/2                   6. Linux
==============================================================================

 1. Installation under the DOS & Win 3.xx

 1)  Turn off your PC and connect the CD-ROM DRIVE to the PC.

     1.1 Adding the CD-ROM drive to a configuration with one IDE Hard Disk
         Set LG CD-ROM drive to SL(Slave mode) by setting a jumper
         on the middle side. The Hard Disk is set to IDE Master mode.

     1.2 CD-ROM only connection to IDE card or Secondary IDE Port on 
	 the PC Motherboard.
         Set the CD-ROM drive to MA (Master mode).
       	 (refer to the Owner's manual)

 2)  Turn the PC on.
 3)  Insert INSTALL DISK to the 3.5-inch driver.
 4)  Type 'install' on the 3.5-INCH DRIVER.
 5)  Check the directory to install. (DEFUALT C:\CDROM)
 6)  After completion of the installation, hit Enter.
 7)  Reboot the PC.
 8)  If the device driver installs successfully but the CD-ROM DRIVE 
	can't be accessed, you check the following
     	in CONFIG.SYS or AUTOEXEC.BAT.
     	
	CONFIG.SYS FILE:

        LASTDRIVE=Z

        DEVICE=C:\CDROM\GSCDROM.SYS /D:MSCD000

        AUTOEXEC.BAT FILE:

        C:\CDROM\MSCDEX /D:MSCD000

 9)  If the CD-ROM DRIVE can't be accessed continuously in MS-DOS or PC-DOS,
     	recheck the connection of P.C and CD-ROM.
 10) If the CD-ROM DRIVE can't be accessed continuously in Win3.xx,
     	recheck the following:

    10-1)  The 32BITDISKACCESS and VIRTUALHDIRQ parameter in the
           Windows SYSTEM.INI file should be set to OFF.

    10-2)  HOW TO MODIFY SYSTEM.INI:
           Using edit.exe, users can edit the SYSTEM.INI file in
           the Windows directory :

           SYSTEM.INI FILE :

           [386ENH]
           VIRTUALHDIRQ=OFF
           32bitDiskAccess=OFF

       	   (refer to the Owner's manual  )

 =============================================================================

 2.  Installation under the  Win 95

 1)  Turn off your PC and Connect CD-ROM DRIVE to the PC.

     1.1 Adding the CD-ROM drive to a configuration with one IDE Hard Disk
         Set LG CD-ROM drive to SL (Slave mode) by setting a jumper
         on the middle side. The Hard Disk is set to IDE Master mode.

     1.2 CD-ROM only connection to IDE card or Secondary IDE Port on 
	 the PC Motherboard.
         Set CD-ROM drive to MA (Master mode).
         (refer to INSTALLATION UNDER DOS AND WIN3.XX)

 2)  Turn the PC on.

 3)  Under WIN 95, the LG CD-ROM DRIVE is automatically found
     by the PnP FUNCTION because LG CD-ROM DRIVE works on 
     Win95's DIVEICE DRIVER under WIN95,

 4)  If you want to use under the COMMAND PROMPT MODE of WIN95,
     the LG CD-ROM DRIVE should be installed from the INSTALL DISK.
     => Insert the install disk into the floppy drive and type 'INSTALL'.
     => (refer to the Owner's manual  )

 9)  If the CD-ROM DRIVE can't use the auto-play fuction
     for Win95 CD or an audio CD, check the following:

     9-1) If LG CD-ROM DRIVE isn't listed in device manager, but the
          LG CD-ROM works on DOS device driver or system was infected
          by some virus.
          First check the virus. 
	  Second remove "c:\cdrom\mscdex /d:mscd000" in autoexec.bat.

==============================================================================

3. Windows NT Workstation Operating System (Version 3.5 or 4.0)Installation

   H/W  Requirements For Windows NT

  -32 bit processor, 386(25 MHZ) or above pentium PC.
  -High-Resolution Video display, VGA or above.
  -Mminium avaliable  HDD Capacity:  90 MB (OS File:70MB, SWAP FILE:20MB).
  -High-density Floppy Drive  for the  X86 processor
   (5.25inch floppy drive  is not supported )
  -Minimum 12MB RAM (16MB recommended)

   The 3 Types of Windows NT  Installation

 - From the CD-ROM  or Floppy diskette
 - From the Network
 - From the Computer Profile Setup

   INSTALLATION From the CD-ROM

 1. Insert DISK1 boot disk into the floppy drive & the CD-ROM NT DISC
    into the CD-ROM DRIVE
 2. Reboot the Computer and follow the instructions on the screen.
 3. There are 2 types of Windows NT set-up, Text mode and Graphic mode setup.

    Text Mode Setup

 1. INSTALLATION starts as soon as PC is rebooted, the menu screen appears.

    F1 Key: To learn more information  about  the NT Installation ,
    Enter Key: To set up NT now.
    R Key: To repair the damaged NT version.
    F3: To quit set-up without installing the NT
    * Choose the option "SET UP NT now" by pressing the Enter Key!

 2.The next scene asks "setup methods": Express setup or custom setup.

   Choose the custom installation in the cases of using the new HDD
   or now O/S. The following explains the customer installation.

 3. Enter Key: detecting the mass storage devices in your computer.
    S Key: skipping the process of detecting the mass storage device.

 4. The CD-ROM is found if the screen shows the message  
    "found:IDE CD-ROM (ATAPI 1.2)/Dual-Chanel PCI IDE
    while loading the device driver.

    S Key: To add CD-ROM Driver, SCSI Adapter, or other disc controller,
      etc. to the system, press "S Key".

    Enter Key: To avoid adding anything to the system, press 'ENTER'.
    Press 'ENTER' because the LG CD-ROM DRIVE has no driver for the Win NT
    but only for DOS.

    The Device Driver of the LG CD-ROM DRIVE supplied for DOS is not found.

 5.  The next scene asks "What media to install WIN NT from"

   5-1) Press 'ENTER' to install from the CD-ROM
   5-2) Press the 'A' key to install from the 3.5-inch disk drive (drive A:)
        (Then press the 'ENTER'.)

 6.The next scene asks  "What kind of keyboard does the customer use?"
  	(We choose the 101 Key code.)

 7.The next scene shows the configuration of H/W & S/W of the PC .
   In order to change anything, use the 'Direction Key' or 
   choose NO change.

 8.The next scene shows the space for the existing partition
   and the new partition. If the HDD is divided into several partitions,
   move to the partition where WIN NT is installed using the direction key.
   If WIN NT is installed on the entire HDD, press ENTER.
   If you want to make a partition, press 'C'.
   Press 'A' to delete the partition highlightened.

 9.The next scene asks what partition you want for Windows NT, FAT or NTFS.
   (*  Select the NTFS file system.)

10. Then the next scene shows the process of the formatting the partition.

11. After the format, the next scene asks the location of the HDD for
    WIN NT to be installed.
    Usually, we install to the " \winnt35" directory.

12 . The next scene shows the process of the examinating
     the HDD for corruption. Press ENTER to check the HDD with detail.
     press 'ESC' to check the HDD basically.
     We recommend choosing ENTER and performing an exhaustive 
     secondary examination.

13.  All the files are copied to the HDD after checking,
     and at this point, the CD-ROM works.

14.  Reboot the PC with the floppy disk drive empty.
     Then 'the Graphic mode setup' starts .

     Graphic Mode Set Up

15) After rebooting the PC, record the user name and the company.

16) Record the Product ID.

17) Record the Computer Name of the PC.

18) Choose the language: choose English (American).

19) Choose the Network, Printers, Applications, and their Settings.
      Choose all the components in the optional components box.

20) Then install NT to the HDD at this point.
    If CD-ROM Drive cannot find the CD, then the ERROR message appears.

21)  Record the Password of the Administrator.

22)  Record the Local Account Username & Password.

23)  Choose the Virtual Memory (usually 50 MB)

24)  Install the S/W.

25)  Set the time and date.

26)  Set the 'DISPLAY' and choose whether to make
     an 'emergency recovery disc' or not.

     Reboot the PC, then NT starts.

=====================================================================================================================

4. The Installation  Procedure of the Solaris x86  2.4 

   Hardware Requirements

   Processor requirements
 	Recommend  CPU=486DX above
	Minium     386 with 387 coprocessor at 33 MHZ. 

   Memory Requirements at least 16MB of RAM

   Supported Disks & Buses
	Supported Disk Drives 	:SCSI, IDE
	Buses  			:ISA, EISA, MCA, PCI, VLB

   Hard Disk Capacity
  	Minimum 200MB above
	300MB for a full installation

   Additional Supported Peripherals.
	SCSI CD-ROM
	SCSI tape drives
	SoundBlaster Pro audio cards
	Network adapters
	Graphical Input Devices
	High-performance, high-resolution super VGA color display adapters

   Operating Environments
            * Boot Diskette
            * CD-ROM
==========================================================================================
  

   5. OS/2 INSTALLATION GUIDE

       TO  install OS/2 using the EASY installation method, follow these steps.

       1. If your computer is on, choose all running.

       2. Insert the installation Diskette A. If you install from a CD,
          also insert the OS/2 disc into the CD-ROM drive.

       3. Turn you computer ON. If your computer is already on, press Ctrl+Alt+Del
          to restart it. Then the IBM logo will display.

       4. Remove the installation Diskette from drive A and insert diskette 1.   
	  Then press ENTER.
          As files are loaded into memory, you will see message asking you to wait,
          at this place to choose the EASY installation. If you choose the advanced 
          installation, you have to use partition to format.

       5. Use the arrow keys on your keyboard to higlight EASY installation.
          Then press ENTER.

       6. Follow the instruction on the screen. If you install from
          diskette, you will be asked to remove and insert diskettes as the 
          intallation progresses. If you install from a CD, you will not see 
          any messages to remove diskettes.

           After diskette 6, you will be asked to reinsert the installation diskette  
           and then reinsert diskette 1. Follow the instruction on the screen. After 
           you remove diskette 1 and press ENTER, you see the OS/2 logo screen, followed 
           by the system configuration screen.

       7. The system configuration screen shows your country configuration
          and the hardware devices that the installation program detected on 
          your system. Check the choices on the screen to be sure they are correct.

          If any of the hardware listed on the screen is incorrect,
          use the mouse to click on the icon (the small picture) next to the device name .

          A screen will appear where you can indicate the correct information
          about your hardware device. If you are unsure the about the hardware
          you are using, refer to documentation that came with it.

          Follow the instructions on each screen. Click on HELP if you need more
          information about any screen you see.

          If the information on the System Configuration screen is correct,
          click on OK .

          At the CD-ROM choosing option, we recommend selecting  "nonlisted CD-ROM 
	  or OTHER option" for the CD-ROM of LG (GoldStar)

          A special note about Super VGA displays: 

		During an EASY installation, the installation program automatically 
	        provides VGA support for your display, even if you have a Super VGA
		(SVGA) display. If you want to upgrade to SVGA support after you 
		have installed OS/2,  use the Selective Install object in the system 
		Setup folder to do so.

     8. When you select system default printer, windows will appear. Use 
	the arrow keys or your mouse to highlight the name of your printer
	in the list of printer names, then indicate the port to which your 
	printer is attached.

     -  If your printer is connected to a parallel port (the connector on the PCend of
        the printer cable has pins ), click on the LPT1, LPT2, or LPT3 button.
        Then press ENTER.

     -  If your printer is connected to a serial port, click on the COM1, COM2, 
	COM3, or COM4 button. Then press ENTER.

        If you do not have a printer attached to your computer, select Do Not Insatall
        Default Printer and press ENTER or click OK.

     9. If you received a warning message at the beginnig of the installation 
	program telling you that you did not have enough free disk space to 
	install OS/2, but you decided to continue with the installation anyway, 
	you will see the OS/2 Setup and installation screen. Go to Step 10.

        If you did not receive a warning message at the beginning of the 
	installation program, go to step 11.

    10. The OS/2 setup and installation screen let  you select the software 
	features you want to install. you will notice that some features have 
	a check mark next to them, which means they are selected for installation.
        The amount of hard disk space required for each feature is shown to 
	the right of the  feature.   

	Follow these steps:

        a.   Click on options you do not want to install to deselect them. 
		By deselecting features, you will save hard disk space.
        b.  If a MORE button appears to the right of an option, click on 	
		the button to see additional items  you can select or deselect.
        c.  Click on install when you have made all your selections.

    11. Follow the instructions that appear on each screen. You will be asked to 
	remove and insert diskettes, including one or more printer driver diskettes.
        After inserting each diskette, click  OK or press ENTER.

    12. When prompted to do so, insert the display driver diskettes that 
	are part of the OS/2  installation.

    13. If you installed OS/2 Warp, a screen appears asking you to insert your 
	windows diskettes. (If windows was preinstalled on your computer when 
	you bought it or if you are installing OS/2 Warp with WIN-OS/2, you can 
	skip this step and go to step 15):

       - If you installed Windows from diskettes, follow these steps:

         a. Remove the OS/2 diskette that is currently in Drive A.
         b. Insert the requested Windows diskette and press ENTER.
         c. Continue removing and inserting your Windows diskettes as requested.

       - If you installed Windows from a CD , follow these steps:

         a. Remove the OS/2 CD from the CD-ROM drive.
         b. Insert the Windows CD into the CD-ROM drive and press ENTER.
         c. When you prompted for the location of the Windows files on 
		the CD, type the drive letter and directory name in the 
		field provided, for example:  e:\winsetup
            	where e: is the letter of the CD-ROM drive, 
		and where \winsetup is the directory that contains the Windows files.

    14. When prompted to do so, remove the Windows diskette or CD and press ENTER.

    15. When the OS/2 installation is completed, you will be prompted to 
	shut down and restart your computer. Remove any diskette that is 
	in drive A, and then click  OK or press ENTER.

    16. When your computer restarts, the OS/2 Tutorial will appear on 
	your screen. View the tutorial to learn about the features of 
	OS/2 and how to use your Desktop. The tutorial also provides 
	information to help you make the transition from DOS and 
	Windows to OS/2.

        For more help on using the operation system, you can access the 
	on-line help system.  Press F1 anytime to get help, or if you 
	see a Help button at the bottom of screen, you can click on it 
	to get more information about that screen




==========================================================================================================================================

   6.  Linux   INSTALLATION

   1. Under the DOS mode, make the "Boot Kernel"  
      D:\Bootdsks.144>RAWRITE BARE(BARE.I, BARE.GZ...) A:

   2. Make a "Root Image"    
      D:\Rootdsks>Rewrite Color (Color.I, Color.GZ) A:

   3. Reboot with the Boot Kernel Disk.

   4. Message    "Don't switch any disks yes! 
	This prompt is just for entering extra parameters.  
	If you don't need to enter any parameters.     
     	Hit Enter to continue.      
	Boot:_
     	==> Hit "ENTER", (You don't need any "Boot Option")

   5. Check whether the CD-ROM Drive is found.
      It's shown differently according to the connection method.    
      	Primary Slave -> hdb,      
	Secondary Master -> hdc      
	Secondary Slave -> hdd.

   6. "VFS : Insert root floppy disk to be loaded into ramdisk and press ENTER."  
      Insert "Root Image disk" and Press ENTER

   7. slackware login :      Type "root"

   8. Message  :  " To restart  the main installation, type setup.

   9. Run  'fdisk.'    
     	#fdisk.(Basically make the Linux native Area of about 200Mbyte and 
	Linux swap area of about 50Mbyte.) 
     	Activate Boot area.
     	Change the ID of the Linux swap area.
     	After saving, End.Fdisk command appears if you Enter L

   9.  Reboot with "Boot Kernel" inserted.     #shutdown -r now

  10.  Login with root. & run the setup.     #setup.

  11.  Move the cusor to the ADD SWAP and Hit Enter.    
       Activate Swap  space

  12.  After Activation of swap space.,
       Choose "YES" in the Continue with Installation  Dialog Box. 

  13.  Using this partition for Linux.     
       Press "OK" For the space to install on, choose the partition 
       activated as Boot space by fdisk.

  14.  Choose the format in the Format Partition dialog box, and capacity 4096 .

  15.  Choose "YES" in the continue box. 

  16.  Choose 5, "Install from CD-ROM" in the source media option.

  17.  Choose 7, "Most IDE-Interface CD-DRIVES from the slackware CD-ROM.

  18.  Choose scan in the "Select IDE Device"

  19.  Choose the slackware in the "Disk your installation method"

  20.  Choose "YES" in the Continue dialog box

  21.  Choose the necessary programs in the "SERIES Selection", and Press "OK"

  22.  Add necessary program from the "Custom Disk SET", and Press "OK". 

  23.  Choose "YES" in the Continue box.

  24.  Choose "NONE" in the Select prompting mode.

  25.  Choose the "YES" in the "Configure Your System" 

  26.  Choose "Continue" in the "Make bootdisk".

  27.  Choose the Modem, Mouse, Mouse port..

  28.  If necessary, choose options in the Lilo Install dialog.

  29.  Choose the Network, GPM, SENDMAIL, Time Zone.

  30.  Press "OK" in the Set up Complete.

  31.  Press EXIT and prompt window shows.

  32.  Reboot.

  33.  Run the Kernel compile if CD-ROM is not found when booting.* 
     - The END -


       Kernel Compile
       darkstar : /# cd/usr/src/linuxdarkstar : /usr/src/linux/# make mrproper
       darkstar : /usr/src/linux/#make config
       Change the configuration to the System.
       Select y where
           Lise new IDE driver for primary/secondary i/f (Config-Blk-DEV-IDE) [y]
       Select y where
           Include support for IDE/ATAPI CDROMS (CONFIG-DEV-IDECD) [n]
        darkstar : /usr/src/linux/# make depdarkstar : /usr/src/linux/# make clean
        darkstar : /usr/src/linux/# make zlmage <- If error occurred, Input " make only"
        darkstar : /usr/src/linux/# make zlilo





