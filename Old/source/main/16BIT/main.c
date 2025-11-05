/*
    Remeny Patchress
    16-Bit Application for MS-DOS
    Feel free to use this for whatever,
    but I highly doubt it's useful.

    (C) Remeny 2025
    // 31st August, 2025
*/
//
// TIP: Please don't code like yandere simulator
//
#include <direct.h>
#include <limits.h>
#include "patchress_dos.h"
#include "minIni.h"

// ---[ Defines ]--- //
#define status(fmt, ...) status(screen_rows, fmt, ##__VA_ARGS__)
#define MAX_ENTRIES 50         // Max menu/entry items

// ---[ Global variables ]--- //
int screen_rows = 0;
char starting_directory[PATH_MAX] = {0};

// ---[ Structures ]--- //
typedef struct {
    char directory[PATH_MAX];
    char long_name[64];
    char version[32];
    char description[512];
    char author[64];
    char exe[16];
    char args[128];
} Entry;

// ---[ Functions ]--- //


// ---[ Main ]--- //

int main(int argc, char* argv[]) {
    if (arg_check(argv, "/?")) {
        printf("\n  MultiPatcher Arguments\n"
             "===========================\n\n"
             "  /ni   = Disable animations\n"
             "  /v    = Verbose mode\n"
             "  /vp   = Verbose mode with pauses (needs /v) [Not best to combine /vw]\n"
             "  /vlog = Verbose mode with logging (needs /v) [Filename: PATCHX16.log]\n"
             "  /vw   = Wait before printing each word (needs /v)\n"
             "  /?    = Show this help message\n"
             "\n");
        return 0;
    }
    screen_rows = _setvideomode(_TEXTC80);
    
    if (screen_rows == 0) {
       printf("I was unable to set the video mode.\r\n");
       return -1;
    }

    // Check for arguments
    if (!arg_check(argv, "/ni")) flags.animate = true;
    if (arg_check(argv, "/v")) {
        flags.verbose = true;
        if (arg_check(argv, "/vp")) flags.v_pause = true;
        if (arg_check(argv, "/vlog")) {
            flags.v_log = true;
            // Logfile name with directory
            _fullpath(logfile, "PATCHX16.log", sizeof(logfile));
        }
        if (arg_check(argv, "/vw")) flags.v_word_by_word = true;
    }

    // PAGE 1
    _fullpath(starting_directory, ".", sizeof(starting_directory));
    dbg("New session");
    dbg("S_DIR: %s", starting_directory);

    int key = 0;

    intro();
    title("Remeny MultiPatcher [MS-DOS]");

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

    // PAGE 2
    int entry_selected = false;
    while (!entry_selected)
    wipe();
    print_page("  Please select an item from below.");
    status("  UP = Previous  DOWN = Next  ENTER = Select  F3 = Exit");
    //user_select_entry("RES");
    
    dbg("Session terminated due to main() end.");
    return 0;
}
