
# Making bootable ISOs

7th December, 2025 11:14PM

You can create a bootable .ISO image containing MultiPatcher.

## Prerequisets

- MultiPatcher compiled at least once
- **Compilation folder must be** `bin/`
- `BOOT.IMG` file inside `bin/`
- `BOOT.IMG` file must be a 1.44mb .IMG file, containing boot code.

## Creating bootable iso image

In Microsoft Windows:

1. Run `utils\\isogen.bat``
2. `ISO.iso` file will be generated.
