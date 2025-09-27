# Adding utilities to Patchress
27th September, 2025 5:44PM
## Locally

You can use Patchress to include your own set of utilities, patches, and applications in your local copy.

### Steps:
1. In the "RES/" directory (or "source/resources" if you are compiling), create a folder.
2. Inside this folder:
    - Create 'lfn.ini' file if you want this directory to hold MORE utilities (so it is not a utility by itself)
                    OR
    - Create 'info.ini' file if this is a utility in itself (i.e., it holds executables).

    If you made lfn.ini, then under `[MAIN]` you should only give a `NAME=` variable.
3. Copy the following (info.ini):
    ``` [MAIN]
    Name=<name that will show in menu selector>
    Description=<cute description that defines your item well>
    Version=<Version number>
    Author=<Creator/Maintainer>
    Exec=<Item to run> ```
4. Make another section named `[OS]`. This defines which OSes support your utility. (Refer OS.md)
5. Copy over all stuff from your utility into this directory.

## Online (Into this repo)
Please reach out to remenycompany@gmail.com