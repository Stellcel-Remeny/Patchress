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
	wlib -q -b $@ +$(OBJS)
	@echo "Library $@ created."

# Compile each .c to .obj
%.obj: %.c
	$(WATC) $(WATCFLAGS) -c $<

# Clean up
clean:
	rm -f $(OBJS) $(LIB)
