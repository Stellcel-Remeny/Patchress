
# Building MultiPatcher

1st November, 2025 4:10PM
30th November, 2025 4:54PM
4th December, 2025 6:45PM

To make a build of MultiPatcher on your system, *assuming it's MS Windows*:

## Prerequisites

1. Meson
2. Ninja
3. DOSBox-X
4. Turbo C++ Compiler files

## Instructions

1. In the root of the MultiPatcher directory, create a new file named ```local.conf```.
2. Put ```[project options]``` in it.
3. Under it, add the following and then save it (use double backslashes or single forward slashes):
    - ```dosbox = '<file>'```, where ```<file>``` must point to the path where DOSBox EXE file is located, including filename.
        The following is an example:
        ```dosbox = 'C:\\DOSBox-X\\DOSBox-X.exe'```
    - ```tcc = '<path>'```, where ```<path>``` must point to the path where TurboC is installed. (The path must contain BIN, INCLUDE, etc)
4. Run ```meson setup builddir --native-file local.conf```.
5. Run ```meson install -C builddir``` to build MultiPatcher. Finalized output will be located in bin_dir (usually ```bin/```)

## Building MPC for Windows VB4

You will need a copy of Microsoft Visual Basic 4.0 16-bit to compile this application.

1. Open Microsoft Visual Basic 4.0 16-bit
2. Open the project in `source/VB4'
3. Make necessary modifications and compile it using the File menu in VB4.
4. Copy the resulting .EXE file as `source/BASE/Patchg16.exe` along with the `DATA/` folder.
5. Recompile the whole project using meson.

## Tips

-You can view ```meson_options.txt``` and enable/edit more options in local.conf.
-To fully rebuild, delete builddir and bin.
