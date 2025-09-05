#
# Makefile for 16-Bit MS-DOS Patchress Program
#

all: main.exe

main.exe: main.c
	$(Q)$(WATC) $(WATCFLAGS) -fe=main.exe main.c "$(SRC)/include/16bit/patchress_dos.lib"
	@echo Successfully built 16-bit app