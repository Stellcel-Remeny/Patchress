@echo off

REM Generates bootable ISO image
REM Windows batch version
REM Primitive

REM Important stuff!
REM ================
REM Outputs to: ..\ISO.iso
REM Input directory is FIXED to ..\BIN for now.

REM Expects:
REM    - ..\BIN folder          -> containing MultiPatcher output [plus add more stuff to add into iso image]
REM    - BOOT.IMG in BIN        -> Floppy image - contains BIOS boot code + Stuff for A:\ drive
REM    - ISOLINUX loader in BIN
REM
REM    - XORRISO.EXE and its stuff in directory of ISOGEN.BAT

REM switch to directory of b_tch script
cd /d "%~dp0"

REM Create bootable image.
xorriso -as mkisofs ^
  -iso-level 3 ^
  -full-iso9660-filenames ^
  -volid MPC ^
  -eltorito-boot BOOT/isolinux.bin ^
  -eltorito-catalog boot.cat ^
  -no-emul-boot ^
  -boot-load-size 4 ^
  -boot-info-table ^
  -eltorito-alt-boot ^
  -e BOOT/efi.img ^
  -no-emul-boot ^
  -eltorito-platform efi ^
  -isohybrid-mbr isohdpfx.bin ^
  -isohybrid-gpt-basdat ^
  -o ..\ISO.iso ^
  ..\BIN
