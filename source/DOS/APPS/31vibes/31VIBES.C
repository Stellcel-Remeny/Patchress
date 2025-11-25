// Application to install vbesvga
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
    int key = 0, ret = 0;
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

    title("VBESVGA for Windows 3.1");
    textcolor(WHITE);

    page1:
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

    // Execute SETUP.EXE
    ret = spawnl(P_WAIT,
                 "SETUP.EXE",
                 "SETUP.EXE",
                 win_path,
                 NULL);

    if (ret != 0) {
        err_msg:
        getch();
        title("Error");
        print_page("An error occured.\n");
        status("  F3 = Exit");
        while (getch() != 61);
        quit(-1);
    }

    // Execute AUXCHECK.COM
    ret = spawnl(P_WAIT,
                 "AUXCHECK.COM",
                 "AUXCHECK.COM",
                 NULL);
    if (ret != 0) goto err_msg;

    // Ask user if they want to install AUXSTACK.COM
    if (!yesno(false, "\n\n Do you want to install AUXSTACK.COM? (Modifies AUTOEXEC.BAT) [Y/N]"))
        quit(0);
    
    // Install AUXSTACK.COM
    // Copy file to Windows installation
    intro();
    title(" AUXSTACK.COM Installation");
    print_page(" Copying AUXSTACK.COM to %s\n", win_path);
    if (copy_file("AUXSTACK.COM", fmt_str("%s\\AUXSTACK.COM", win_path)) != 0)
        goto err_msg;

    // Add line to AUTOEXEC.BAT
    print_page(" Appending to C:\\AUTOEXEC.BAT");
    if (file_append("C:\\AUTOEXEC.BAT", "\n%s\\AUXSTACK.COM\n", win_path) != 0)
        goto err_msg;

    print_page(" Installation completed.\n"
               " Restart your computer for changes to take effect.");
    status(" Finished. Press F3 to exit.");
    while (getch() != 61);
    quit(0);
    return 0;
}
