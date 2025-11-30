// Application to install XMGR.SYS or HIMEMX.EXE
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
    char tmp[80] = {0};
    char *list[] = { "XMGR", "HIMEMX", NULL };
    long himem_mem_limit = 0;
    int key = 0;
    int choice = -1;
    bool use_xmgr = false; // If true, use xmgr. If false, use HIMEMX.
    FILE *config_sys;
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

    title("Memory Manager Setup");
    textcolor(WHITE);

    page1:
    print_page("  XMgr is an XMS manager which handles up to 4-GB of RAM and supports V3.70+ UMBPCI. \n\n"
               "  HimemX is an XMS memory manager. It's derived from FDHimem with bugfixes, optimizations and extensions.\n\n"
               "  What do you want Setup to install?\n");
    status("  ENTER = Select  F3 = Exit");

    // Expect only -2, 0, 1 as the return values
    cprintf("     ");
    choice = selector(false, true, list);
    if      (choice == -2) { quit(-1); }
    else if (choice == 0) {  // XMGR
        dbg("XMGR");
        use_xmgr = true;
    }
    else if (choice == 1) {  // HIMEMX
        dbg("HIMEMX");
        use_xmgr = false;
        print_page("\n Memory limit for HIMEMX in *KB* (0/Blank = No limit) (Set to 256000 for Win3x)\n");
        status("  ENTER = Continue");
        cprintf("     ");
        input_num(&himem_mem_limit, 16, 256000);
    }
    print_page("\n  Please enter the path where the memory manager shall be installed.\n");
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
    // Check if installation exist in current dir
    if (!file_exists("XMGR.SYS") || !(file_exists("HIMEMX.EXE")))
        crash("One or more required files not found.");

    status("Checking for previous files and removing...");

    if (use_xmgr) {  // INSTALL XMGR
        // Delete file if already exist
        if (file_exists("%s\\XMGR.SYS", ins_path))
            remove_file("%s\\XMGR.SYS", ins_path);

        // Install file
        status("Copying XMGR.SYS...");
        sprintf(tmp, "%s\\XMGR.SYS", ins_path);
        if (copy_file("XMGR.SYS", tmp) != 0) {
            print_page(" Error: Unable to copy XMGR.SYS to %s.\n"
                    " Make sure you have write permissions to that directory.\n\n"
                    " Press F3 to exit.", ins_path);
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
                    "    DEVICE=%s\\XMGR.SYS\n\n"
                    " Setup successfully copied XMGR.SYS to %s.\n"
                    " Press F3 to exit.", ins_path, ins_path);
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        } else {
            fprintf(config_sys, "\nDEVICE=%s\\XMGR.SYS\n", ins_path);
            fclose(config_sys);
        }
    } else {  // INSTALL HIMEMX
        // Delete file if already exist
        if (file_exists("%s\\HIMEMX.EXE", ins_path))
            remove_file("%s\\HIMEMX.EXE", ins_path);

        // Install file
        status("Copying HIMEMX.EXE...");
        sprintf(tmp, "%s\\HIMEMX.EXE", ins_path);
        if (copy_file("HIMEMX.EXE", tmp) != 0) {
            print_page(" Error: Unable to copy HIMEMX.EXE to %s.\n"
                    " Make sure you have write permissions to that directory.\n\n"
                    " Press F3 to exit.", ins_path);
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        }

        // Add line to CONFIG.SYS
        status("Updating C:\\CONFIG.SYS...");
        config_sys = fopen("C:\\CONFIG.SYS", "a");
        if (config_sys == NULL) {
            print_page(" Error: Unable to open C:\\CONFIG.SYS for writing.\n"
                    " You must add the following to your CONFIG.SYS manually:\n");

            if (himem_mem_limit == 0) {
                print_page("    DEVICE=%s\\HIMEMX.EXE\n", ins_path);
            } else {
                print_page("    DEVICE=%s\\HIMEMX.EXE /MAX=%ld\n", ins_path, himem_mem_limit);
            }

            print_page("\n Setup successfully copied HIMEMX.EXE to %s.\n"
                       " Press F3 to exit.", ins_path);
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        } else {
            if (himem_mem_limit == 0) {
                fprintf(config_sys, "\nDEVICE=%s\\HIMEMX.EXE\n", ins_path);
            } else {
                fprintf(config_sys, "\nDEVICE=%s\\HIMEMX.EXE /MAX=%ld\n", ins_path, himem_mem_limit);
            }
            fclose(config_sys);
        }
    }

    print_page("\n Operation completed successfully.\n"
               " You must restart to load the new memory manager.\n"
               " If HIMEM.SYS is also in C:\\CONFIG.SYS, you MUST comment it out.\n\n"
               " Press F3 to exit.");
    status("  F3 = Exit");
    while (getch() != 61);
    quit(0);

    // to shut up
    return 0;
}
