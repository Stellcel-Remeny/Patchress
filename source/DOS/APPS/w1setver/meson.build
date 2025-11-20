# You only need to edit source_file, output_file, and install_bin_dir
# 
# An appropriate INFO.INI file must accompany it. You must add this INI file to
# source/BASE/RES/<directory>/INFO.INi
#

# Edit these variables only.
source_file = 'W1SETVER.C'
output_file = 'W1SETVER.EXE'
install_bin_dir = bin_patches / 'W1SETVER'

# Stop right there.

sub_variables = declare_dependency(
  variables : {
    'source_file' : source_file,
    'output_file' :  output_file,
    'install_bin_dir' : install_bin_dir,
  }
)

# Make this installable
custom_target(
  output_file + '_DRIP',
  input: source_file,
  output: output_file,
  command: 'echo',
  build_by_default: true,
  build_always_stale: true,
  install: true,
  install_dir: install_bin_dir,
)