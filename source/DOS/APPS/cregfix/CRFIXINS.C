// Application to install CREGFIX
// remeny

#include "MPCLIB.H"
#include "MININI.H"
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

int add_vxd_ini(const char *winDir) {
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
            fputs("device=CREGFIX.VXD\n", out);
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
    char ins_path[60] = {0};
    char tmp[80];
    int key = 0;
    int choice = -1;
    char *list[] = { "CREGFIX.VXD", "CREGFIX.SYS", NULL };
    bool use_vxd = false;
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

    title("CREGFIX Setup");
    textcolor(WHITE);

    page1:
    print_page("  CREGFIX is a small DOS driver that works around an issue of many modern CSM"
               " BIOS implementations where certain control register bits are left \"dirty\", thus"
               " causing issues when trying to run legacy operating systems such as Microsoft"
               " Windows 9x (see \"While initializing device VCACHE: Windows protection error\""
               " issue) or while trying to run EMM386.EXE.\n\n"
               "  What do you want Setup to install?\n");
    status("  ENTER = Select  F3 = Exit");

    // Expect only -2, 0, 1 as the return values
    cprintf("     ");
    choice = selector(false, true, list);
    if      (choice == -2) { quit(-1); }
    else if (choice == 0) {  // CREGFIX.VXD
        dbg("cregfix.vxd");
        use_vxd = true;
        print_page("\n  Please enter the path to your Windows installation.\n");
        status("  ENTER = Continue");
        cprintf("     ");
        input(ins_path, sizeof(ins_path), "C:\\WINDOWS");
        wipe();
        // Check if SYSTEM.INI exists in the Windows path
        if (!file_exists("%s\\SYSTEM.INI", ins_path)) {
            print_page(" SYSTEM.INI file is not found in specified Windows path.\n"
                    " You must go back and type in a valid directory.\n\n"
                    " Press ENTER to go back, or F3 to exit."
                    );
            status("  ENTER = Go Back  F3 = Exit");
            goto keychk;
        }
        // Check if SYSTEM.CB exists in the Windows path
        if (!file_exists("%s\\SYSTEM.CB", ins_path)) {
            print_page(" SYSTEM.CB file is not found in specified Windows path.\n"
                    " You must go back and type in a valid directory.\n\n"
                    " Press ENTER to go back, or F3 to exit."
                    );
            status("  ENTER = Go Back  F3 = Exit");
            goto keychk;
        }
    }
    else if (choice == 1) {  // CREGFIX.SYS
        dbg("cregfix.sys");
        use_vxd = false;
        print_page("\n  Please enter the path where CREGFIX shall be installed.\n");
        status("  ENTER = Continue");
        cprintf("     ");
        input(ins_path, sizeof(ins_path), "C:\\DOS");
    }

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
    // Check if installation files exist in current dir
    if (!file_exists("CREGFIX.SYS") || !file_exists("CREGFIX.VXD"))
        crash("One or more required files not found.");

    status("Checking for previous files...");
    // Delete if cregfix files already exist
    if (file_exists("%s\\CREGFIX.SYS", ins_path))
        remove_file("%s\\CREGFIX.SYS", ins_path);

    if (file_exists("%s\\CREGFIX.VXD", ins_path))
        remove_file("%s\\CREGFIX.VXD", ins_path);

    // Install CREGFIX
    if (use_vxd) {  // INSTALL CREGFIX.VXD
        status("Copying CREGFIX.VXD...");
        sprintf(tmp, "%s\\SYSTEM\\CREGFIX.VXD", ins_path);
        if (copy_file("CREGFIX.VXD", tmp) != 0) {
            print_page(" Error: Unable to copy CREGFIX.VXD to %s\\SYSTEM.\n"
                    " Make sure you have write permissions to that directory.\n\n"
                    " Press F3 to exit.", ins_path);
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        }

        // Add line to SYSTEM.INI
        status("Updating %s\\SYSTEM.INI...", ins_path);

        if (add_vxd_ini(ins_path) != 0) {            
            title("Error");
            print_page(" An error occured trying to update SYSTEM.INI.\n"
                    " Press F3 to exit.");
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        }
        // Add line to SYSTEM.CB
        status("Updating %s\\SYSTEM.CB...", ins_path);
        // For this, we assume [386enh] does not exist (my case). So it plays nicely with MININI
        sprintf(tmp, "%s\\SYSTEM.CB", ins_path);
        if (!ini_puts("386Enh", "device", "CREGFIX.VXD", tmp)) {
            title("Error");
            print_page(" An error occured trying to update SYSTEM.CB.\n"
                    " Press F3 to exit.");
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        }
    }
    else {  // INSTALL CREGFIX.SYS        
        status("Copying CREGFIX.SYS...");
        sprintf(tmp, "%s\\CREGFIX.SYS", ins_path);
        if (copy_file("CREGFIX.SYS", tmp) != 0) {
            print_page(" Error: Unable to copy CREGFIX.SYS to %s.\n"
                    " Make sure you have write permissions to that directory.\n\n"
                    " Press F3 to exit.", ins_path);
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        }

        // Add line
        status("Updating C:\\CONFIG.SYS...");
        if (file_prepend("C:\\CONFIG.SYS", "DEVICE=%s\\CREGFIX.SYS", ins_path) != 0) {
            print_page(" Error: An error occured while trying to edit C:\\CONFIG.SYS.\n"
                    " You must add the following at the top of your CONFIG.SYS manually:\n\n"
                    "    DEVICE=%s\\CREGFIX.SYS\n\n"
                    " Press F3 to exit.", ins_path);
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        }
    }

    print_page("\n Operation completed successfully.\n"
               " You must restart to load CREGFIX.\n\n"
               " Press F3 to exit.");
    status("  F3 = Exit");
    while (getch() != 61);
    quit(0);

    // to shut up
    return 0;
}
