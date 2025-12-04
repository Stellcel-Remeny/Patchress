
# Adding utilities

4th December, 2025 7:00PM

You can add new utilities/patches/etc. into your local instance of MultiPatcher, either at compile time or after it.

(To add in an already compiled instance, follow compile-time steps from 1-3, but just use the 'RES' directory.)

You can also add a .C file (for MS-DOS app), which can take advantage of `MPCLIB.C`. See 'Adding custom DOS utility'

## Compile time

1. In `source/BASE/RES` directory, make a directory with a name that is not longer than **8 charcaters**.
2. Inside that directory, create either:
    - `LFN.INI` if the directory will serve as a menu (holds more menus/entries)
    - `INFO.INI` if the directory will serve as an entry (holds the actual util/patch/etc.)

3. Populate the .INI file. View [INI file structures](ini_structures.md)
4. Compile the project. View [Instructions](docs/building.md#instructions)

## Adding custom DOS utility

You can add your own .C file to be compiled by TURBOC 3.0 compiler in DOSBox, and then automatically be added into your local MultiPatcher instance.

By doing this, you can also include the `MININI.C` and `MPCLIB.C` files in your C file, or any other .C + .H file found in `source/DOS/INCLUDE`, which will be automatically made available to your .C file.

Steps to add a custom DOS utility:

1. In the directory `source/DOS/APPS`, create a new directory having a name less than **8 characters**.
2. Inside that directory, add a file named `meson.build`
3. Copy the template given in [TEMPLATE](TEMPLATE.md), and follow its instructions.
4. Add your .C file with the `<src_c_file>` name you have set in your `meson.build` file.
5. Delete any builddir you have currently, and then re-build MultiPatcher. View [Building](building.md).
