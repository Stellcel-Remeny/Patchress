// Application to change the reported DOS version (unnecessary app but ok)
// remeny

#include "MPCLIB.H"
#include <process.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {    
    char win_path[60] = {0};
    char dos_path[60] = {0};
    char *tmp;
    int key = 0, ret = 0;
    FILE *config_sys;
    // Check for arguments
    if (!arg_check(argv, "/ni")) flags.animate = true;
    if (arg_check(argv, "/v")) { // Verbose/Debug mode
        flags.verbose = true;
        if (arg_check(argv, "/vp")) flags.v_pause = true;
        if (arg_check(argv, "/vlog")) flags.v_log = true;
        if (arg_check(argv, "/vw")) flags.v_word_by_word = true;
    }

    get_screen_size();
    title("Set reported DOS version for Windows 1.0");

    page1:
    print_page("This application runs SETVER.EXE on WIN100.BIN\n"
               "to set the reported DOS version to 3.31.\n\n");
    status("  ENTER = Continue  F3 = Exit");
    print_page("  Please enter the path to your Windows 1.0 installation.\n\n");
    cprintf("     ");
    input(win_path, sizeof(win_path), "C:\\WINDOWS");
    print_page("\n\n  Please enter the path of your current DOS installation.\n\n");
    status("  ENTER = Continue  F3 = Exit");
    cprintf("     ");
    input(dos_path, sizeof(dos_path), "C:\\DOS");

    wipe();
    if (win_path[0] == '\0' || dos_path[0] == '\0') {
        print_page(" A path is invalid, as it is empty. Please go back and double-check.\n\n"
                   " Press ENTER to re-enter the path, or F3 to exit.");
        status("  ENTER = Go Back  F3 = Exit");
        while (1) {
            key = getch();
            if (key == 13) {
                wipe();
                goto page1;
            } else if (key == 61) {
                return 0;
            }
        }
    }
    print_page("The paths you entered are:\n"
               " DOS: %s\n"
               " WINDOWS: %s\n\n"
               "If this is correct, press ENTER to continue, or ESC to re-enter the paths.\n"
               "You can also press F3 to quit now.\n", dos_path, win_path);
    status("  ENTER = Continue  ESC = Go back  F3 = Exit  ");

    while (key != 13) {
        key = getch();
        if (key == 27) {
            wipe();
            goto page1;
        } else if (key == 61) {
            return 0;
        }
    }

    // Check if SETVER.EXE exists in the DOS path
    if (!file_exists("%s\\SETVER.EXE", dos_path)) {
        wipe();
        print_page(" SETVER.EXE is not found in the specified DOS path (%s).\n"
                   " Setup can install SETVER.EXE version 5.0 for you.\n"
                   " Setup will also add the necessary line to 'C:\\CONFIG.SYS'.\n\n"
                   " Press ENTER to install SETVER.EXE, F3 to exit.", dos_path);
        status("  ENTER = Continue  F3 = Exit");
        while (1) {
            key = getch();
            if (key == 13) {
                // Copy SETVER.EXE from current directory to DOS path
                status("Copying SETVER.EXE to %s...", dos_path);
                strcpy(tmp, "%s\\SETVER.EXE", dos_path);
                if (copy_file("SETVER.EXE", tmp) != 0) {
                    print_page(" Error: Unable to copy SETVER.EXE to %s.\n"
                               " Make sure you have write permissions to that directory.\n\n"
                               " Press F3 to exit.", dos_path);
                    status("  F3 = Exit");
                    while (getch() != 61);
                    return -1;
                }
                // Add line to CONFIG.SYS
                status("Updating C:\\CONFIG.SYS...");
                config_sys = fopen("C:\\CONFIG.SYS", "a");
                if (config_sys == NULL) {
                    print_page(" Error: Unable to open C:\\CONFIG.SYS for writing.\n"
                               " You must add the following to your CONFIG.SYS manually:\n\n"
                               "    DEVICE=%s\\SETVER.EXE\n\n"
                               " You can still continue with setup by pressing ENTER.\n"
                               " Press F3 to exit.", dos_path);
                    status("  ENTER = Continue  F3 = Exit");
                    while (getch() != 61);
                    return -1;
                }
                fprintf(config_sys, "\nDEVICE=%s\\SETVER.EXE\n", dos_path);
                fclose(config_sys);
                break;
            } else if (key == 61) {
                return 0;
            }
        }
    }
    wipe();
    status("Setting reported DOS version to 3.31...");

    dbg("%s\\SETVER.EXE %s\\WIN100.BIN 3.31", dos_path, win_path);
    ret = spawnl(P_WAIT, "%s\\SETVER.EXE %s\\WIN100.BIN 3.31", dos_path, win_path);

    if (ret == 0) {
        print_page("\nOperation completed successfully.\n"
                   "Press Enter to exit.");
        while (getch() != 13);
        return 0;
    } else {
        print_page("Error: Unable to run SETVER.EXE.\n"
                    "When you go back to MS-DOS terminal, try running the following:\n\n"
                    "    %s\\SETVER.EXE %s\\WIN100.BIN 3.31\n\n"
                    "Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        return -1;
    }
}
