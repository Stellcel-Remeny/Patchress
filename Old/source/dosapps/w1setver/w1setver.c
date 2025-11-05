// Application to change the reported DOS version (unnecessary app but ok)
// remeny

#include "patchress_dos.h"
#include <process.h>

int main(int argc, char* argv[]) {
    screen_rows = _setvideomode(_TEXTC80);
    
    if (screen_rows == 0) {
       printf("I was unable to set the video mode.\r\n");
       return -1;
    }

    // Check for arguments
    if (arg_check(argv, "/v")) {
        flags.verbose = true;
        if (arg_check(argv, "/vp")) flags.v_pause = true;
    }

    char win_path[60] = {0};
    char dos_path[60] = {0};
    char setver_args[128] = {0};
    int key = 0;

    intro();
    title("Set reported DOS version for Windows 1.0");

    page1:
    print_page("This application runs SETVER.EXE on WIN100.BIN\n"
               "to set the reported DOS version to 3.31.\n\n");
    status(screen_rows, "  ENTER = Continue");
    print("  Please enter the path to your Windows 1.0 installation.\n\n");
    print("     ");
    input(win_path, sizeof(win_path), "C:\\WINDOWS");
    print("\n\n  Please enter the path of your current DOS installation.\n\n");
    status(screen_rows, "  ENTER = Continue");
    print("     ");
    input(dos_path, sizeof(dos_path), "C:\\DOS");

    wipe();
    if (win_path[0] == '\0' || dos_path[0] == '\0') {
        print_page("Trying to troll me? One of the paths is empty.\n"
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
    print_page("The paths you entered are:\n"
               " DOS: %s\n"
               " WINDOWS: %s\n\n"
               "If this is correct, press ENTER to continue, or ESC to re-enter the paths.\n"
               "You can also press F3 to quit now.\n", dos_path, win_path);
    status(screen_rows, "  F3 = Exit  ESC = Go back  ENTER = Continue");

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

    save_screen();

    dbg("Running command: SETVER.EXE %s", setver_args);
    int ret = spawnvp(P_WAIT, "SETVER.EXE", setver_args);

    restore_screen();

    if (ret == 0) {
        print_page("\nOperation completed successfully.\n"
                   "Press Enter to exit.");
        while (getch() != 13);
        return 0;
    } else {
        print_page("Error: Unable to run SETVER.EXE.\n"
                    "Make sure SETVER.EXE is present in PATH and loaded in CONFIG.SYS.\n"
                    "When you go back to MS-DOS terminal, try going into your Windows directory\n"
                    "and running SETVER.EXE manually to see if it works.\n\n"
                    "Press F3 to exit.");
        status(25, "  F3 = Exit");
        while (getch() != 61);
        return -1;
    }
}
