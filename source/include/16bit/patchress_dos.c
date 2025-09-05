//
// Functions file for Patchress and other 16-Bit DOS programs
//

#include "patchress_dos.h"

// ---[ Functions ]--- //
void clear_line(int row) {
    if (row < 1) return; // Invalid row
    _settextposition(row, 1);
    for(int i = 0; i < SCREEN_COLUMNS; i++)
        print(" ");
    _settextposition(row, 1); // reset cursor to start
}

void status(int screen_row, const char *fmt, ...) {
    // Updates the navigation bar

    // Capture current position and color scheme
    struct rccoord current_position = _gettextposition();
    int current_bkgd_color = _getbkcolor();
    int current_fore_color = _gettextcolor();

    // Format the text into a buffer
    char buffer[SCREEN_COLUMNS + 1];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    // Set color scheme
    _setbkcolor(COLOR_WHITE);
    _settextcolor(COLOR_BLACK);

    // Move cursor to the bottom
    _settextposition(screen_row, 2);

    // Clear previous text
    for(int i = 0; i < SCREEN_COLUMNS - 2; i++)
        print(" ");

    // Print new text
    _settextposition(screen_row, 2);
    print(buffer);

    // Restore position and color
    _setbkcolor(current_bkgd_color);
    _settextcolor(current_fore_color);
    _settextposition(current_position.row, current_position.col);
}

void intro(int screen_rows, bool animate) {
    // Navigation Bar
    _setbkcolor(COLOR_WHITE);
    _clearscreen(_GCLEARSCREEN);
    status(screen_rows, "Please wait...");

    _setbkcolor(COLOR_BLACK);
    for (int i = 0; i < screen_rows; i++) clear_line(i);

    // Intro Animation!
    _setbkcolor(COLOR_BLUE);
    for (int i = 0; i < screen_rows; i++) {
        if (animate)
            delay(5);
        clear_line(i);
    }

    _setbkcolor(COLOR_BLUE);
    _settextcolor(COLOR_WHITE);
    _settextposition(5, 1);
}

void title(const char* fmt, ...) {
    // Capture current position
    struct rccoord current_position = _gettextposition();

    // Format the title into a buffer
    char buffer[SCREEN_COLUMNS - 4]; // adjust size as needed
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    // Print title at row 2, col 2
    clear_line(2);
    _settextposition(2, 2);
    print(buffer);

    // Print underline at row 3
    clear_line(3);
    char underline[2] = {205, '\0'}; // box-drawing character
    for (size_t i = 0; i < strlen(buffer) + 3; i++) print(underline);

    // Restore previous cursor position
    _settextposition(current_position.row, current_position.col);
}

void print_page(const char* fmt, ...) {
    char text[1024];  // buffer for formatted text
    va_list args;
    va_start(args, fmt);
    vsnprintf(text, sizeof(text), fmt, args);
    va_end(args);

    char buffer[SCREEN_COLUMNS];
    int i = 0, col = 0;
    size_t pos = 0, len = strlen(text);
    print(" ");  // initial space

    while (pos < len) {
        // handle explicit newlines
        if (text[pos] == '\n') {
            print("\n ");
            col = 0;
            pos++;
            continue;
        }

        // collect a word
        i = 0;
        while (pos < len && text[pos] != '\n' && !isspace((unsigned char)text[pos]) && i < SCREEN_COLUMNS) {
            buffer[i++] = text[pos++];
        }
        buffer[i] = '\0';

        // if nothing collected, print the space
        if (i == 0) {
            print(" ");
            col++;
            pos++;
            continue;
        }

        // wrap line if needed
        if (col + i > SCREEN_COLUMNS) {
            print("\n ");
            col = 0;
        }

        // print word
        print(buffer);
        col += i;

        // handle space after word
        if (pos < len && text[pos] == ' ') {
            if (col + 1 > SCREEN_COLUMNS) {
                print("\n ");
                col = 0;
            } else {
                print(" ");
                col++;
            }
            pos++;
        }
    }
    print("\n"); // final newline
}

void wipe() {
    _setbkcolor(COLOR_BLUE);
    for (int i = 24; i > 4; i--) {
        clear_line(i);
        delay(5);
    }
    _setbkcolor(COLOR_BLUE);
    _settextcolor(COLOR_WHITE);
    _settextposition(5, 1);
}

void quit() {
    // Quit function
    // TODO: Make this an animated dialog
    exit(0);
}

int file_exists(const char *fmt, ...) {
    char path[128];  // buffer for formatted path
    va_list args;
    va_start(args, fmt);
    vsnprintf(path, sizeof(path), fmt, args);
    va_end(args);

    status(25, "Checking for file: %s", path);
    FILE *f = fopen(path, "r");
    if (f) { fclose(f); return 1; }
    return 0;
}

int get_entries(char **menus, char **entries, const char *folder, int max_entries) {
    //
    // This function dumps all folders that have the Longfilename file
    // (lfn.ini) in them, in the variable 'menus'. It is expected that
    // they would hold entries.
    //
    // Folders which have 'info.ini' in them will be added to 'entries'.
    // 
    struct find_t fblock;
    char path[128];
    int count, menu_count, entry_count = 0;

    // Look for everything in folder (8.3 format)
    sprintf(path, "%s\\*.*", folder);

    // Start search
    if (_dos_findfirst(path, _A_SUBDIR, &fblock) != 0)
        return 0;

    do {
        if (count >= max_entries) break;

        if (fblock.attrib & _A_SUBDIR) {
            // Skip "." and ".."
            if (strcmp(fblock.name, ".") == 0 || strcmp(fblock.name, "..") == 0)
                continue;

            // Check for lfn.ini and info.ini
            if (file_exists("%s\\%s\\lfn.ini", folder, fblock.name)) {
                menus[menu_count] = malloc(strlen(fblock.name) + 1);
                if (!menus[menu_count]) break;
                strcpy(menus[menu_count], fblock.name);
                menu_count++;
            } else if (file_exists("%s\\%s\\info.ini", folder, fblock.name)) {
                entries[entry_count] = malloc(strlen(fblock.name) + 1);
                if (!entries[entry_count]) break;
                strcpy(entries[entry_count], fblock.name);
                entry_count++;
            } else {
                continue; // Neither file exists, skip
            }

            count++;
        }
    } while (_dos_findnext(&fblock) == 0);

    return count;
}

int count_arrays(char *arr[]) {
    int count = 0;
    while (arr[count] != NULL)
        count++;
    return count;
}
