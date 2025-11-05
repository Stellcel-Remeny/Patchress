#
# Makefile for Patchress
# 31st August, 2025
# 31st October, 2025
#

# ---[ Include ]--- #
include init_settings.in
include $(SCRIPTS)/scripts.mk

# ---[ Menuconfig ]--- #
export srctree := $(CURDIR)
include $(srctree)/make/Kbuild.include
export HOSTCC := $(CC)

config:
	echo $(CC)
	$(Q)$(MAKE) $(build)=make/basic
	$(Q)$(MAKE) $(build)=make/kconfig $@

%config:
	$(Q)$(MAKE) $(build)=make/basic
	$(Q)$(MAKE) $(build)=make/kconfig $@