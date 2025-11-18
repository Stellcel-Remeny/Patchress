# Variables for directories
bin_patches = meson.project_source_root() / get_option('bin_dir') / 'RES' / 'PATCHES'
bin_utils = meson.project_source_root() / get_option('bin_dir') / 'RES' / 'UTILS'
bin_cosmetic = meson.project_source_root() / get_option('bin_dir') / 'RES' / 'COSMETIC'

# For every directory in this folder with meson.build, include them.
# Then, compile a list of arguments to pass into DOSBox.
# This way, we only have to call DOSBox once to compile all other DOS apps.
# (Or else it would be a jumpscare in a nightmare)

# Init arguments to pass into DOSBox
dosbox_args = [
  '-noconsole',
  '-c', 'cls',
  '-c', 'mount x "' + tcc + '"',
  '-c', 'mount y "' + meson.current_source_dir() + '"',
  '-c', 'mount r "' + meson.current_build_dir() + '"',
  '-c', 'mount i "' + custom_include_path + '"',
  '-c', 'PATH %path%;x:\\BIN',
  '-c', 'r:',
  '-c', 'tcc.exe /IX:\\include /LX:\\LIB /IY:\\INCLUDE -ms Y:\\W1SETVER.C Y:\\INCLUDE\\MPCLIB.C Y:\\INCLUDE\\MININI.C'
        + (get_option('tcc_output_to_file') ? ' >> TCC_LOG.TXT' : ''),
]

# Ask Windows to list folders in this directory (bare names only)
rd = run_command('cmd', '/c', 'dir', '/b', '/ad')
subdirs = rd.stdout().strip().split('\n')

# For each directory, look for meson.build and include it.
foreach d : subdirs
  if fs.is_dir(d) and fs.exists(d / 'meson.build')
    # Wipe variables
    src = ''
    out = ''
    dest = ''
    # Enter the directory so its variables become visible
    subdir(d)
    vars = sub_variables
    src  = vars.get_variable('source_file')
    out  = vars.get_variable('output_file')
    dest = vars.get_variable('install_bin_dir')

    # After subdir(), the following variables MUST exist:
    #   source_file
    #   output_file
    #   install_bin_dir
    if src == ''
      error('In ' + d + '/meson.build, source_file is empty.')
    elif out == ''
      error('In ' + d + '/meson.build, output_file is empty.')
    elif dest == ''
      error('In ' + d + '/meson.build, install_bin_dir is empty.')
    endif

    dosbox_args += ['-c', 'tcc.exe /IX:\\include /LX:\\LIB /II:\\ -ms Y:\\' + d + '\\' + src + ' I:\\MPCLIB.C I:\\MININI.C'
                + (get_option('tcc_output_to_file') ? ' >> TCC2_LOG.TXT' : '')]

    # Make this installable
    custom_target(
      d + '_dos_app',
      input: d / src,
      output: out,
      command: 'echo',
      build_by_default: true,
      build_always_stale: true,
      install: true,
      install_dir: dest
    )
  endif
endforeach

# Run dosbox with all arguments
custom_target('other_dos_apps',
    input: [],
    output: 'ALL_DOS_APPS_BUILT.TXT',
    command: [dosbox] + dosbox_args + (get_option('exit_on_16bit_compilation') ? ['-c', 'exit'] : []),
    build_by_default: true,
    build_always_stale: true,
)