
# Making an instance of Patchress

1st November, 2025 4:10PM

To make a build of patchress on your system, *assuming it's MS Windows*:

## Prerequisites

1. Meson
2. Ninja
3. DOSBox
4. Turbo C++ Compiler files

## Instructions

1. In the root of Patchress directory, create a new file named ```local.conf```.
2. Put ```[project options]``` in it.
3. Under it, add the following and then save it (use double backslashes or single forward slashes):
    - ```dosbox = '<path>'```, where ```<path>``` must point to the path where DOSBox.exe is located.
        The following is an example:
        ```dosbox = 'C:\\Program Files (x86)\\DOSBox-0.74-3'```
    - ```tcc = '<path>'```, where ```<path>``` must point to the path where TurboC is installed. (The path must contain BIN, INCLUDE, etc)
4. Run ```meson setup builddir --native-file local.conf```.
5. Run ```meson install -C builddir``` to build Patchress. Finalized output will be located in bin_dir (usually ```bin/```)

## Tips

-You can view ```meson_options.txt``` and enable/edit more options in local.conf.
-To fully rebuild, delete builddir and bin.