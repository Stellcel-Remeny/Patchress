#
# Makefile for Patchress
# 31st August, 2025
# 31st October, 2025

#
# Patchress Meson Build File
# 2023 - 2025 NTSP3:
## Patchress, MultiPatcher MPC, MultibootSystemEssentials MSE, NTPatcher, RealBoot
#
# 2025 Remeny
# Novem 5 2025
# GNU GPL v3
#

# ---[ Include ]--- #
include init_settings.in
include $(SCRIPTS)/scripts.mk

# ---[ Menuconfig ]--- #
export srctree := $(CURDIR)
include $(srctree)/make/Kbuild.include
export HOSTCC := $(CC)

config:
	$(Q)$(MAKE) $(build)=make/basic
	$(Q)$(MAKE) $(build)=make/kconfig $@

%config:
	echo $(CC) $(MSYSTEM)
	$(Q)$(MAKE) $(build)=make/basic
	$(Q)$(MAKE) $(build)=make/kconfig $@

clean:
	$(Q)rm -rf build/
	$(Q)find make -type f \( -name "*.o" -o -name "*.d" -o -name "fixdep" -o -name "mconf" \) -delete
