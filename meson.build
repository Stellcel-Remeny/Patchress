# Patchress Meson Build File
# 2023 - 2025 NTSP3:
## Patchress, MultiPatcher MPC, MultibootSystemEssentials MSE, NTPatcher, RealBoot
#
# 2025 Remeny
# Novem 5 2025
# GNU GPL v3
#

project('Patchress',
    version : '0.3',
    default_options : ['warning_level=3'])

# Get directories from options
src_dos  = get_option('src_dos')
message('DOS Source directory: ' + src_dos)

# Compile DOS App
subdir(src_dos)

# Now is a good time to copy src_base
install_subdir(get_option('src_base'),
               install_dir: meson.project_source_root() / get_option('bin_dir'),
               strip_directory: true)