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
             "  /ni   = Disable animations\n"
             "  /v    = Verbose mode\n"
             "  /vp   = Verbose mode with pauses (needs /v) [Not best to combine /vw]\n"
             "  /vlog = Verbose mode with logging (needs /v) [Filename: PATCHX16.log]\n"
             "  /vw   = Wait before printing each word (needs /v)\n"
             "  /?    = Show this help message\n"
             "\n";

void user_select_entry(const char *init_short_dir){
// This function is the best part of the program.
// TODO: Add check to see if we go outside init dir on ESC press
// TODO: Print the name specified in lfn.ini for Menus.
    // Init variables
    char current_directory[128],
         entry_directory[128],
         *menus[MAX_ENTRIES] = {0},
         *entries[MAX_ENTRIES] = {0},
         *all_items[MAX_ENTRIES * 2] = {0},
         key = '\0';
    
    _fullpath(current_directory, init_short_dir, sizeof(current_directory)); // Put into current_Directory first, since init_dir is const
    const char *init_dir = current_directory;

    bool entry_selected = false;
    int total_items = 0, selected_item = 0,
        num_menus = 0, num_entries = 0;
    
    dbg("Initial directory: %s", current_directory);

    select_entry:
    // Here, we let the user select an entry.
    while (!entry_selected) {
        wipe();
        // First, we need to get the entries in the current directory.
        total_items = get_entries(menus, entries, current_directory, MAX_ENTRIES);
        dbg("Total items found in current dir: %d", total_items);

        if (total_items == 0) {
            // We found nothing.
            dbg("CASE: NOTHING FOUND.");
            print_page("\n No entries or menus were found in the specified directory.\n\n"
                       " Press ESC to go back...");
            status("  ESC = Go back  F3 = You are a Quitter");
            // Key checker
            while (true) {
                key = getch();
                if (key == 61) quit();  // F3 Key
                if (key == 27) {        // ESC key
                    dbg("OLD DIRECTORY: %s", current_directory);
                    char *last_backslash = strrchr(current_directory, '\\');
                    if (last_backslash != NULL) {
                        *last_backslash = '\0';  // Truncate the string at the last backslash
                    }
                    dbg("NEW DIRECTORY: %s", current_directory);
                    break;
                }
            }
        } else {
            // We found something.
            dbg("CASE: FOUND.");
            print_page("\n Please select an entry from below.\n\n");
            dbg("PRINT PAGE SUCCESSFUL.");
            // Get the number of menus and entries
            num_menus = count_arrays(menus);
            num_entries = count_arrays(entries);
            dbg("MENUS: %d, ENTRIES: %d", num_menus, num_entries);
            dbg("Printing %d items from directory %s", total_items, init_dir);

            // Gather all entries and menus in one char* [] variable.
            // We put menus first, then entries.
            combine(menus, entries, all_items);
            status("  ENTER = Select  UP = Previous  DOWN = Next  ESC = Go back  F3 = Exit");
            selected_item = selector(all_items);

            if (selected_item == -1) {
                // User pressed ESC
                dbg("ESC PRESSED.");
                // Move the directory up one level
                dbg("OLD DIRECTORY: %s", current_directory);
                char *last_backslash = strrchr(current_directory, '\\');
                if (last_backslash != NULL) {
                    *last_backslash = '\0';  // Truncate the string at the last backslash
                }
                dbg("NEW DIRECTORY: %s", current_directory);
                continue; // Go back to the start of the loop
            } else if (selected_item > num_menus - 1) {
                // We assumed menus to be shown first.
                // Therefore, if the selected item is greater than the number of menus,
                // it means the user selected an entry. (Because entries are after menus)

                dbg("ENTRY SELECTED: %s", entries[selected_item - num_menus]);
                entry_directory[0] = '\0'; // Clear the buffer
                strncat(entry_directory, current_directory, sizeof(entry_directory) - 1);
                strncat(entry_directory, "\\", sizeof(init_dir) - strlen(current_directory) - 1);
                strncat(entry_directory, entries[selected_item - num_menus], sizeof(entry_directory) - 1);
                entry_selected = true;
            } else {
                // This case can only mean one thing:
                // User selected a menu.
                dbg("MENU SELECTED: %s", menus[selected_item]);
                // Change directory to the selected menu
                strncat(current_directory, "\\", sizeof(init_dir) - strlen(current_directory) - 1);
                strncat(current_directory, menus[selected_item], sizeof(init_dir) - strlen(current_directory) - 1);
                dbg("Changing directory to: %s", current_directory);
            }
        }
    }

    // An entry was chosen.
    dbg("ENTRY DIRECTORY: %s", entry_directory);
    
    // Get information from its INI file
    // TODO: ^^^^^^

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

    dbg("New session: Welcome.");

    int key = 0, index = 0;
    char *page;

    intro();

    page1:
    title("Remeny Patchress [MS-DOS]");

    delay(100);
    _settextposition(5, 1);

    page = "  Welcome to Patchress!\n\n"
           "   This application contains some utilities.\n\n\n"
           "   Press ENTER to continue...";
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
    
    dbg("Session terminated due to main() end.");
    return 0;
}
