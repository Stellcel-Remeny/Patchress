// Application to install shutdown for ms-dos
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
    FILE *autoexec_bat;
    (void)argc;
    // Check for arguments
    validate_mpc_args(argv);

    get_screen_size();

    // Save current working directory
    getcwd(cwd, sizeof(cwd));

    // Play intro again if we absolutely need it (bruh)
    if (!arg_check(argv, "/MPC")) intro();

    title("Shutdown Setup");
    textcolor(WHITE);

    page1:
    print_page("  What does it do?\n"
               " It has 2 functions: shutdown your computer\n"
               "                     reboot your computer\n\n"
               " The shutdown option only works on ATX systems with Advanced Power Management\n"
               " version 1.2 or higher. Just try the program, if it works, your system meets\n"
               " the requirements.\n"
               " The reboot option works on any modern personal computer.\n\n"
               "  This application copies SHUTDOWN.COM.\n");
    status("  ENTER = Next");
    print_page("  Please enter the path where Shutdown shall be installed.\n");
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
    // Check if file exist in current dir
    if (!file_exists("SHUTDOWN.COM"))
        crash("One or more required files not found.");

    status("Checking for previous files...");
    // Delete previously installed files
    if (file_exists("%s\\SHUTDOWN.COM", ins_path))
        remove_file("%s\\SHUTDOWN.COM", ins_path);

    // Install item
    status("Copying SHUTDOWN.COM...");
    sprintf(tmp, "%s\\SHUTDOWN.COM", ins_path);
    if (copy_file("SHUTDOWN.COM", tmp) != 0) {
        print_page(" Error: Unable to copy SHUTDOWN.COM to %s.\n"
                   " Make sure you have write permissions to that directory.\n\n"
                   " Press F3 to exit.", ins_path);
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    print_page("\n Operation completed successfully.\n\n"
                " How to use it?\n"
                " Just type SHUTDOWN and you will see the following text:\n\n"
                "   ShutDown v1.2 www.blacklight.wxs.org\n"
                "   S(hutdown), R(estart), or C(ancel)? _\n\n"
                " You can also operate ShutDown from the command-line.\n\n"

                " To shutdown, type:    SHUTDOWN S   and press Enter\n"
                " To reboot, type:      SHUTDOWN R   and press Enter\n"
                " To show help, type:   SHUTDOWN ?   and press Enter\n\n"
               " Press F3 to exit.", ins_path);
    status("  F3 = Exit");
    while (getch() != 61);
    quit(0);

    // to shut up
    return 0;
}
