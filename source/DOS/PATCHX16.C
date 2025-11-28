/*
  Code for 16-bit version of MultiPatcher
  2025 Remeny

  Compile using Turbo C++ 3.5 compiler
*/

// ---[ Defines ]--- //
#define INI_ANSIONLY // For minini.h
#define MAX_ENTRIES 100 // Max menu/entry items

// ---[ Include ]--- //
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <dir.h>
#include <process.h>

#include "minIni.h"
#include "mpclib.h"

// ---[ Globals ]--- //
char mpc_args[512]; // Stores arguments passed into MPC
char root_dir[MAXPATH]; // Root directory of Multipatcher

// ---[ Structures ]--- //
typedef struct {
    char directory[MAXPATH];
    char long_name[64];
    char version[32];
    char description[512];
    char author[64];
    char exe[MAXFILE + MAXEXT];
    char args[128];
    bool pass_mpc_args;
    bool batch_mode;
} Entry;

// ---[ Functions ]--- //
// Displays quit dialog
void quit(void) {
    // Init variables
    int key = 0;
    struct text_info saved_attr;
    // Save current screen
    unsigned char screen_buffer[MAX_SCREEN_COLS * MAX_SCREEN_ROWS * 2];
    save_screen(screen_buffer);

    // Capture current position and color
    save_pos_and_color(saved_attr);

    status("");
    // Print the window
    gotoxy(14, 7);
    window(14, 7, 52, 10);

    // Set color scheme (Red on grey)
    textbackground(WHITE);
    textcolor(RED);

    // Print the text
    cprintf(" Are you sure you want to quit?");
    status("  F3 = Quit  Enter = Cancel ");

    while (key != ENTER_KEY) {
        key = getch();
        if (key == F3_KEY) {
            // Proceed to quit
            status("Goodbye!");
            if (root_dir[0] != '\0') {
                _chdrive((toupper(root_dir[0]) - 'A') + 1); // Starting drive
                chdir(root_dir); // Return to starting directory
            }
            intro_reverse();
            textbackground(BLACK);
            textcolor(LIGHTGRAY);
            dbg("Terminated due to quit() request.");
            exit(0);
        }
    }

    // ENTER KEY: don't quit.
    // Window off animation
    window_off(14, 7, 52, 10);
    // Restore previous screen
    restore_screen(screen_buffer);
    // Restore position and color
    restore_pos_and_color(saved_attr);
    return; // Cancel quit
}

// This function dumps all folders that have the Name= variable
// (lfn.ini) in them, in the variable 'menus'.
// Folders which have 'info.ini' in them will be added to 'entries'.
// Returns:
//      number of items found (both menus and entries)
int get_items(char **menus, char **entries, const char *folder, int max_items) {
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

// This function gathers the names from Name= in lfn.ini
// files for menus and info.ini files for entries.
// It populates the all_items array with these names.
void get_fancy_names(char **all_items, char **menus, char **entries, const char *directory) {
    int i = 0;
    char ini_path[MAXPATH];
    char fancy_name[64] = {0};
    int menu_count;
    // First, process menus
    while (menus[i] != NULL) {
        sprintf(ini_path, "%s\\%s\\lfn.ini", directory, menus[i]);
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

// Prints whatever is in the Entry struct
void print_entry_details(const Entry *entry) {
    if (!entry) return;
    print_page(
        " Details:\n\n"
        "     Name: %s\n"
        "     Version: %s\n"
        "     Author: %s\n"
        "     Executable: %s %s\n\n"
        "     Description: %s\n\n"
        " Press ENTER to run, or ESC to go back...",
        entry->long_name,
        entry->version,
        entry->author,
        entry->exe,
        entry->args,
        entry->description
    );
}

// Logic to display information about an entry
void display_entry(Entry *entry) {
    // Init vars
    unsigned char screen_buffer[MAX_SCREEN_COLS * MAX_SCREEN_ROWS * 2];
    int key = -1, code = 0;
    bool entry_runs_on_msdos = false;

    // Buffer for Batch-mode args
    char batch_mode_args[sizeof(entry->args) + 32] = {0};

    dbg("ENTRY DIRECTORY: %s", entry->directory);
    dbg("Gathering information from INI file.");
    status("");
    wipe();

    // Get information from its INI file
    if (chdir(entry->directory)) crash("Failure to swap to %s", entry->directory); // Change to entry directory

    entry_runs_on_msdos = ini_getbool("OS", "MSDOS", false, "info.ini");

    if (!entry_runs_on_msdos) {
        dbg("Information gather HALT - does not support DOS.");
        print_page(" The selected entry does not support MS-DOS.\n"
                    " Press ESC to go back...");
        status("  ESC = Go back  F3 = Exit");
    } else { 
        // Gather all needed information.
        ini_gets("MAIN", "Name", "<unspecified>", entry->long_name, sizeof(entry->long_name), "info.ini");
        ini_gets("MAIN", "Description", "<unspecified>", entry->description, sizeof(entry->description), "info.ini");
        ini_gets("MAIN", "Version", "<unspecified>", entry->version, sizeof(entry->version), "info.ini");
        ini_gets("MAIN", "Author", "<unspecified>", entry->author, sizeof(entry->author), "info.ini");
        ini_gets("MSDOS", "Exec", "", entry->exe, sizeof(entry->exe), "info.ini");
        ini_gets("MSDOS", "Args", "", entry->args, sizeof(entry->args), "info.ini");
        entry->pass_mpc_args = ini_getbool("MSDOS", "PassArgs", false, "info.ini");
        entry->batch_mode = ini_getbool("MSDOS", "BatchMode", false, "info.ini");
        dbg("Information gather OK.");
        
        // Check if executable is blank
        if (entry->exe[0] == '\0') {
            print_page(" The selected entry does not specify an executable that can run under MSDOS.\n"
                        " (Variable EXEC= under [MSDOS] is blank)\n\n"
                        " Press ESC to go back...");
            status("  ESC = Go back  F3 = Exit");
        } else {
            // Pass MPC arguments if needed
            if (entry->pass_mpc_args) {
                strcat(entry->args, " /MPC ");
                strcat(entry->args, mpc_args);
            }

            // Print information
            print_entry_details(entry);
            status("  ENTER = Run  E = Edit args  ESC = Go back  F3 = Exit");
        }

    }

    // Check keys:
    //  F3 = Execute quit()
    // ESC = End funct (it means user wants to go back to item selector)
    // ENT = spawn the executable
    //   E = Edit arguments
    key = -1;
    while (key != ESC_KEY) {
        key = getch();
        if      (key == F3_KEY)            { quit(); }
        else if (key == 'e' || key == 'E') {
            dbg("EDIT ARGS PAGE OPENING");
            dbg("OLD ARGS: %s", entry->args);
            // Edit arguments
            status("");
            wipe();
            print_page(" Current arguments: %s\n\n"
                       " Enter new arguments below:\n\n", entry->args);
            status("  ENTER = Update");
            cprintf("    ");
            input(entry->args, 70, entry->args);
            dbg("NEW ARGS: %s", entry->args);
            wipe();
            print_entry_details(entry);
        }
        else if (key == ENTER_KEY) {
            if (!file_exists(entry->exe))
                crash("File not found: %s", entry->exe); // We can define an error but this is easier.

            save_screen(screen_buffer);
            status("");
            dbg("Executing %s with args %s in dir %s", entry->exe, entry->args, entry->directory);
            // Clear current screen and set color scheme to White on black
            if (entry->pass_mpc_args) { wipe(); }
            else { intro_reverse(); }

            // Execute the program
            if (entry->batch_mode) { // Batch files require COMMAND.COM to be executed
                dbg("BATCHMODE");

                // Build batch mode args
                sprintf(batch_mode_args, "/C %s %s", entry->exe, entry->args);
                code = spawnvp(P_WAIT, "COMMAND.COM", build_argv("COMMAND.COM", batch_mode_args));
            } else {
                dbg("NOT BATCHMODE");
                code = spawnv(P_WAIT, entry->exe, build_argv(entry->exe, entry->args));
            }
            
            dbg("Program exited with code %d\n", code);

            // Rebuild old screen
            intro();
            title("Remeny MultiPatcher [MS-DOS]");
            restore_screen(screen_buffer);
        }
    }
}

void user_select_item(const char *init_short_dir){
// This function is the best part of the program.
// TODO: Add a search system
    // Init variables
    char current_directory[MAXPATH] = {0},     // Holds the Full path of current working directory
         *menus[MAX_ENTRIES / 2 + 1] = {0},    // Holds short name (dir name) of menus
         *entries[MAX_ENTRIES / 2 + 1] = {0},  // Holds short name (dir name) of entries
         *fancy_names[MAX_ENTRIES + 1] = {0},  // Holds fancy name of both menus and entries
         *last_backslash;                      // Pointer to last backslash in current_directory if ESC pressed to go up one dir

    int total_items = 0, selected_item = 0,
        num_menus = 0, num_entries = 0,
        key = -1;

    Entry *entry = (Entry *)malloc(sizeof(Entry));
    if (!entry) crash("Failed to allocate memory for Entry");
    memset(entry, 0, sizeof(Entry));

    // Copy the fullpath of init_short_dir into current_directory
    _fullpath(current_directory, init_short_dir, sizeof(current_directory));
    
    dbg("Initial directory: %s", current_directory);
    if (!dir_exists(current_directory))
        crash("Init directory '%s' does not exist!", current_directory);

    // Here, we let the user select an entry.
    for (;;) {
        wipe();
        print_page(" You are currently in: %s", current_directory);
        // First, we need to get the entries in the current directory.
        total_items = get_items(menus, entries, current_directory, MAX_ENTRIES);
        dbg("Total items found in current dir: %d", total_items);

        if (total_items == 0) {
            // We found nothing.
            dbg("CASE: NOTHING FOUND.");
            print_page("\n No entries or menus were found in the specified directory.\n\n"
                    " Press ESC to go back...");
            status("  ESC = Go back  F3 = Exit");
            // Key checker
            key = -1;
            while (key != ESC_KEY) {
                key = getch();
                if (key == F3_KEY) quit();  // F3 Key
            } // ESC key:
            
            dbg("OLD DIRECTORY: %s", current_directory);
            // Make sure we do not cross higher than Drive Letter level (?)
            // CHECK ASSUMES WE ARE NOT ABOVE '<root_dir>/RES', HENCE NO CHECKS FOR THAT.
            last_backslash = strrchr(current_directory, '\\');
            if (last_backslash) {
                *last_backslash = '\0';   // truncate at last backslash
            }
            dbg("NEW DIRECTORY: %s", current_directory);
            continue; // Goto start of loop
        } else {
            // We found something.
            dbg("CASE: FOUND.");
            print_page("\n Please select an item from below.\n\n");
            // Get the number of menus and entries
            num_menus = count_arrays(menus);
            num_entries = count_arrays(entries);
            dbg("MENUS: %d, ENTRIES: %d", num_menus, num_entries);
            dbg("Printing %d items from directory %s", total_items, current_directory);

            // Gather the fancy names
            get_fancy_names(fancy_names, menus, entries, current_directory);

            status("  ENTER = Select  UP = Previous  DOWN = Next  ESC = Go back  F3 = Exit");
            // Show selector
            cprintf("     ");
            selected_item = selector(fancy_names);

            if (selected_item == -1) {
                // User pressed ESC
                dbg("ESC PRESSED.");
                // Get the previous directory
                dbg("OLD DIRECTORY IN: %s", current_directory);
                last_backslash = strrchr(current_directory, '\\');

                // Check if new directory goes outside of initial directory
                dbg("CHK IF STRLEN CURRENT_DIRECTORY: %d", strlen(current_directory));
                dbg("IS > STRLEN ROOT_DIR: %d", strlen(root_dir));
                dbg("+ STRLEN INIT_SHORT_DIR: %d + 1", strlen(init_short_dir));
                if (last_backslash) {
                    dbg("LAST BACKSLASH FOUND.");
                    if (strlen(current_directory) > strlen(root_dir) + strlen(init_short_dir) + 1) {
                        dbg("NOT IN APPROOT DIRECTORY.");
                        *last_backslash = '\0';   // truncate at last backslash
                    } else {
                        dbg("IN APPROOT DIRECTORY.");
                    }
                }
                dbg("NEW DIRECTORY UP: %s", current_directory);
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
                // Display entry information
                display_entry(entry);
                // If the funct closes, that means user pressed ESC.
                // So we don't do anything.
            } else {
                // This case can only mean one thing:
                // User selected a menu.
                dbg("MENU SELECTED: %s", menus[selected_item]);
                // Change directory to the selected menu
                if (strlen(current_directory) + 1 + strlen(menus[selected_item]) < sizeof(current_directory)) {
                    strcat(current_directory, "\\");
                    strcat(current_directory, menus[selected_item]);
                } else {
                    // New path length exceeds sizeof current_directory
                    // We can design an error to go back to 'cwd/init_short_dir', but crash() is easier.
                    crash("New menu path is too long!: %d > %d",
                        strlen(current_directory) + 1 + strlen(menus[selected_item]),
                        sizeof(current_directory));
                }
                dbg("Changing directory to: %s", current_directory);
            }
        }
    }
}

// ---[ Main ]--- //
int main(int argc, char *argv[]) {
    int key = -1;
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
    join(mpc_args, argv + 1); // Join all arguments into a single string
    dbg("INIT: TSIZE ROW: %d, COL: %d, ARGS: %s", screen_rows, screen_cols, mpc_args);

    // Save current working directory
    getcwd(root_dir, sizeof(root_dir));

    intro();
    title("Remeny MultiPatcher [MS-DOS]");

    // Page 1
    textcolor(LIGHTGRAY);
    print_page("  Welcome to MultiPatcher !\n\n"
               "   This application contains some utilities.\n\n\n"
               "   Press ENTER to continue...\n");

    status("  ENTER = Continue  F3 = Exit");

    key = -1;
    while (key != ENTER_KEY) {
        key = getch();
        if      (key == F3_KEY)    { quit(); }
        else if (key == TILDE_KEY) { crash("Crash test."); }
    }

    // Page 2
    user_select_item("RES");

    dbg("Termination due to program end");
    return 0;
}