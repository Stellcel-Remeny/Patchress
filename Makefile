#
# Makefile for Patchress
# 31st August, 2025
#

# ---[ Variables ]--- #
Q			:= 
SRC			:= $(abspath source)
BIN			:= $(abspath bin)

WATCOM_DIR	:= /i/WATCOM/binnt
WATC		:= $(WATCOM_DIR)/wcl
WATCFLAGS	:= -bcl=dos -za99

ifeq ($(OS),Windows_NT)
    WATCFLAGS += -i="$(shell cygpath -w $(SRC))\include\16bit"
else
    WATCFLAGS += -i="$(SRC)/include/16bit"
endif

export Q SRC BIN WATC WATCFLAGS
export PATH := $(WATCOM_DIR):$(PATH)

all: init 16bit 32bit bundle

init:
	$(Q)export PATH=$(WATCOM_DIR):$$PATH

16bit:
	$(Q)$(MAKE) -C "$(SRC)/include/16bit"
	$(Q)$(MAKE) -C "$(SRC)/main/16BIT"

32bit:

bundle:
	$(Q)mkdir -p "$(BIN)" "$(BIN)/RES"
	$(Q)cp "$(SRC)/checker/Patcher.bat" "$(BIN)/Patcher.bat"
	$(Q)cp "$(SRC)/main/16BIT/main.exe" "$(BIN)/patchx16.exe"
	$(Q)cp -r "$(SRC)/resources/"* "$(BIN)/RES/"