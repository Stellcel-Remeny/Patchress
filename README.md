# MultiPatcher
![MultiPatcher Logo](media/mpc_banner.png)


The MultiPatcher is a utility/collection of utilities & patches for Operating Systems ranging from MS-DOS to Microsoft Windows 11.

## Screenshots
![Patchress under MS-DOS](media/patchress_dos.gif)
![Patchress under Windows NT 4](media/patchress_nt4.png)
![Patchress under Windows 7](media/patchress_nt61.png)

## Architecture
MS-DOS uses a 16-bit application made using the OpenWatcom Compiler. Windows 95-ME and Windows NT 4 - Windows 2000 share a single application made using Visual Basic 6. Windows XP and Windows Vista+ uses an application made using Delphi.

In order to provide a seamless experience, 'Patcher.bat' was added. This batch file tries to automatically figure out whether you are running MS-DOS or Windows. If it detects that you are running MS-DOS, it launches 'patchx16.exe'. Otherwise, it launches 'patchx32.exe'.

Patchx32.exe is an application that is made using Visual Basic 6. This should be able to run on Windows 95+/NT4+. Here, it checks for your Windows version. If it detects Windows XP+, it launches the Delphi app (should be in RES/). Otherwise, it continues execution as normal.

The 'RES/' folder contains required files for Patchress to function properly. Inside 'RES/MODERN', it contains the Delphi application. The patches, utilities, etc. are located inside 'RES/ITEMS'. Each directory containing 'lfn.ini' shows up as a menu in the Patchress GUI, except if the directory contains 'info.ini'.

The 'info.ini' tells Patchress that it is an entry instead of a menu. Under '[MAIN]', it describes the name of the entry in 'NAME=', description in 'DESCRIPTION=', creator's name in 'AUTHOR=', version in 'VERSION=', and the main executable in 'EXEC='. Under the '[OS]' section, you can specify the Operating Systems it will run under. For this, refer OS.md

## Goals
The goal here is to make an independent and lightweight utility where the users can use it to launch other utilities. We don't want heavy applications like some Partition manager, but something like the Windows Update Blocker is welcomed.

## Compiling
If you are using Microsoft Windows, you must compile this utility from within a linux shell (like msys2). Then, in the root directory, run `make`. A copy of Patchress will be created in the `bin/` directory. The Watcom compiler must also be available in the system's PATH.

## Contributing
If you want to add anything that you think would make a great addition to this project, please send an email to remenycompany@gmail.com.

## Credits
For a list of Utilities included, please view CREDITS.TXT. Thank you.

# X-----X