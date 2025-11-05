all: W1SETVER.EXE

W1SETVER.EXE: w1setver.c $(SRC)/include/16bit/patchress_dos.lib
	$(Q)$(WATC) $(WATCFLAGS) -fe=W1SETVER.EXE w1setver.c "$(SRC)/include/16bit/patchress_dos.lib"
	@echo Successfully built W1SETVER.EXE

clean:
	$(Q)rm -f W1SETVER.EXE *.obj