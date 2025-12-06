// Application to set correct windows path for patchmem
// remeny

#include "MPCLIB.H"
#include <process.h>
#include <stdio.h>
#include <conio.h>
#include <dir.h>
#include <stdlib.h>
#include <dos.h>

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
    char tmp[80];
    int key = 0;
    int msdos_sys_attrs = 0;
    FILE *msdos_sys;
    (void)argc;
    // Check for arguments
    validate_mpc_args(argv);

    get_screen_size();

    // Save current working directory
    getcwd(cwd, sizeof(cwd));

    // Play intro again if we absolutely need it (bruh)
    if (!arg_check(argv, "/MPC")) intro();

    title("Patchmem");
    textcolor(WHITE);

    page1:
    print_page("The Windows 95/98/SE/ME RAM Limitation Patch Program patches Windows 95, 98, "
                "98SE or ME to support Computers with more than 512MB of RAM. Unmodified "
                "Windows 95, 98, 98SE or ME can malfunction or crash when more than 512MB of "
                "RAM is present.\n");
    status("  ENTER = Next");
    print_page("  Please enter the path to your Windows 95/98/98SE/ME installation.\n");
    cprintf("     ");
    input(win_path, sizeof(win_path), "C:\\WINDOWS");
    dbg("WIN_PATH: %s", win_path);

    status("");
    wipe();
    if (win_path[0] == '\0') {
        print_page(" The path to your Windows 9x installation is empty.\n\n"
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

    // Make backup of MSDOS.SYS
    wipe();
    status("Checking for previous files...");
    if (file_exists("C:\\MSDOSBAK.MPC"))
        if (remove_file("C:\\MSDOSBAK.MPC") != 0) {
            print_page(" Error: Unable to remove existing C:\\MSDOSBAK.MPC.\n"
                        " Make sure you have write permissions to that file.\n\n"
                        " Press F3 to exit.");
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        }

    status("Checking for MSDOS.SYS...");
    if (file_exists("C:\\MSDOS.SYS")) {
        print_page("Making backup of C:\\MSDOS.SYS...");
        // Save original attributes
        if (save_attrs(&msdos_sys_attrs, "C:\\MSDOS.SYS") != 0) {
            print_page(" Error: Unable to get attributes of C:\\MSDOS.SYS.\n"
                       " Make sure you have read permissions to that file.\n\n"
                       " Press F3 to exit.");
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        }
        // Remove attributes
        status("Removing SHR attribs from C:\\MSDOS.SYS");
        if (clear_RHS("C:\\MSDOS.SYS") != 0) {
            print_page(" Error: Unable to clear attributes of C:\\MSDOS.SYS.\n"
                       " Make sure you have write permissions to that file.\n\n"
                       " Press F3 to exit.");
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        }
        // Copy MSDOS.SYS to MSDOSBAK.MPC
        status("Backing up C:\\MSDOS.SYS to C:\\MSDOSBAK.MPC");
        if (copy_file("C:\\MSDOS.SYS", "C:\\MSDOSBAK.MPC") != 0) {
            print_page(" Error: Unable to backup C:\\MSDOS.SYS.\n"
                       " Make sure you have write permissions to that file.\n\n"
                       " Press F3 to exit.");
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        }
    }

    // Dump windows path into MSDOS.SYS
    print_page("Dumping Windows path into C:\\MSDOS.SYS");
    msdos_sys = fopen("C:\\MSDOS.SYS", "w");
    if (!msdos_sys) {
        print_page(" Error: Unable to open C:\\MSDOS.SYS for writing.\n"
                   " Make sure you have write permissions to that file.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    } else {
        status("Writing new windir...");
        fprintf(msdos_sys, "[Paths]\nWINDIR=%s\n", win_path);
        fclose(msdos_sys);
    }
    
    // Execute patchmem
    title("Terminal Output - PATCHMEM.EXE");

    if (spawnl(P_WAIT, "PATCHMEM.EXE", "PATCHMEM.EXE", NULL) != 0) {
        title("Error - Patchmem not installed.");
        print_page(" Patchmem returned error.");
        
        if (yesno(false, " Would you like to try restoring the original MSDOS.SYS? [Y/N]"))
            goto restore_msdos;

        print_page(" Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    restore_msdos:
    if (remove_file("C:\\MSDOS.SYS") != 0) {
        print_page("An error occured trying to remove dummy MSDOS.SYS");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    if (file_exists("C:\\MSDOSBAK.MPC")) {
        // Restore file
        print_page("Restoring original MSDOS.SYS");
        if (copy_file("C:\\MSDOSBAK.MPC", "C:\\MSDOS.SYS") != 0) {
            print_page("An error occured trying to restore MSDOS.SYS from MSDOSBAK.MPC");
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        }
        if (remove_file("C:\\MSDOSBAK.MPC") != 0) {
            print_page("An error occured trying to remove backup MSDOSBAK.MPC");
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        }

        // Restore attributes (don't check, it is inaccurate for some reason)
        status("Restoring original attributes to C:\\MSDOS.SYS");
        (void)restore_attrs(msdos_sys_attrs, "C:\\MSDOS.SYS");
    }

    print_page(" Operation completed successfully.\n"
               " Press F3 to exit.");
    status("  F3 = Exit");
    while (getch() != 61);
    quit(0);
    return 0;
}
