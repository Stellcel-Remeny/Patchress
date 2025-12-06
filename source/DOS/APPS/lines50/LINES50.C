// Application to increase screen height in msdos
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

    title("Screen row increase using MODE");
    textcolor(WHITE);

    page1:
    print_page("  This application appends the following to C:\\AUTOEXEC.BAT:\n\n"
               "       MODE CON COLS=80 LINES=50\n\n"
               "  Press ENTER to continue.\n"
               "  Requires MODE to be available in PATH.\n"
               "  Requires ANSI.SYS to be loaded via CONFIG.SYS.");
    status("  ENTER = Install  F3 = Exit");

    while (key != 13) {
        key = getch();
        if (key == 61) quit(0);
    }

    wipe();
    // Add line to AUTOEXEC.BAT
    status("Updating C:\\AUTOEXEC.BAT...");
    autoexec_bat = fopen("C:\\AUTOEXEC.BAT", "a");
    if (autoexec_bat == NULL) {
        print_page(" Error: Unable to open C:\\AUTOEXEC.BAT for writing.\n"
                   " You must add the following to your AUTOEXEC.BAT manually:\n\n"
                   "    MODE CON COLS=80 LINES=50\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    } else {
        fprintf(autoexec_bat, "\nMODE CON COLS=80 LINES=50\n");
        fclose(autoexec_bat);
    }

    print_page("\n Operation completed successfully.\n"
               " You must restart for changes to take effect.\n\n"
               " Press F3 to exit.");
    status("  F3 = Exit");
    while (getch() != 61);
    quit(0);

    // to shut up
    return 0;
}
