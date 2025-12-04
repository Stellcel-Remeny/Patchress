// Application to install CREGFIX
// remeny

#include "MPCLIB.H"
#include <stdio.h>
#include <conio.h>
#include <dir.h>
#include <stdlib.h>

char cwd[MAXPATH];

void quit(int ret) {
    if (cwd[0] != '\0') {
        _chdrive((toupper(cwd[0]) - 'A') + 1); // Starting drive
        chdir(cwd); // Return to starting directory
    }
    intro_reverse(); 
    exit(ret);
}

int main(int argc, char* argv[]) {
    char ins_path[60] = {0};
    char tmp[80];
    int key = 0;
    (void)argc;
    // Check for arguments
    if (!arg_check(argv, "/ni")) flags.animate = true;
    if (arg_check(argv, "/v")) { // Verbose/Debug mode
        flags.verbose = true;
        if (arg_check(argv, "/vp")) flags.v_pause = true;
        if (arg_check(argv, "/vlog")) flags.v_log = true;
        if (arg_check(argv, "/vw")) flags.v_word_by_word = true;
    }

    get_screen_size();

    // Save current working directory
    getcwd(cwd, sizeof(cwd));

    // Play intro again if we absolutely need it (bruh)
    if (!arg_check(argv, "/MPC")) intro();

    title("CREGFIX Setup");
    textcolor(WHITE);

    page1:
    print_page("  CREGFIX is a small DOS driver that works around an issue of many modern CSM "
               "BIOS implementations where certain control register bits are left \"dirty\", thus "
               "causing issues when trying to run legacy operating systems such as Microsoft "
               "Windows 9x (see \"While initializing device VCACHE: Windows protection error\" "
               "issue) or while trying to run EMM386.EXE.\n\n"

               "  This application copies CREGFIX.SYS and loads it in C:\\CONFIG.SYS\n");
    status("  ENTER = Next");
    print_page("  Please enter the path where CREGFIX shall be installed.\n");
    cprintf("     ");
    input(ins_path, sizeof(ins_path), "C:\\DOS");
    dbg("INS_PATH: %s", ins_path);

    status("");
    wipe();
    if (ins_path[0] == '\0') {
        print_page(" A path is invalid, as it is empty. Please go back and double-check.\n\n"
                   " Press ENTER to re-enter the path, or F3 to exit.");
        status("  ENTER = Go Back  F3 = Exit");
        keychk:
        key = 0;
        while (1) {
            key = getch();
            if (key == 13) {
                wipe();
                goto page1;
            } else if (key == 61) {
                quit(0);
            }
        }
    }

    print_page(" The installation directory is:\n\n"
               "  %s\n\n"
               " If this is correct, press ENTER to install, or ESC to re-enter the path.\n"
               " You can also press F3 to quit now.\n", ins_path);
    status("  ENTER = Install  ESC = Go back  F3 = Exit  ");

    while (key != 13) {
        key = getch();
        if (key == 27) {
            wipe();
            goto page1;
        } else if (key == 61) {
            quit(0);
        }
    }

    wipe();
    // Check if cregfix exist in current dir
    if (!file_exists("CREGFIX.SYS"))
        crash("One or more required files not found.");

    status("Checking for previous files...");
    // Delete if cregfix files already exist
    if (file_exists("%s\\CREGFIX.SYS", ins_path))
        remove_file("%s\\CREGFIX.SYS", ins_path);

    // Install CREGFIX
    status("Copying CREGFIX.SYS...");
    sprintf(tmp, "%s\\CREGFIX.SYS", ins_path);
    if (copy_file("CREGFIX.SYS", tmp) != 0) {
        print_page(" Error: Unable to copy CREGFIX.SYS to %s.\n"
                   " Make sure you have write permissions to that directory.\n\n"
                   " Press F3 to exit.", ins_path);
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    // Add line
    status("Updating C:\\CONFIG.SYS...");
    if (file_prepend("C:\\CONFIG.SYS", "DEVICE=%s\\CREGFIX.SYS", ins_path) != 0) {
        print_page(" Error: An error occured while trying to edit C:\\CONFIG.SYS.\n"
                   " You must add the following at the top of your CONFIG.SYS manually:\n\n"
                   "    DEVICE=%s\\CREGFIX.SYS\n\n"
                   " Press F3 to exit.", ins_path);
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    print_page("\n Operation completed successfully.\n"
               " You must restart to load CREGFIX.\n\n"
               " Press F3 to exit.");
    status("  F3 = Exit");
    while (getch() != 61);
    quit(0);

    // to shut up
    return 0;
}
