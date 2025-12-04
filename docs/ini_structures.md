
# INI file structures

28th November, 2025 9:16PM
29th November, 2025 8:02AM
4th December, 2025 9:39PM

## Menus and LFN.INI

- The presence of `LFN.INI` inside any folder in `RES/` tells MultiPatcher that it is a menu.

- A menu is a folder that contains other menus or entries in it.

## Entries and INFO.INI

- The presence of `INFO.INI` inside any folder in `RES/` tells MultiPatcher that it is an entry.

- An entry is a folder that contains the actual patch/utility/etc in it.

- These show up in the MPC GUI/TUI app different to Menus.

- They can execute the application specified in `INFO.INI`.

## Structure of LFN.INI

Under `[MAIN]`:

- `name=` The name to be displayed in the MPC interface.

Under `[OS]`:

- `msdos=<true/false>` To show under DOS, set to `true`.
- `w31=<true/false>` To show under Windows 3.1, set to `true`.
- `w95=<true/false>` To show under Windows 95, set to `true`.

... and so on for each of these options: `w98`, `wme`, `nt31`, `nt35`, `nt351`, `nt4`, `w2k`, and `wxp`

## Structure of INFO.INI

Under `[MAIN]`:

- `name=` The name to be displayed in the MPC interface.
- `description=` A short description of the item.
- `author=` Creator of the item.
- `version=` Version of the item.

Under `[OS]`:

- `msdos=<true/false>` To show under DOS, set to `true`.
- `w31=<true/false>` To show under Windows 3.1, set to `true`.
- `w95=<true/false>` To show under Windows 95, set to `true`.

... and so on for each of these options: `w98`, `wme`, `nt31`, `nt35`, `nt351`, `nt4`, `w2k`, and `wxp`

Under `[MSDOS]`:

- `exec=` Name of the executable
- `passArgs=<true/false>` Passes arguments from the main MultiPatcher application down, along with the `/MPC` argument.
- `batchMode=<true/false>` Run `Exec=` under `system()` (The COMMAND.COM Shell). Must be set to TRUE if `Exec=` is a batch script.
- `pauseOnQuit=<true/false>` Pause for one keypress after `Exec=` finishes.
