// Application to install vbesvga
// remeny

#include "MPCLIB.H"
#include <process.h>
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
    char win_path[60] = {0};
    int key = 0, ret = 0;
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

    title("VBESVGA for Windows 3.1");
    textcolor(WHITE);

    page1:
    status("  ENTER = Next");
    print_page("  Please enter the path to your Windows 3.1 installation.\n");
    cprintf("     ");
    input(win_path, sizeof(win_path), "C:\\WINDOWS");
    dbg("WIN_PATH: %s", win_path);

    status("");
    wipe();
    if (win_path[0] == '\0') {
        print_page(" The path to your Windows 3.1 installation is empty.\n\n");

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

    // Execute SETUP.EXE
    ret = spawnl(P_WAIT,
                 "SETUP.EXE",
                 "SETUP.EXE",
                 win_path,
                 NULL);

    getch();

    if (ret != 0) {
        title("Error");
        print_page("An error occured.\n");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    quit(0);
    return 0;
}
