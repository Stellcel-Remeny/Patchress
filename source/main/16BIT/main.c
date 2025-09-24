/*
    Remeny Patchress
    16-Bit Application for MS-DOS
    Feel free to use this for whatever,
    but I highly doubt it's useful.

    (C) Remeny 2025
    // 31st August, 2025
*/

// Please don't code like yandere simulator


#include <graph.h>
#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include <direct.h>
#include <stdarg.h>

#include "patchress_dos.h"

// ---[ Defines ]--- //
#define status(fmt, ...) status(screen_rows, fmt, ##__VA_ARGS__)
#define MAX_ENTRIES 100         // Max menu/entry items

// ---[ Global variables ]--- //
int screen_rows = 0;
bool animate = true;

// ---[ Functions ]--- //
char* help = "\n  Patchress Arguments\n"
             "========================\n\n"
             "  /ni = Disable animations\n"
             "  /v  = Verbose mode\n"
             "\n";

void user_select_entry(const char *init_short_dir){
// This function is the best part of the program.
    // Init variables
    const char *init_dir = get_full_path(init_short_dir);
    char *menus[MAX_ENTRIES] = {0}, *entries[MAX_ENTRIES] = {0};
    char *current_directory = (char*) init_dir;
    char key = '\0';
    bool entry_selected = false;
    int total_items = 0;

    select_entry:
    // Here, we let the user select an entry.
    while (!entry_selected) {
        wipe();
        // First, we need to get the entries in the init directory.
        total_items = get_entries(menus, entries, init_dir, MAX_ENTRIES);
        dbg("Total items found in init dir: %d", total_items);

        if (total_items == 0) {
            // We found nothing.
            print_page("\n No entries or menus were found in the specified directory.\n\n"
                       " Press ESC to go back...");
            status("  ESC = Go back  F3 = You are a Quitter");
        } else {
            // We found something.
            print_page("\n Please select an entry from below.\n\n");
            dbg("Printing %d items from directory %s", total_items, init_dir);

            // Gather all entries and menus in one char* [] variable.
            // We put menus first, then entries.
            char *all_items[MAX_ENTRIES * 2] = {0};
            combine(menus, entries, all_items);
            status("  ENTER = Select  UP = Previous  DOWN = Next  ESC = Go back  F3 = Exit");
            selector(all_items);
            // Implement: return FALSE if ESC pressed, return TRUE if ENTER. And also capture index number
        }

        // Key checker
        while (true) {
            key = getch();
            if (key == 61) quit();  // F3 Key
            if (key == 27) {        // ESC key
                dbg("OLD DIRECTORY: %s", current_directory);
                current_directory = get_full_path(".."); // Go up one directory
                dbg("NEW DIRECTORY: %s", current_directory);
                break;
            } else if (key == 13 && total_items > 0) { // ENTER key. Only works if there are items.
                dbg("This isn't implemented yet.");
                crash("Some vague reason.");
                break;
            }
        }
    }

    return;
}

// ---[ Main ]--- //

int main(int argc, char* argv[]) {
    if (presence_in_array(argv, "/?")) {
        printf(help);
        return 0;
    }
    screen_rows = _setvideomode(_TEXTC80);
    
    if (screen_rows == 0) {
       printf("I was unable to set the video mode.\r\n");
       return -1;
    }

    bool animate = false, verbose = false;

    // Check for arguments
    if (!arg_check(argv, "/ni")) animate = true;
    if (arg_check(argv, "/v")) verbose = true;

    init(screen_rows, animate, verbose);

    int key = 0, index = 0;
    char *page;

    intro();

    page1:
    title("Remeny Patchress [MS-DOS]");

    delay(100);
    _settextposition(5, 1);

    page = "  Welcome to Patchress!\n\n"
           "   This application contains some utilities.\n\n\n"
           "   Press any key to continue...";
    print_page(page);
    print_page("The Mitochondria is the Powerhouse of the Cell.");
    status("  ENTER = Continue  F3 = Exit");

    key = -1;
    while (true) {
        key = getch();
        if (key == 13) goto page2;
        quit_check(key);
    }

    // Page 2
    page2:

    user_select_entry("RES");
    /*if (chdir(selected_entry) != 0) {
        return crash("Failure to swap to %s", selected_entry);
    }
    
    status("%s", selected_entry);*/
    
    return 0;
}
