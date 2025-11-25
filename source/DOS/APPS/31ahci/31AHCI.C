// Application to install AHCIFIX.386
// remeny

#define INI_ANSIONLY

#include "MPCLIB.H"
#include "MININI.H"
#include <stdio.h>
#include <conio.h>
#include <dir.h>
#include <stdlib.h>
#include <string.h>

char cwd[MAXPATH];

void quit(int ret) {
    if (cwd[0] != '\0') {
        _chdrive((toupper(cwd[0]) - 'A') + 1); // Starting drive
        chdir(cwd); // Return to starting directory
    }
    intro_reverse(); 
    exit(ret);
}

int add_ahcifix(const char *winDir) {
    char ini[260], tmp[260];
    FILE *in, *out;
    char line[512];
    int in386 = 0;

    /* Build paths */
    sprintf(ini, "%s\\SYSTEM.INI", winDir);
    sprintf(tmp, "%s\\SYSTEM.TMP", winDir);

    in  = fopen(ini, "r");
    if(!in) return 1;

    out = fopen(tmp, "w");
    if(!out) { fclose(in); return 1; }

    while(fgets(line, sizeof(line), in)) {
        if(!strncmp(line, "[386Enh]", 8)) {
            in386 = 1;
            fputs(line, out);
            continue;
        }

        if(in386) {
            fputs("device=ahcifix.386\n", out);
            in386 = 0;
        }

        fputs(line, out);

        if(line[0] == '[')
            in386 = 0;
    }

    fclose(in);
    fclose(out);

    remove(ini);
    rename(tmp, ini);

    return 0;
}

int main(int argc, char* argv[]) {
    char win_path[60] = {0};
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

    title("AHCIFIX.386 for Windows 3.1");
    textcolor(WHITE);

    page1:
    print_page("This is a small and simple Virtual Device Driver (\"VxD\") for Windows 3.1 in 386 Enhanced Mode. Its purpose is to work around two bugs in the firmware for Intel AHCI controllers, which normally cause Windows 3.1 Enhanced Mode to crash on disk access.\n");
    print_page(" This program installs the AHCIFIX.386 file into your Windows 3.1 installation.\n\n");
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

    // Check if SYSTEM.INI exists in the Windows path
    if (!file_exists("%s\\SYSTEM.INI", win_path)) {
        print_page(" SYSTEM.INI file is not found in specified Windows path.\n"
                   " You must go back and type in a valid directory.\n\n"
                   " Press ENTER to go back, or F3 to exit."
                  );
        status("  ENTER = Go Back  F3 = Exit");
        goto keychk;
    }

    print_page(" The path you entered is:\n\n"
               "  WINDOWS: %s\n\n"
               " If this is correct, press ENTER to continue, or ESC to re-enter the paths.\n"
               " You can also press F3 to quit now.\n", win_path);
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

    status("Checking for previous files...");
    wipe();
    // Check if AHCIFIX.386 already exists
    if (file_exists("%s\\SYSTEM\\AHCIFIX.386", win_path)) {
        print_page(" AHCIFIX.386 seems to be already installed.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }
    // Copy AHCIFIX.386 from current directory to WIN path
    status("Copying AHCIFIX.386 to %s\\SYSTEM...", win_path);
    sprintf(tmp, "%s\\SYSTEM\\AHCIFIX.386", win_path);
    if (copy_file("AHCIFIX.386", tmp) != 0) {
        print_page(" Error: Unable to copy AHCIFIX.386 to %s\\SYSTEM.\n"
                   " Make sure you have write permissions to that directory.\n\n"
                   " Press F3 to exit.", win_path);
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    // Add line to SYSTEM.INI
    status("Updating %s\\SYSTEM.INI...", win_path);

    if (add_ahcifix(win_path) == 0) {
        print_page("\n Operation completed successfully.\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        if (!arg_check(argv, "/MPC")) intro();
        quit(0);
    } else {
        title("Error");
        print_page(" An error occured.\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    return 0;
}
