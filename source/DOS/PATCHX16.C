/*
  Code for 16-bit version of Patchress
  2025 Remeny

  Compile using Turbo C++ 3.5 compiler
*/

// ---[ Defines ]--- //
#define INI_ANSIONLY // For minini.h
#define MAX_ENTRIES 50 // Max menu/entry items

// ---[ Include ]--- //
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <dir.h>

#include "minIni.h"
#include "mpclib.h"

// ---[ Structures ]--- //
typedef struct {
    char directory[MAXPATH];
    char long_name[64];
    char version[8];
    char description[512];
    char author[64];
    char exe[MAXFILE + MAXEXT];
    char args[128];
} Entry;

// ---[ Functions (Garbage from old MPC PTC MSE Whatever trash) ]--- //
int get_entries(char **menus, char **entries, const char *folder, int max_items) {
    //
    // This function dumps all folders that have the Name= variable
    // (lfn.ini) in them, in the variable 'menus'.
    //
    // Folders which have 'info.ini' in them will be added to 'entries'.
    // 
    struct find_t fblock;
    char path[MAXPATH];
    int count = 0, menu_count = 0, entry_count = 0;

    // Look inside this folder
    sprintf(path, "%s\\*.*", folder);

    // Start search
    if (_dos_findfirst(path, _A_SUBDIR, &fblock) != 0)
        return 0;  // no subdirs found

    do {
        if (fblock.attrib & _A_SUBDIR) {
            // Skip files starting with '.'
            if (fblock.name[0] == '.')
                continue;

            // Check for lfn.ini and info.ini

            if (file_exists("%s\\%s\\lfn.ini", folder, fblock.name)) {
                menus[menu_count] = (char *)malloc(strlen(fblock.name) + 1);
                if (!menus[menu_count]) break;
                strcpy(menus[menu_count], fblock.name);
                menu_count++;
            } 
            else if (file_exists("%s\\%s\\info.ini", folder, fblock.name)) {
                entries[entry_count] = (char *)malloc(strlen(fblock.name) + 1);
                if (!entries[entry_count]) break;
                strcpy(entries[entry_count], fblock.name);
                entry_count++;
            } 
            else {
                continue; // Neither file exists, skip
            }
            count++;
        }
    } while (_dos_findnext(&fblock) == 0 && count < max_items);

    // Null terminate both arrays
    menus[menu_count] = NULL;
    entries[entry_count] = NULL;

    return count;
}

void get_fancy_names(char **all_items, char **menus, char **entries, const char *directory) {
    // This function gathers the names from Name= in lfn.ini
    // files for menus and info.ini files for entries.
    // It populates the all_items array with these names.

    int i = 0;
    char ini_path[MAXPATH];
    char fancy_name[64] = {0};
    int menu_count;
    // First, process menus
    while (menus[i] != NULL) {
        sprintf(ini_path, "%s\\%s\\lfn.ini", directory, menus[i]);
//        fancy_name[64] = {0};
        ini_gets("MAIN", "Name", menus[i], fancy_name, sizeof(fancy_name), ini_path);
        all_items[i] = (char *)malloc(strlen(fancy_name) + 1);
        if (all_items[i]) {
            strcpy(all_items[i], fancy_name);
        } else {
            all_items[i] = (char *)malloc(strlen(menus[i]) + 1);
            if (all_items[i]) {
                strcpy(all_items[i], menus[i]);
            }
        }
        i++;
    }

    menu_count = i;
    i = 0;
    // Now, process entries
    while (entries[i] != NULL) {
        sprintf(ini_path, "%s\\%s\\info.ini", directory, entries[i]);
//        fancy_name[64] = {0};
        ini_gets("MAIN", "Name", entries[i], fancy_name, sizeof(fancy_name), ini_path);
        all_items[menu_count + i] = (char *)malloc(strlen(fancy_name) + 1);
        if (all_items[menu_count + i]) {
            strcpy(all_items[menu_count + i], fancy_name);
        } else {
            all_items[menu_count + i] = (char *)malloc(strlen(entries[i]) + 1);
            if (all_items[menu_count + i]) {
                strcpy(all_items[menu_count + i], entries[i]);
            }
        }
        i++;
    }
    // Null terminate the array
    all_items[menu_count + i] = NULL;
}

void user_select_entry(const char *init_short_dir){
// This function is the best part of the program.
// TODO: Add a search system
// TODO: Add a way to edit execution arguments before running.
    // Init variables
    char current_directory[MAXPATH] = {0},
         init_dir[MAXPATH] = {0},
         *menus[MAX_ENTRIES / 2 + 1] = {0},
         *entries[MAX_ENTRIES / 2 + 1] = {0},
         *all_items[MAX_ENTRIES + 1] = {0},
         *last_backslash;

    char newdir[MAXPATH]; // c-gpt fix
    unsigned char screen_buffer[MAX_SCREEN_COLS * MAX_SCREEN_ROWS * 2];

    bool entry_selected = false,
         entry_runs_on_msdos = false;

    int total_items = 0, selected_item = 0,
        num_menus = 0, num_entries = 0,
        key = 0,
        code = 0;

    Entry *entry = (Entry *)malloc(sizeof(Entry));
    if (!entry) crash("Failed to allocate memory for Entry");
    memset(entry, 0, sizeof(Entry));

    _fullpath(init_dir, init_short_dir, sizeof(init_dir));
    // Copy the init_dir into current_directory
    strncpy(current_directory, init_dir, sizeof(current_directory) - 1);
    
    dbg("Initial directory: %s", current_directory);

    select_entry:
    // Here, we let the user select an entry.
    while (!entry_selected) {
        wipe();
        root_slash_skip:
        print_page(" You are currently in: %s", current_directory);
        // First, we need to get the entries in the current directory.
        total_items = get_entries(menus, entries, current_directory, MAX_ENTRIES);
        dbg("Total items found in current dir: %d", total_items);

        if (total_items == 0) {
            // We found nothing.
            dbg("CASE: NOTHING FOUND.");
            print_page("\n No entries or menus were found in the specified directory.\n\n"
                       " Press ESC to go back...");
            status("  ESC = Go back  F3 = Exit");
            // Key checker
            while (true) {
                key = getch();
                if (key == 61) quit();  // F3 Key
                if (key == 27) {        // ESC key
                    dbg("OLD DIRECTORY: %s", current_directory);
                    last_backslash = strrchr(current_directory, '\\');
                    if (last_backslash) {
                        *last_backslash = '\0';   // truncate at last backslash
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

            // Gather the fancy names
            get_fancy_names(all_items, menus, entries, current_directory);

            status("  ENTER = Select  UP = Previous  DOWN = Next  ESC = Go back  F3 = Exit");
            // Show selector
            cprintf("     ");
            selected_item = selector(all_items);

            if (selected_item == -1) {
                // User pressed ESC
                dbg("ESC PRESSED.");
                // Check if new directory goes outside init_dir
                if (strcmp(current_directory, init_dir) == 0) {
                    // We are already in the initial directory. (Assuming we are already NOT above it)
                    dbg("Already in initial directory, cannot go back further.");
                    quick_wipe();
                    goto root_slash_skip; // What a dumb way.
                }
                // Move the directory up one level
                dbg("OLD DIRECTORY: %s", current_directory);
                last_backslash = strrchr(current_directory, '\\');
                if (last_backslash) {
                    *last_backslash = '\0';   // truncate at last backslash
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
                sprintf(entry->directory,
                        //sizeof(entry->directory),
                        "%s\\%s",
                        current_directory,
                        entries[selected_item - num_menus]);
                entry_selected = true;
            } else {
                // This case can only mean one thing:
                // User selected a menu.
                dbg("MENU SELECTED: %s", menus[selected_item]);
                // Change directory to the selected menu
                memset(newdir, 0, sizeof(newdir));
                sprintf(newdir, "%s\\%s", current_directory, menus[selected_item]);
                strcpy(current_directory, newdir);
                dbg("Changing directory to: %s", current_directory);
            }
        }
    }

    // An entry was chosen.
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
            save_screen(screen_buffer);
            status("");
            dbg("Executing %s with args %s in dir %s", entry->exe, entry->args, entry->directory);
            // Clear current screen and set color scheme to White on black
            intro_reverse();

            // Execute the program
            code = system(entry->exe);
            dbg("Program exited with code %d\n", code);

            // Rebuild old screen
            intro();
            title("Remeny MultiPatcher [MS-DOS]");
            restore_screen(screen_buffer);
        }
    }
    return;
}

// ---[ Main ]--- //
int main(int argc, char *argv[]) {
    int key = 0;
    (void)argc;   // prevents unused-variable warning
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

    // Page 2
    user_select_entry("RES");

    dbg("Termination due to program end");
    return 0;
}