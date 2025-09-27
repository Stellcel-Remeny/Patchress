# Operating system support
27th September, 2025 5:44PM

You can tell Patchress that an item supports running under an Operating system via the `[OS]` section.

If an OS is not specified as '=true' or similar, then it is marked as False by Patchress and therefore refuse to run it.

## Variables

`msdos=true` : Allows running under MS-DOS and Windows 3.x. (No dedicated flag for Win3x exists yet)