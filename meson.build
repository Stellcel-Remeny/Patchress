# Patchress Meson Build File
# 2023 - 2025 NTSP3:
## Patchress, MultiPatcher MPC, MultibootSystemEssentials MSE, NTPatcher, RealBoot
#
# 2025 Remeny
# Novem 5 2025
# GNU GPL v3
#

project('Patchress',
    version : '0.2',
    default_options : ['warning_level=3'])

# Get source directories from options
src_dos  = get_option('src_dos')
message('DOS Source directory: ' + src_dos)

# Compile DOS App
subdir(src_dos)