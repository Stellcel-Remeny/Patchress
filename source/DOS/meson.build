#
# Build file for 16-bit Patchress MSDOS
#

# Get DOS utility paths from options
dosbox = get_option('dosbox')
message('DOSbox Directory: ' + dosbox)
tcc = get_option('tcc')
message('TurboC Directory: ' + tcc)

# Add executable to end of DOSBox path
dosbox = dosbox + '\\DOSBox.exe'

# Variables
source_file = 'PATCHX16.C'
output_file = 'PATCHX16.EXE'

# Check if Tcc exist
fs = import('fs')
if not fs.is_file(tcc + '\\BIN\\TCC.EXE')
    message('TCC.EXE not found in "BIN" in the directory specified!')
endif

# Arguments to pass into DOSBox
dosbox_args = [
    '-noconsole',
    '-c', 'cls',
    '-c', 'mount x "' + tcc + '"',
    '-c', 'mount y "' + meson.current_source_dir() + '"',
    '-c', 'mount r "' + meson.current_build_dir() + '"',
    '-c', 'PATH %path%;x:\\BIN',
    '-c', 'r:',
    '-c', 'tcc.exe /IX:\\include /LX:\\LIB /IY:\\INCLUDE -ms Y:\\PATCHX16.C Y:\\INCLUDE\\MPCLIB.C Y:\\INCLUDE\\MININI.C > TCC_LOG.TXT',
]

# If debug run after compilation is enabled
if get_option('quick_run_16bit')
    message('QUICK_RUN_16BIT IS ENABLED.')
    dosbox_args += ['-c', 'MPC.EXE' + get_option('mpc_dos_args')]
endif

if get_option('exit_on_16bit_compilation')
    dosbox_args += ['-c', 'exit']
endif

# To 

# Build the application
custom_target('16_bit_mpc_dos',
    input: source_file,
    output: output_file,
    command: [dosbox] + dosbox_args,
    build_by_default: true,
    build_always_stale: true,
    native: false
    install: true,
    install_dir: meson.project_source_root() / get_option('bin_dir')
)

# To run Patchx16.exe (```meson compile -C builddir run```)
run_target('run_dos',
    command: [
        dosbox,
        '-noconsole',
        '-c', 'mount r "' + meson.project_source_root() / get_option('bin_dir') + '"',
        '-c', 'r:',
        '-c', output_file,
        '-c', 'exit'
    ]
)
