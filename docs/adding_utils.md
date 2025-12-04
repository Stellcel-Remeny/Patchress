
# Adding utilities

4th December, 2025 7:00PM

You can add new utilities/patches/etc. into your local instance of MultiPatcher, either at compile time or after it.

(To add in an already compiled instance, follow compile-time steps from 1-3, but just use the 'RES' directory.)

## Compile time

1. In `source/BASE/RES` directory, make a directory with a name that is not longer than **8 charcaters**.
2. Inside that directory, create either:
    - `LFN.INI` if the directory will serve as a menu (holds more menus/entries)
    - `INFO.INI` if the directory will serve as an entry (holds the actual util/patch/etc.)

3. Populate the .INI file. View [INI file structures](ini_structures.md)
4. Compile the project. View [Instructions](docs/building.md#instructions)
