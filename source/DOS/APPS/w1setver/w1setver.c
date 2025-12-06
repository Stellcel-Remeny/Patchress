// Application to change the reported DOS version (unnecessary app but ok)
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
    char dos_path[60] = {0};
    char tmp[80];
    int key = 0, ret = 0;
    FILE *config_sys;
    (void)argc;
    // Check for arguments
    validate_mpc_args(argv);
    
    get_screen_size();

    // Save current working directory
    getcwd(cwd, sizeof(cwd));

    // Play intro again if we absolutely need it (bruh)
    if (!arg_check(argv, "/MPC")) intro();

    title("Set reported DOS version for Windows 1.0");
    textcolor(WHITE);

    page1:
    print_page("  This application runs SETVER.EXE on WIN100.BIN\n"
               "  to set the reported DOS version to 3.31.\n");
    status("  ENTER = Next");
    print_page("  Please enter the path to your Windows 1.0 installation.\n");
    cprintf("     ");
    input(win_path, sizeof(win_path), "C:\\WINDOWS");
    dbg("WIN_PATH: %s", win_path);
    print_page("\n\n  Please enter the path of your current DOS installation.\n");
    status("  ENTER = Next");
    cprintf("     ");
    input(dos_path, sizeof(dos_path), "C:\\DOS");
    dbg("DOS_PATH: %s", dos_path);
    dbg("DCHECK WIN_PATH: %s", win_path);

    status("");
    wipe();
    if (win_path[0] == '\0' || dos_path[0] == '\0') {
        if (win_path[0] == '\0') {
            print_page(" The path to your Windows 1.0 installation is empty.\n");
        } else {
            print_page(" The path to your MS-DOS installation is empty.\n"
                       " If you use the DOS prompt of any Windows 9x installations and you got\n"
                       " confused, you should point the path to:\n\n"
                       "    <drive>:\\<win9x_installation>\\COMMAND\n\n");
        }
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

    // Check if WIN100.BIN exists in the Windows path
    if (!file_exists("%s\\WIN100.BIN", win_path)) {
        print_page(" WIN100.BIN file is not found in specified Windows path.\n"
                   " You must go back and type in a valid directory.\n\n"
                   " Press ENTER to go back, or F3 to exit."
                  );
        status("  ENTER = Go Back  F3 = Exit");
        goto keychk;
    }

    print_page(" The paths you entered are:\n\n"
               "  DOS: %s\n"
               "  WINDOWS: %s\n\n"
               " If this is correct, press ENTER to continue, or ESC to re-enter the paths.\n"
               " You can also press F3 to quit now.\n", dos_path, win_path);
    status("  ENTER = Continue  ESC = Go back  F3 = Exit  ");

    while (key != 13) {
        key = getch();
        if (key == 27) {
            wipe();
            goto page1;
        } else if (key == 61) {
            quit(0);
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
                break;
            } else if (key == 61) {
                quit(0);
            }
        }
        // Copy SETVER.EXE from current directory to DOS path
        status("Copying SETVER.EXE to %s...", dos_path);
        sprintf(tmp, "%s\\SETVER.EXE", dos_path);
        if (copy_file("SETVER.EXE", tmp) != 0) {
            print_page(" Error: Unable to copy SETVER.EXE to %s.\n"
                       " Make sure you have write permissions to that directory.\n\n"
                       " Press F3 to exit.", dos_path);
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
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
            while (1) {
                key = getch();
                if (key == 13) { break; }
                else if (key == 61) { quit(-1); }
            }
        } else {
            fprintf(config_sys, "\nDEVICE=%s\\SETVER.EXE\n", dos_path);
            fclose(config_sys);
        }
    }
    wipe();
    status("Setting reported DOS version to 3.31...");

    // Switch to path containing WIN100.BIN
    _chdrive((toupper(win_path[0]) - 'A') + 1);
    chdir(win_path);

    // reuse tmp to build path to SETVER.EXE
    sprintf(tmp, "%s\\SETVER.EXE", dos_path);
    dbg("%s WIN100.BIN 3.31", tmp);

    title("Terminal Output");

    ret = spawnl(P_WAIT,
                 tmp,
                 tmp,
                 "WIN100.BIN",
                 "3.31",
                 NULL);

    if (ret == 0) {
        print_page("\n Operation completed successfully.\n"
                   " Please ensure that SETVER.EXE is properly loaded in C:\\CONFIG.SYS.\n"
                   " If the following line does not exist, add it:\n\n"
                   "    DEVICE=%s\\SETVER.EXE\n\n"
                   " Press F3 to exit.", dos_path);
        status("  F3 = Exit");
        while (getch() != 61);
        quit(0);
    } else {
        title("Error");
        print_page("Error: Unable to run SETVER.EXE.\n"
                    " When you go back to MS-DOS terminal, try running the following:\n\n"
                    "     cd %s\n"
                    "     %s\\SETVER.EXE WIN100.BIN 3.31\n\n"
                    " After that, add the following to C:\\CONFIG.SYS:\n\n"
                    "     DEVICE=%s\\SETVER.EXE\n\n"
                    " Press F3 to exit.", win_path, dos_path, dos_path);
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    return 0;
}
