// Application to change the reported DOS version (unnecessary app but ok)
// remeny

#include "patchress_dos.h"
#include <process.h>

#define SCREEN_HEIGHT 25

int main() {
    screen_rows = SCREEN_HEIGHT;

    char win_path[60] = {0};
    char setver_args[128] = {0};
    int key = 0;

    intro();
    title("Set reported DOS version for Windows 1.0");

    page1:
    print_page("This application runs SETVER.EXE on WIN100.BIN\n"
               "to set the reported DOS version to 3.31.\n\n"
               "This ASSUMES that SETVER.EXE IS LOADED in CONFIG.SYS,\n"
               "and that it is present in PATH.\n\n");
    print("  Please enter the path to your Windows 1.0 installation.\n\n");
    print("     ");
    input(win_path, sizeof(win_path), "C:\\WINDOWS");

    wipe();
    if (win_path[0] == '\0') {
        print_page("Trying to troll me? You did not enter a path.\n"
                   "Press ENTER to re-enter the path, or F3 to exit.");
        status(25, "  F3 = Exit");
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
    print_page("The path you entered is: %s\n\n"
               "If this is correct, press ENTER to continue, or ESC to re-enter the path.\n"
               "You can also press F3 to quit now.\n", win_path);

    while (key != 13) {
        key = getch();
        if (key == 27) {
            wipe();
            goto page1;
        } else if (key == 61) {
            return 0;
        }
    }

    wipe();
    print_page("Running SETVER.EXE on WIN100.BIN to set reported DOS version to 3.31...\n\n");
    snprintf(setver_args, sizeof(setver_args), "SETVER.EXE %s\\WIN100.BIN 3.31", win_path);
    dbg("Running command: SETVER.EXE %s", setver_args);
    if (spawnvp(P_WAIT, "SETVER.EXE", setver_args) == 0) {
        print_page("\nOperation completed successfully.\n"
                   "Press Enter to exit.");
        while (getch() != 13);
        return 0;
    } else {
        print_page("Error: Unable to run W1SETVER.EXE.\n"
                    "Make sure SETVER.EXE is present in PATH and loaded in CONFIG.SYS.\n"
                    "When you go back to MS-DOS terminal, try going into your Windows directory\n"
                    "and running SETVER.EXE manually to see if it works.\n\n"
                    "Press F3 to exit.");
        status(25, "  F3 = Exit");
        while (getch() != 61);
        return -1;
    }    
}
