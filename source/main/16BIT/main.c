/*
    Remeny Patchress
    16-Bit Application for MS-DOS
    Feel free to use this for whatever,
    but I highly doubt it's useful.

    (C) Remeny 2025
    // 31st August, 2025
*/

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
void user_select_entry_thing(){
    int total_num_items = 0, num_entries = 0, num_menus = 0;
    int key = 0, i = 0;
    char *menus[100], *entries[100];
    char current_folder[128] = "RES";
    bool entry_selected = false;

    while (!entry_selected) {
        chdir(current_folder);
        total_num_items = get_entries(menus, entries, ".", MAX_ENTRIES);

        if (total_num_items == 0) {
            print_page("No items found here to list. Press ESC to go back.");
            status("  ESC = Go up  F3 = You are a Quitter");
        } else {
            num_entries = count_arrays(entries);
            num_menus = count_arrays(menus);

            i = 0;
            while (i < num_menus) {
                print_page("%c: MENU: %s", 'A' + i, menus[i]);
                i++;
            }

            i = 0;
            while (i < num_entries) {
                print_page("%c: ENTRY: %s", 'A' + num_menus + i, entries[i]);
                i++;
            }
            status("  <A-Z> = Select item  ESC = Go up  F3 = Quit");
        }

        // User option
        key = -1;
        do {
            key = getch();
            if (key == 27) status("future...."); // ESC key
            if (key == 0) quit_check(key);
            if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) {
                if (key >= 'a' && key <= 'z') key = key - 'a' + 'A';   // convert to uppercase
                status("You pressed: %c", key);
            }
        } while (true);
    }
}

// ---[ Main ]--- //

int main() {
    screen_rows = _setvideomode(_TEXTC80);
    
    if (screen_rows == 0) {
       print("I was unable to set the video mode.\r\n");
       return -1;
    }

    int key = 0, index = 0;
    char *page;

    intro(screen_rows, animate);

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
    wipe();
    page = "  Please select an item from below.\n\n";

    user_select_entry_thing();
    
    return 0;
}
