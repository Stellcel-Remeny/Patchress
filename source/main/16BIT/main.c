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

char* user_select_entry_thing(char *page){
    int total_num_items = 0, num_entries = 0, num_menus = 0;
    int key = 0, i = 0;
    char *menus[MAX_ENTRIES] = { NULL };
    char *entries[MAX_ENTRIES] = { NULL };
    const char init_dir[] = "RES";
    char current_folder[16];
    strncpy(current_folder, init_dir, sizeof(current_folder)-1);
    current_folder[sizeof(current_folder)-1] = '\0';

    char *selected_entry = malloc(128);     // heap buffer returned to caller
    if (!selected_entry) return NULL;
    selected_entry[0] = '\0';
    bool entry_selected = false;

    while (!entry_selected) {
        status("Please wait...");
        wipe();

        // chdir returns 0 on success
        if (chdir(current_folder) != 0) {
            total_num_items = 0;
        } else {
            total_num_items = get_entries(menus, entries, ".", MAX_ENTRIES);
        }

        if (total_num_items == 0) {
            print_page("No items found here to list. Press ESC to go back.");
            status("  ESC = Go up  F3 = You are a Quitter");
        } else {
            print_page(page);
            num_entries = count_arrays(entries);
            num_menus = count_arrays(menus);

            //for (i = 0; i < num_menus; ++i)
                //print_page("%c: MENU: %s", 'A' + i, menus[i]);
                _settextposition(18, 2);
                int hi = selector(menus);

            for (i = 0; i < num_entries; ++i)
                print_page("%c: ENTRY: %s", 'A' + num_menus + i, entries[i]);

            status("  <A-Z> = Select item  ESC = Go up  F3 = Quit");
        }

        // User option
        key = -1;
        do {
            key = getch();
            if (key == 0) quit_check(key);
            if (key == 27) { // ESC Key - go up to '..' if the current directory isn't init_dir
                if (!strcmp(get_parent_dir(".."), init_dir)) {
                    strcpy(current_folder, "..");
                    break;
                }
            } else if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) {
                if (key >= 'a' && key <= 'z') key = key - 'a' + 'A';
                key = key - 'A'; // convert to index
                if (key < num_menus) {
                    strncpy(current_folder, menus[key], sizeof(current_folder)-1);
                    current_folder[sizeof(current_folder)-1] = '\0';
                    break;
                } else {
                    key = key - num_menus;
                    if (key < num_entries) {
                        strncpy(selected_entry, entries[key], 127);
                        selected_entry[127] = '\0';
                        entry_selected = true;
                        break;
                    } else {
                        continue;
                    }
                }
            }
        } while (1);
    }

    // free the menu/entry strings allocated by get_entries
    for (i = 0; i < MAX_ENTRIES && menus[i]; ++i) free(menus[i]);
    for (i = 0; i < MAX_ENTRIES && entries[i]; ++i) free(entries[i]);

    return selected_entry;
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
    while (key != 13 && key != 0) key = getch();
    
    if (key == 13)
        goto page2;

    quit_check(key);

    // Page 2
    page2:
    status("Gathering entries...");
    page = "  Please select an item from below.\n\n";

    char *selected_entry = user_select_entry_thing(page);
    if (chdir(selected_entry) != 0) {
        free(selected_entry);
        return crash("Failure to swap to %s", selected_entry);
    }
    
    status("%s", selected_entry);
    free(selected_entry);
    
    return 0;
}
