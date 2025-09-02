#
# Makefile for Patchress
# 31st August, 2025
#

# ---[ Variables ]--- #
Q			:= 
SRC			:= source
BIN			:= bin

WATCOM_DIR	:= /i/WATCOM/binnt
WATC		:= $(WATCOM_DIR)/wcl
WATCFLAGS	:= -bcl=dos -za99

export Q SRC BIN WATC WATCFLAGS
export PATH := $(WATCOM_DIR):$(PATH)

all: init 16bit 32bit bundle

init:
	$(Q)export PATH=$(WATCOM_DIR):$$PATH

16bit:
	$(Q)$(MAKE) -C "$(SRC)/main/16BIT"

32bit:

bundle:
	$(Q)mkdir -p "$(BIN)"
	$(Q)cp "$(SRC)/checker/Patcher.bat" "$(BIN)/Patcher.bat"
	$(Q)cp "$(SRC)/main/16BIT/main.exe" "$(BIN)/patchx16.exe"