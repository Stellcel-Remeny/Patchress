// Application to install cutemouse
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

    title("Cutemouse Setup");
    textcolor(WHITE);

    page1:
    print_page("  CuteMouse is a DOS based, open source mouse driver, which supports many protocols of serial and PS/2 mice. \n\n"
               "  This application copies CTMOUSE.EXE, MOUSETST.COM, and PROTOCOL.COM.\n");
    status("  ENTER = Next");
    print_page("  Please enter the path where Cutemouse shall be installed.\n");
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
    // Check if cutemouse exist in current dir
    if (!file_exists("CTMOUSE.EXE") || !file_exists("MOUSETST.COM") || !file_exists("PROTOCOL.COM"))
        crash("One or more required files not found.");

    status("Checking for previous files...");
    // Do not proceed if cutemouse files already exist
    if (file_exists("%s\\CTMOUSE.EXE", ins_path)) {
        print_page(" Cutemouse seems to be already installed.\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    // We don't care about these
    if (file_exists("%s\\MOUSETST.COM", ins_path))
        remove_file("%s\\MOUSETST.COM", ins_path);

    if (file_exists("%s\\PROTOCOL.COM", ins_path))
        remove_file("%s\\PROTOCOL.COM", ins_path);

    // Install Cutemouse
    status("Copying CTMOUSE.EXE...");
    sprintf(tmp, "%s\\CTMOUSE.EXE", ins_path);
    if (copy_file("CTMOUSE.EXE", tmp) != 0) {
        print_page(" Error: Unable to copy CTMOUSE.EXE to %s.\n"
                   " Make sure you have write permissions to that directory.\n\n"
                   " Press F3 to exit.", ins_path);
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    status("Copying MOUSETST.COM...");
    sprintf(tmp, "%s\\MOUSETST.COM", ins_path);
    if (copy_file("MOUSETST.COM", tmp) != 0) {
        print_page(" Error: Unable to copy MOUSETST.COM to %s.\n"
                   " Make sure you have write permissions to that directory.\n\n"
                   " Press F3 to exit.", ins_path);
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    status("Copying PROTOCOL.COM...");
    sprintf(tmp, "%s\\PROTOCOL.COM", ins_path);
    if (copy_file("PROTOCOL.COM", tmp) != 0) {
        print_page(" Error: Unable to copy PROTOCOL.COM to %s.\n"
                   " Make sure you have write permissions to that directory.\n\n"
                   " Press F3 to exit.", ins_path);
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    // Add line to AUTOEXEC.BAT
    if(!yesno(" Do you want to add CTMOUSE.EXE to C:\\AUTOEXEC.BAT? [Y/N]")) {
        print_page("\n Setup successfully copied cutemouse to %s.\n"
                   " Cutemouse will not be loaded automatically on startup.\n"
                   " Press F3 to exit.", ins_path);
        status("  F3 = Exit");
        while (getch() != 61);
        quit(0);
    }
    status("Updating C:\\AUTOEXEC.BAT...");
    autoexec_bat = fopen("C:\\AUTOEXEC.BAT", "a");
    if (autoexec_bat == NULL) {
        print_page(" Error: Unable to open C:\\AUTOEXEC.BAT for writing.\n"
                   " You must add the following to your AUTOEXEC.BAT manually:\n\n"
                   "    %s\\CTMOUSE.EXE\n\n"
                   " Setup successfully copied cutemouse to %s.\n"
                   " Press F3 to exit.", ins_path, ins_path);
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    } else {
        fprintf(autoexec_bat, "\n%s\\CTMOUSE.EXE\n", ins_path);
        fclose(autoexec_bat);
    }

    print_page("\n Operation completed successfully.\n"
               " You must restart to load Cutemouse.\n\n"
               " Please ensure that CTMOUSE.EXE is properly loaded in C:\\AUTOEXEC.BAT.\n"
               " If the following line does not exist, add it:\n\n"
               "    %s\\CTMOUSE.EXE\n\n"
               " Press F3 to exit.", ins_path);
    status("  F3 = Exit");
    while (getch() != 61);
    if (!arg_check(argv, "/MPC")) intro();
    quit(0);

    // to shut up
    return 0;
}
