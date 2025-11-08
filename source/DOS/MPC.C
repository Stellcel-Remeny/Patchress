/*
  Code for 16-bit version of Patchress
  2025 Remeny

  Compile using Turbo C++ 3.5 compiler
*/

// ---[ Include ]--- //
#include <stdio.h>
#include <conio.h>

#include "mpclib.h"

// ---[ Functions ]--- //

// ---[ Main ]--- //
int main(int argc, char *argv[]) {
    int key = 0;
    // Help documentation
    if (arg_check(argv, "/?")) {
        printf("\n  MultiPatcher Arguments\n"
             "===========================\n\n"
             "  /ni   = Disable animations\n"
             "  /v    = Verbose mode\n"
             "  /vp   = Verbose mode with pauses on statusbar update (needs /v)\n"
             "  /vlog = Verbose mode with logging (needs /v)\n"
             "  /vw   = Wait before printing each word (needs /v)\n"
             "  /?    = Show this help message\n"
             "\n");
        return 0;
    }

    flags.v_word_by_word = true;
    flags.v_pause = true;

    // Check for arguments
    if (!arg_check(argv, "/ni")) flags.animate = true;
    if (arg_check(argv, "/v")) { // Verbose/Debug mode
        flags.verbose = true;
        if (arg_check(argv, "/vp")) flags.v_pause = true;
        if (arg_check(argv, "/vlog")) flags.v_log = true;
        if (arg_check(argv, "/vw")) flags.v_word_by_word = true;
    }

    get_screen_size(); // Fill screen_rows and screen_cols before doing anything.
    dbg("INIT: TSIZE ROW: %d, COL: %d", screen_rows, screen_cols);
    intro();
    title("Remeny MultiPatcher [MS-DOS]");

    // Page 1
    textcolor(LIGHTGRAY);
    print_page("  Welcome to MultiPatcher !\n\n"
               "   This application contains some utilities.\n\n\n"
               "   Press ENTER to continue...\n");

    status("  ENTER = Continue  F3 = Exit");

    key = -1;
    while (true) {
        key = getch();
        if (key == 13) break;
        if (key == 61) quit();
        if (key == 96) crash("Crash test.");
    }

    return 0;
}