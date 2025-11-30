# Variables for directories
bin_patches = meson.project_source_root() / get_option('bin_dir') / 'RES' / 'PATCHES'
bin_utils = meson.project_source_root() / get_option('bin_dir') / 'RES' / 'UTILS'
bin_cosmetic = meson.project_source_root() / get_option('bin_dir') / 'RES' / 'COSMETIC'
bin_drivers = meson.project_source_root() / get_option('bin_dir') / 'RES' / 'DRIVERS'

# For every directory in this folder with meson.build, include them.
# Then, compile a list of arguments to pass into DOSBox.
# This way, we only have to call DOSBox once to compile all other DOS apps.
# (Or else it would be a jumpscare in a nightmare)

# Arguments to pass to DOSBOX-x
dosbox_args = [
  '-noconsole',
  '-c', 'cls',
  '-c', 'mount x "' + tcc + '"',
  '-c', 'mount y "' + meson.current_source_dir() + '"',
  '-c', 'mount r "' + meson.current_build_dir() + '"',
  '-c', 'mount i "' + custom_include_path + '"', # We now use this only to provide header files.
  '-c', 'mount o "' + custom_include_path_OBJ + '"', # We use the OBJ variable to not recompile libraries. (EXCPECTS MAIN MESON.BUILD TO HAVE ALREADY COMPILED THEM)
  '-c', 'PATH %PATH%;x:\\BIN',
  '-c', 'r:',
  '-c', 'CMPDAPPS.BAT',
]

batch_cmds = []

# Ask Windows to list folders in this directory (bare names only)
rd = run_command('cmd', '/c', 'dir', '/b', '/ad')
subdirs = rd.stdout().strip().split('\n')

# For each directory, look for meson.build and include it.
foreach d : subdirs
  if fs.is_dir(d) and fs.exists(d / 'meson.build')
    # Wipe variables
    src = ''
    out = ''
    # Enter the directory so its variables become visible
    subdir(d)
    vars = sub_variables
    src  = vars.get_variable('source_file')
    out  = vars.get_variable('output_file')

    # After subdir(), the following variables MUST exist:
    #   source_file
    #   output_file
    if src == ''
      error('In ' + d + '/meson.build, source_file is empty.')
    elif out == ''
      error('In ' + d + '/meson.build, output_file is empty.')
    endif

    batch_cmds += ['cd ' + d,
                   'tcc.exe /IX:\\include /LX:\\LIB /II:\\ -ms Y:\\' + d + '\\' + src + ' O:\\MPCLIB.OBJ O:\\MININI.OBJ'
                   + (get_option('tcc_output_to_file') ? ' > TCC_LOG.TXT' : ''),
                   'cd ..']
  endif
endforeach

# Quit if needed
batch_cmds += get_option('exit_on_16bit_compilation') ? ['exit'] : []

# Dump batch_cmds into a .bat file
batch_content = '\n'.join(batch_cmds)
configure_file(
  input: 'CMPDAPPS.BAT.in',
  output: 'CMPDAPPS.BAT',
  configuration: {
    'BATCH_CONTENT': batch_content,
  }
)

# Run dosbox
custom_target('other_dos_apps',
    input: [],
    output: 'ALL_DOS_APPS_BUILT.TXT',
    command: [dosbox] + dosbox_args,
    build_by_default: true,
    build_always_stale: true,
    depends: mpc_dos, # Make sure main one builds libraries...
)