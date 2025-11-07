# Making an instance of Patchress
1st November, 2025 4:10PM

To make a build of patchress on your system, *assuming it's MS Windows*:

## Prerequisites
1. Meson
2. Ninja
3. DOSBox
4. Turbo C++ Compiler files

## Instructions

1. In the root of Patchress directory, open the ```meson_options.txt``` file.
2. Change the value of options:
    - ```dosbox``` must point to path where DOSBox.exe is located.
    - ```tcc``` must point to path where TurboC++ is installed. (The path must contain BIN, INCLUDE, etc)
3. Run ```meson setup build``` if 'build' directory does not exist.
4. Run ```meson compile -C build``` to build Patchress, for every change you make.