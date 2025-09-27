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
#include "patchress_dos.h"

// ---[ Defines ]--- //
#define status(fmt, ...) status(screen_rows, fmt, ##__VA_ARGS__)
#define MAX_ENTRIES 100         // Max menu/entry items

// ---[ Global variables ]--- //
int screen_rows = 0;

// ---[ Structures ]--- //
typedef struct {
    char directory[128];
    char long_name[64];
    char version[32];
    char description[512];
    char author[64];
    char exe[16];
    char args[128];
} Entry;

// ---[ Functions ]--- //
void user_select_entry(const char *init_short_dir){
// This function is the best part of the program.
// TODO: Add check to see if we go outside init dir on ESC press
// TODO: Print the name specified in lfn.ini for Menus.
// TODO: Add a search system
// TODO: Add a way to edit execution arguments before running.
    // Init variables
    char current_directory[128] = {0},
         *menus[MAX_ENTRIES] = {0},
         *entries[MAX_ENTRIES] = {0},
         *all_items[MAX_ENTRIES * 2] = {0};

    Entry *entry = malloc(sizeof(Entry));
    if (!entry) crash("Failed to allocate memory for Entry");
    memset(entry, 0, sizeof(Entry));
    
    _fullpath(current_directory, init_short_dir, sizeof(current_directory)); // Put into current_Directory first, since init_dir is const
    const char *init_dir = current_directory;

    bool entry_selected = false,
         entry_runs_on_msdos = false;
    int total_items = 0, selected_item = 0,
        num_menus = 0, num_entries = 0,
        key = 0;
    
    dbg("Initial directory: %s", current_directory);

    select_entry:
    // Here, we let the user select an entry.
    while (!entry_selected) {
        wipe();
        print_page(" You are currently in: %s", current_directory);
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
            // Show selector
            print("     ");
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
                // Clear previous entry information
                memset(entry, 0, sizeof(Entry));
                // Copy new entry directory
                snprintf(entry->directory,
                        sizeof(entry->directory),
                        "%s\\%s",
                        current_directory,
                        entries[selected_item - num_menus]);
                entry_selected = true;
            } else {
                // This case can only mean one thing:
                // User selected a menu.
                dbg("MENU SELECTED: %s", menus[selected_item]);
                // Change directory to the selected menu
                snprintf(current_directory,
                        sizeof(current_directory),
                        "%s\\%s",
                        current_directory,
                        menus[selected_item]);
                dbg("Changing directory to: %s", current_directory);
            }
        }
    }

    // An entry was chosen.
    show_entry_info:
    dbg("ENTRY DIRECTORY: %s", entry->directory);
    dbg("Loading information.");
    wipe();

    // Get information from its INI file
    if (chdir(entry->directory)) crash("Failure to swap to %s", entry->directory); // Change to entry directory

    entry_runs_on_msdos = ini_getbool("OS", "MSDOS", 0, "info.ini");

    if (!entry_runs_on_msdos) {
        print_page("The selected entry does not support MS-DOS.\n"
                    "Press ESC to go back...");
        status("  ESC = Go back  F3 = Exit");
    } else { 
        // Gather all information.
        dbg("Gathering information from INI file.");
        ini_gets("MAIN", "Name", "<unspecified>", entry->long_name, sizeof(entry->long_name), "info.ini");
        ini_gets("MAIN", "Description", "<unspecified>", entry->description, sizeof(entry->description), "info.ini");
        ini_gets("MAIN", "Version", "<unspecified>", entry->version, sizeof(entry->version), "info.ini");
        ini_gets("MAIN", "Author", "<unspecified>", entry->author, sizeof(entry->author), "info.ini");
        ini_gets("MAIN", "Exec", "", entry->exe, sizeof(entry->exe), "info.ini");
        ini_gets("MAIN", "Args", "", entry->args, sizeof(entry->args), "info.ini");
        dbg("Information gather OK.");
        
        // Check if executable is blank
        if (entry->exe[0] == '\0') {
            print_page("The selected entry does not specify an executable in exec=\n"
                        "Press ESC to go back...");
            status("  ESC = Go back  F3 = Exit");
        } else {
            // Print information
            print_page(" Details:\n\n"
                       "     Name: %s\n"
                       "     Version: %s\n"
                       "     Author: %s\n"
                       "     Description: %s\n\n"
                       "     Executable: %s %s [ARGUMENTS NOT PASSED]\n\n"
                       " Press ENTER to run, or ESC to go back...",
                       entry->long_name, entry->version, entry->author, entry->description, entry->exe, entry->args
                    );
            status("  ENTER = Run  ESC = Go back  F3 = Exit");
        }

    }

    // Key checker 2
    while (true) {
        key = getch();
        if (key == 61) quit();  // F3 Key
        if (key == 27) {        // ESC key
            entry_selected = false;
            goto select_entry;
        }
        if (key == 13 && entry_runs_on_msdos && entry->exe[0] != '\0') {
                                // ENTER key
            if (!file_exists(entry->exe)) crash("File not found: %s", entry->exe);
            status("");
            dbg("Executing %s with args %s in dir %s", entry->exe, entry->args, entry->directory);
            // Clear current screen and set color scheme to White on black
            intro_reverse();

            // Execute the program
            int code = system(entry->exe);
            dbg("Program exited with code %d\n", code);

            // Rebuild old screen
            intro();
            title("Remeny Patchress [MS-DOS]");
            goto show_entry_info;
        }
    }

    free(entry);
    return;
}

// ---[ Main ]--- //

int main(int argc, char* argv[]) {
    if (arg_check(argv, "/?")) {
        printf("\n  Patchress Arguments\n"
             "========================\n\n"
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

    dbg("New session: Welcome.");
    dbg("Please wait...");

    int key = 0;

    intro();
    title("Remeny Patchress [MS-DOS]");
    if (flags.animate) delay(100);

    print_page("  Welcome to Patchress!\n\n"
               "   This application contains some utilities.\n\n\n"
               "   Press ENTER to continue...\n");
    
    print_page("The Mitochondria is the Powerhouse of the Cell.");
    status("  ENTER = Continue  F3 = Exit");

    key = -1;
    while (true) {
        key = getch();
        if (key == 13) break;
        if (key == 61) quit();
        if (key == 96) crash("Crash test.");
    }

    user_select_entry("RES");
    
    dbg("Session terminated due to main() end.");
    return 0;
}
