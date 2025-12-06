// Application to install RDISK.COM
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
    //char drive_letter[3];
    int key = 0;
    FILE *autoexec_bat;
    (void)argc;
    // Check for arguments
    validate_mpc_args(argv);

    get_screen_size();

    // Save current working directory
    getcwd(cwd, sizeof(cwd));

    // Play intro again if we absolutely need it (bruh)
    if (!arg_check(argv, "/MPC")) intro();

    title("RAMDISK Setup");
    textcolor(WHITE);

    page1:
    print_page(" RDISK is a RAM-disk driver. It creates a \"fast\" disk using up to 2-GB\n"
               " of XMS memory.   Files can be uploaded via AUTOEXEC to the RAM-disk and\n"
               " accessed at memory speeds.    RDISK is a simple RAM-disk driver with no\n"
               " resizing or other options.\n");
    status("  ENTER = Next");
    print_page("  Please enter the path where RAMDISK shall be installed.\n");
    cprintf("     ");
    input(ins_path, sizeof(ins_path), "C:\\DOS");
    dbg("INS_PATH: %s", ins_path);
/*    print_page("\n  Drive letter to use as Ramdisk (CONFIG.SYS autoloading).\n");
    cprintf("     ");
    input(drive_letter, sizeof(drive_letter), "R");*/

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

    print_page(" The path is:\n\n"
               "  Installation directory: %s\n\n"
               //"  Ramdisk drive letter: %s\n\n"
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
    // Check if installation exist in current dir
    if (!file_exists("RDISK.COM") || !file_exists("RDISKON.COM"))
        crash("One or more required files not found.");

    status("Checking for previous files and removing...");
    // Delete file if already exist
    if (file_exists("%s\\RDISK.COM", ins_path))
        remove_file("%s\\RDISK.COM", ins_path);

    if (file_exists("%s\\RDISKON.COM", ins_path))
        remove_file("%s\\RDISKON.COM", ins_path);

    print_page("Installing Ramdisk...\n");

    // Install file
    status("Copying RDISK.COM...");
    sprintf(tmp, "%s\\RDISK.COM", ins_path);
    if (copy_file("RDISK.COM", tmp) != 0) {
        print_page(" Error: Unable to copy RDISK.COM to %s.\n"
                   " Make sure you have write permissions to that directory.\n\n"
                   " Press F3 to exit.", ins_path);
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    status("Copying RDISKON.COM...");
    sprintf(tmp, "%s\\RDISKON.COM", ins_path);
    if (copy_file("RDISKON.COM", tmp) != 0) {
        print_page(" Error: Unable to copy RDISKON.COM to %s.\n"
                   " Make sure you have write permissions to that directory.\n\n"
                   " Press F3 to exit.", ins_path);
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    // Add line to AUTOEXEC.BAT
    if (yesno(false, "Auto-load RDISK.COM into AUTOEXEC.BAT? [Y/N]")) {
        print_page("\nUpdating AUTOEXEC.BAT");
        status("Updating C:\\AUTOEXEC.BAT...");
        autoexec_bat = fopen("C:\\AUTOEXEC.BAT", "a");
        if (autoexec_bat == NULL) {
            print_page(" Error: Unable to open C:\\AUTOEXEC.BAT for writing.\n"
                    " You must add the following to your AUTOEXEC.BAT manually:\n\n"
                    "    %s\\RDISK.COM\n\n"
                    " Setup successfully copied RDISK.COM to %s.\n"
                    " Press F3 to exit.", ins_path, ins_path);
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        } else {
            fprintf(autoexec_bat, "%s\\RDISK.COM\n", ins_path);
            fclose(autoexec_bat);
        }
    }

    print_page("\n Operation completed successfully.\n"
               " You must restart to load RDISK.COM.\n");
    status("  F3 = Exit");
    while (getch() != 61);
    quit(0);

    // to shut up
    return 0;
}
