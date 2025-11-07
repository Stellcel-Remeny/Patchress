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

# Check if Tcc exist
fs = import('fs')
if not fs.is_file(tcc + '\\BIN\\TCC.EXE')
    message('TCC.EXE not found in "BIN" in the directory specified!')
endif

# Arguments to pass into DOSBox
dosbox_args = [
    '-noconsole',
    '-c', 'mount x ' + tcc,
    '-c', 'mount y ' + meson.current_source_dir(),
    '-c', 'PATH %path%;x:\\BIN',
    '-c', 'y:',
    '-c', 'tcc.exe /IX:\\include /LX:\\lib -ms MPC.C',
]

# If debug run after compilation is enabled
if get_option('quick_run_16bit')
    message('QUICK_RUN_16BIT IS ENABLED.')
    dosbox_args += ['-c', 'MPC.EXE']
endif

dosbox_args += ['-c', 'exit']

# Build the application
custom_target('MPC.EXE',
    input: 'MPC.C',
    output: 'MPC.EXE',
    command: [dosbox, dosbox_args],
    build_by_default: true,
)