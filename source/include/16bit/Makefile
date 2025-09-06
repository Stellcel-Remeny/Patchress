# Static library Makefile

# ---[ Variables ]--- #
LIB       := patchress_dos.lib

# Automatically find all .c files in this folder
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.obj)

# ---[ Targets ]--- #
all: $(LIB)

# Build the static library
$(LIB): $(OBJS)
	$(Q)wlib -q -b $@ +$(OBJS)
	@echo "Library $@ created."

# Compile each .c to .obj
%.obj: %.c
	$(Q)$(WATC) $(WATCFLAGS) -c $<
	$(Q)rm -f "$(LIB)"

# Clean up
clean:
	rm -f $(OBJS) $(LIB)
