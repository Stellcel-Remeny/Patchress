@echo off

REM Generates bootable ISO image
REM Windows batch version
REM Primitive

REM Important stuff!
REM ================
REM Outputs to: ..\ISO.iso
REM Input directory is FIXED to ..\BIN for now.

REM Expects:
REM    - ..\BIN folder    -> containing MultiPatcher output [plus add more stuff to add into iso image]
REM    - BOOT.IMG in BIN  -> Floppy image - contains BIOS boot code + Stuff for A:\ drive
REM
REM    - MKISOFS.EXE in directory of ISOGEN.BAT

REM switch to directory of b_tch script
cd /d "%~dp0"

REM Create bootable image.
mkisofs -o ..\ISO.iso -b BOOT.IMG -c boot.cat -R -D ..\BIN
