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

// ---[ Global variables ]--- //
int screen_rows = 0;
bool animate = true;

// ---[ Main ]--- //

int main() {
    screen_rows = _setvideomode(_TEXTC80);
    
    if (screen_rows == 0) {
       print("I was unable to set the video mode.\r\n");
       return -1;
    }

    bool menu_selected = false;
    int key, index, total_num_entries, num_entries, num_menus = 0;
    char *page;
    char *menus[MAX_ENTRIES], *entries[MAX_ENTRIES];
    char current_folder[128] = "RES";

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

        key = getch();
        if (key == 13)
            goto page2;

        if (key == 0) { // extended key
            key = getch();
            if (key == 61) quit(); // F3 Key
        }

    // Page 2
    page2:
        status("Gathering entries...");
        wipe();
        page = "  Please select an item from below.\n\n";

        do {
            chdir(current_folder);
            total_num_entries = get_entries(menus, entries, ".", MAX_ENTRIES);
            delay(100);
            _settextposition(5, 1);
            print_page(page);

            if (total_num_entries == 0) {
                print_page("  No entries found. Please ensure you have the correct folder structure.");
                status("  ESC = Back  F3 = Exit");
            } else {
                for (int i = 0; i < total_num_entries; i++) {
                    // TODO: Add support for displaying Longer names defined in name=
                    // TODO: Add support for showing version, author, etc
                    // TODO: Add support for selecting using Arrow keys
                    // holy its currently dark here - it was a bundle of sunshine just minutes before! Now omg heavy clouds are covering the sun, guys!
                    // 8:56am

                    print_page("  %c. %s", 'A' + i, menus[i] ? menus[i] : entries[i]);
                }
                num_entries = count_arrays(entries);
                num_menus = count_arrays(menus);
                status("  <letter> = Select  ESC = Back  F3 = Exit");
            }
            // Get the letter, ESC or F3 key
            while (true) {
                key = getch();
                if (key >= 'A' && key <= 'Z') {
                    index = key - 'A';
                } else if (key >= 'a' && key <= 'z') {
                    index = key - 'a';
                } else if (key == 0) { // extended key
                    key = getch();
                    if (key == 61) quit(); // F3 Key
                } else {
                    continue;
                }
                // It is expected that entires would be shown first, then menus.
                // So, we first check if index > number of entries (not num_entries variable).
                print_page("KEY: %d, TOTAL_ENTRIES: %d, NUMBEROFENTRIES: %d, NUMBEROFMENUS: %d", index, total_num_entries, num_entries, num_menus);
                if (index < num_entries) {
                    // An entry was selected
                    status("You selected entry: %s", entries[index]);
                    //menu_selected = true;
                } else {
                    index = index - num_entries; // This gives us index for menus
                    if (menus[index]) {
                        // A menu was selected
                        //strcpy(current_folder, menus[index]);
                        menu_selected = false;
                        //break; // Break inner loop to refresh menu
                    } else {
                        status("Invalid selection. Please try again.");
                    }
                }
            }
        } while (!menu_selected);
        
    return 0;
}
