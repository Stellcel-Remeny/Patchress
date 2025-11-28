
# Structure of INFO.INI

28th November, 2025 9:16PM

## What does INFO.INI tell?

The presence of `INFO.INI` inside any folder in `RES/` tells MultiPatcher that it is an entry.

## What is an entry?

An entry is a folder that contains the actual patch/utility/etc in it.

These show up in the MPC GUI/TUI app different to Menus.

They can execute the application specified in `INFO.INI`.

## Structure

Under `[MAIN]`:
    - `name=` The name to be displayed in the MPC interface.
    - `description=` A short description of the item.
    - `author=` Creator of the item.
    - `version=` Version of the item.

Under `[OS]`:
    - `msdos=<true/false>` Boolean to specifiy if supported under MS-DOS.

Under `[MSDOS]`:
    - `exec=` Name of the executable
    - `passArgs=<true/false>` Passes arguments from the main MultiPatcher application down, along with the `/MPC` argument.
    - `batchMode=<true/false>` Run `Exec=` under `system()` (The COMMAND.COM Shell). Must be set to TRUE if `Exec=` is a batch script.
