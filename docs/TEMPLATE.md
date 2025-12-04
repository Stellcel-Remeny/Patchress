
# TEMPLATE

When adding a new dos .C app, you must also add a meson.build file with the following code:

```meson
# Edit these variables only.
source_file = '<src_c_file>'
output_file = '<tcc_output_exe>'
install_bin_dir = bin_<patches/utils/drivers/cosmetics> / '<name>'

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
```

Then, replace:

- ```<src_c_file>``` with the name of your .C file,
- ```<tcc_output_exe>``` with the name of your generated .EXE file (will be always equal to the name as your .C file, but change extension to .EXE),
- ```<name>``` with the 8 character-long name of your app (must be same as the dos utility's src dir name)
