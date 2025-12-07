// Application to automate installation of winmedos.com
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
    char tmp2[80];
    int key = 0;
    (void)argc;
    // Check for arguments
    validate_mpc_args(argv);

    get_screen_size();

    // Save current working directory
    getcwd(cwd, sizeof(cwd));

    // Play intro again if we absolutely need it (bruh)
    if (!arg_check(argv, "/MPC")) intro();

    title("MS-DOS mode for Windows Me");
    textcolor(WHITE);

    page1:
    status("  ENTER = Next");
    // TODO: Restore attributes
    print_page("  File attributes [Readonly, Hidden, System] will not be restored.\n\n"
               "  This installer will initialize everything needed for the patch to work.\n\n"
               "  Please enter the path to your Windows Me installation.\n");
    cprintf("     ");
    input(win_path, sizeof(win_path), "C:\\WINDOWS");
    dbg("WIN_PATH: %s", win_path);

    status("");
    wipe();
    if (win_path[0] == '\0') {
        print_page(" The path to your Windows Me installation is empty.\n\n"
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

    if (!file_exists("%s\\COMMAND.COM", win_path) ||
        !file_exists("%s\\COMMAND\\EBD\\IO.SYS", win_path) ||
        !file_exists("%s\\SYSTEM\\REGENV32.EXE", win_path) ||
        !file_exists("%s\\WIN.COM", win_path))
    {
        print_page(" Your Windows Me installation does not contain the required files.\n\n"
                   " Press ENTER to re-enter the path, or F3 to exit.");
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

    wipe();
    // Check if required files exist in current dir
    if (!file_exists("WINMEDOS.COM"))
        crash("One or more required files not found.");

    // If our trademarked temporary directory exists, delete it
    if (dir_exists("C:\\_TMPMPC")) {
        status("Removing old temporary directory...");
        if (remove_folder("C:\\_TMPMPC") != 0) {
            print_page(" Error: Unable to remove old temporary directory C:\\_TMPMPC\n\n"
                       " Press F3 to exit.");
            status("  F3 = Exit");
            while (getch() != 61);
            quit(-1);
        }
    }

    // Make temporary directory
    status("Creating temporary directory...");
    if (mkdir("C:\\_TMPMPC") != 0) {
        print_page(" Error: Unable to create temporary directory C:\\_TMPMPC\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    // Remove attributes of COMMAND.COM, IO.SYS and REGENV32.EXE
    status("Clearing attributes...");
    // crash() was easier
    if (clear_RHS("%s\\COMMAND.COM", win_path) != 0)
        crash("Cannot clear attribs COMMAND.COM");
    if (clear_RHS("%s\\COMMAND\\EBD\\IO.SYS", win_path) != 0)
        crash("Cannot clear attribs IO.SYS");
    if (clear_RHS("%s\\SYSTEM\\REGENV32.EXE", win_path) != 0)
        crash("Cannot clear attribs REGENV32.EXE");

    // Copy needed items to temporary directory
    status("Copying IO.SYS...");
    sprintf(tmp, "%s\\COMMAND\\EBD\\IO.SYS", win_path);
    if (copy_file(tmp, "C:\\_TMPMPC\\IO.SYS") != 0) {
        print_page(" Error: Unable to copy IO.SYS to temporary directory C:\\_TMPMPC.\n"
                   " Make sure you have write permissions.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    status("Copying COMMAND.COM...");
    sprintf(tmp, "%s\\COMMAND.COM", win_path);
    if (copy_file(tmp, "C:\\_TMPMPC\\COMMAND.COM") != 0) {
        print_page(" Error: Unable to copy COMMAND.COM to temporary directory C:\\_TMPMPC.\n"
                   " Make sure you have write permissions.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    status("Copying REGENV32.EXE...");
    sprintf(tmp, "%s\\SYSTEM\\REGENV32.EXE", win_path);
    if (copy_file(tmp, "C:\\_TMPMPC\\REGENV32.EXE") != 0) {
        print_page(" Error: Unable to copy REGENV32.EXE to temporary directory C:\\_TMPMPC.\n"
                   " Make sure you have write permissions.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    status("Copying WINMEDOS.COM...");
    if (copy_file("WINMEDOS.COM", "C:\\_TMPMPC\\WINMEDOS.COM") != 0) {
        print_page(" Error: Unable to copy WINMEDOS.COM to temporary directory C:\\_TMPMPC.\n"
                   " Make sure you have write permissions.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    // Switch to temporary directory and run WINMEDOS.COM
    status("Switching to temporary directory...");
    intro_reverse();
    _chdrive(3); // C: is usually 3
    chdir("C:\\_TMPMPC");
    clrscr();
    if (spawnl(P_WAIT, "WINMEDOS.COM", NULL) != 0) {
        status(" Press any key to return...");
        getch();
        title("Errr");
        print_page(" Error: WINMEDOS.COM failed to run correctly.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    status(" Press any key to apply the patches...");
    getch();

    intro();
    title("MS-DOS mode for Windows Me");

    // Backup old files
    status("Backing up Windows COMMAND.COM...");

    if (file_exists("%s\\COMMAND.BAK", win_path))
        remove_file("%s\\COMMAND.BAK", win_path);

    sprintf(tmp, "%s\\COMMAND.COM", win_path);
    sprintf(tmp2, "%s\\COMMAND.BAK", win_path);

    if (rename(tmp, tmp2) != 0) {
        print_page(" Error: Unable to backup COMMAND.COM.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    // attrib clear of c:\command.com
    status("Clearing attributes of C:\\COMMAND.COM...");
    (void)clear_RHS("C:\\COMMAND.COM");
    
    status("Backing up C:\\COMMAND.COM...");

    if (file_exists("C:\\COMMAND.BAK"))
        remove_file("C:\\COMMAND.BAK");

    if (rename("C:\\COMMAND.COM", "C:\\COMMAND.BAK") != 0) {
        print_page(" Error: Unable to backup C:\\COMMAND.COM.\n"
                   " Unfortunately, you must restore previous files manually by renaming the .BAK file.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    // attrib clear of io.sys
    status("Clearing attributes of IO.SYS...");
    if (clear_RHS("C:\\IO.SYS") != 0) {
        print_page(" Error: Unable to clear attributes of C:\\IO.SYS.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    status("Backing up IO.SYS...");

    if (file_exists("C:\\IO.BAK"))
        remove_file("C:\\IO.BAK");

    if (rename("C:\\IO.SYS", "C:\\IO.BAK") != 0) {
        print_page(" Error: Unable to backup C:\\IO.SYS.\n"
                   " Unfortunately, you must restore previous files manually by renaming the .BAK file.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    status("Backing up REGENV32.EXE...");

    if (file_exists("%s\\SYSTEM\\REGENV32.BAK", win_path))
        remove_file("%s\\SYSTEM\\REGENV32.BAK", win_path);

    sprintf(tmp, "%s\\SYSTEM\\REGENV32.EXE", win_path);
    sprintf(tmp2, "%s\\SYSTEM\\REGENV32.BAK", win_path);

    if (rename(tmp, tmp2) != 0) {
        print_page(" Error: Unable to backup REGENV32.EXE.\n"
                   " Unfortunately, you must restore previous files manually by renaming the .BAK file.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    // Move the modified files
    status("Installing patched COMMAND.COM...");
    sprintf(tmp, "%s\\COMMAND.COM", win_path);

    if (copy_file("C:\\_TMPMPC\\COMMAND.COM", tmp) != 0) {
        print_page(" Error: Unable to install patched COMMAND.COM to the Windows directory\n"
                   " Please restore previous files from their .BAK backups.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);        
    }

    if (move_file("C:\\_TMPMPC\\COMMAND.COM", "C:\\COMMAND.COM") != 0) {
        print_page(" Error: Unable to install patched COMMAND.COM to the C:\\ drive.\n"
                   " Please restore previous files from their .BAK backups.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);        
    }

    status("Installing patched IO.SYS...");

    if (move_file("C:\\_TMPMPC\\IO.SYS", "C:\\IO.SYS") != 0) {
        print_page(" Error: Unable to install patched IO.SYS to C:\\\n"
                   " Please restore previous files from their .BAK backups.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);        
    }

    status("Installing patched REGENV32.EXE...");
    sprintf(tmp, "%s\\SYSTEM\\REGENV32.EXE", win_path);

    if (move_file("C:\\_TMPMPC\\REGENV32.EXE", tmp) != 0) {
        print_page(" Error: Unable to install patched REGENV32.EXE\n"
                   " Please restore previous files from their .BAK backups.\n\n"
                   " Press F3 to exit.");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    // Clean temporary directory
    status("Cleaning temporary files...");
    chdir(".."); // So we can delete the directory
    _chdrive((toupper(cwd[0]) - 'A') + 1);
    if (remove_folder("C:\\_TMPMPC") != 0) {
        print_page(" Warning: Unable to remove temporary directory C:\\_TMPMPC.\n"
                   " Please remove it manually.\n\n"
                   " Press ENTER to continue.");
        status("  ENTER = Continue");
        while (getch() != 13);
        wipe();
    }

    status("Updating C:\\CONFIG.SYS...");
    if (file_append("C:\\CONFIG.SYS", "\nDEVICE=%s\\IFSHLP.SYS\n", win_path) != 0) {
        print_page(" Warning: Could not update CONFIG.SYS.\n"
                   " Please add the following manually:\n\n"
                   "    DEVICE=%s\\IFSHLP.SYS\n\n"
                   " Press ENTER to continue.", win_path);
        status("  ENTER = Continue");
        while (getch() != 13);
        wipe();
    }

    if(yesno(false, "\n Would you like to automatically load WIN.COM at startup?")) {
        status("Updating C:\\AUTOEXEC.BAT...");
        if (file_append("C:\\AUTOEXEC.BAT", "\n%s\\WIN.COM\n", win_path) != 0) {
            print_page(" Warning: Could not update AUTOEXEC.BAT.\n"
                       " Please add the following manually:\n\n"
                       "    %s\\WIN.COM\n\n"
                       " Press ENTER to continue.", win_path);
            status("  ENTER = Continue");
            while (getch() != 13);
            wipe();
        }
    }

    print_page("\n Installation completed.\n\n"
               " Press F3 to exit.");
    status("  F3 = Exit");
    while (getch() != 61);
    quit(0);
    return 0;
}
