//
// Functions file for Patchress and other 16-Bit DOS programs
//

#include <malloc.h>
#include "patchress_dos.h"

// ---[ Global variables ]--- //
int screen_rows = 0;
char logfile[128] = {0};
Flags flags = { false, false, false, false, false };

// ---[ Functions ]--- //
void dbg(const char* fmt, ...) {
    if (!flags.verbose) return; // Quit if verbose mode is not enabled.

    // Format the text into a buffer
    char buffer[SCREEN_COLUMNS + 1];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    // Capture current position and color scheme
    struct rccoord current_position = _gettextposition();
    int current_bkgd_color = _getbkcolor();
    int current_fore_color = _gettextcolor();

    // Print it as a status text, but modified colour. (Code from status()) //

    // Set color scheme
    _setbkcolor(COLOR_BLACK);
    _settextcolor(COLOR_LIGHT_GREEN);

    // Move cursor to the bottom. Always assume to be the last row.
    _settextposition(screen_rows, 2);

    // Clear previous text
    for(int i = 0; i < SCREEN_COLUMNS - 2; i++)
        print(" ");

    // Print new text
    _settextposition(screen_rows, 2);
    print(buffer);

    // Log if we have to
    if (flags.v_log && logfile[0] != '\0') {
        // Append to logfile
        FILE *f = fopen(logfile, "a");   // "a" = append mode
        if (!f) {
            perror("fopen");
            // Do not use crash() here to avoid recursion
            status(2, "Unable to open log file for writing.");
            exit(-1);
        }
        fprintf(f, "%s\n", buffer);
        fclose(f);
    }

    // Restore position and color
    _setbkcolor(current_bkgd_color);
    _settextcolor(current_fore_color);
    _settextposition(current_position.row, current_position.col);

    // Wait a bit so the user can see it
    if (flags.v_pause) {
        getch();
    } else {
        delay(100);
    }
}

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

void intro() {
    // Navigation Bar
    _setbkcolor(COLOR_WHITE);
    _clearscreen(_GCLEARSCREEN);
    status(screen_rows, "Please wait...");

    _setbkcolor(COLOR_BLACK);
    for (int i = 0; i < screen_rows; i++) clear_line(i);

    // Intro Animation!
    _setbkcolor(COLOR_BLUE);
    for (int i = 0; i < screen_rows; i++) {
        if (flags.animate && (i % 2 == 0))  // delay every 2nd row
            delay(1);
        clear_line(i);
    }

    _setbkcolor(COLOR_BLUE);
    _settextcolor(COLOR_WHITE);
    _settextposition(5, 1);
}

void intro_reverse() {
    // Intro Animation reversed! (Does not affect status bar)
    _setbkcolor(COLOR_BLACK);
    _settextcolor(COLOR_WHITE);
    for (int i = screen_rows - 1; i > 0; i--) {
        if (flags.animate && (i % 2 == 0))  // delay every 2nd row
            delay(1);
        clear_line(i);
    }
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
    for (size_t i = 0; i < strlen(buffer) / 2 + 1; i++) {
        print(underline);
        print(underline);
        if (flags.animate) delay(2);
    }

    // Restore previous cursor position
    _settextposition(current_position.row, current_position.col);
}

void print_page(const char* fmt, ...) {
    static char text[1024];  // buffer for formatted text
    va_list args;
    va_start(args, fmt);
    vsnprintf(text, sizeof(text), fmt, args);
    va_end(args);

    static char buffer[SCREEN_COLUMNS];
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
        while (pos < len && text[pos] != '\n' &&
               !isspace((unsigned char)text[pos]) &&
               i < SCREEN_COLUMNS - 1) {
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
        if (flags.v_word_by_word)
            dbg("PRINTING WORD: '%s' (len=%d)", buffer, i);
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

        if (flags.animate) delay(1);
    }
    print("\n"); // final newline
}

void wipe() {
    _setbkcolor(COLOR_BLUE);
    for (int i = 24; i > 4; i--) {
        clear_line(i);
        if (flags.animate && (i % 2 == 0))  // delay only every 2nd line
            delay(5);
    }
    _setbkcolor(COLOR_BLUE);
    _settextcolor(COLOR_WHITE);
    _settextposition(5, 1);
}

void quit() {
    // Quit function

    // Save current screen
    save_screen();

    // Capture current position and color
    struct rccoord current_position = _gettextposition();
    int current_bkgd_color = _getbkcolor(),
        current_fore_color = _gettextcolor();
    
    // Set color scheme (Red on grey)
    _setbkcolor(COLOR_WHITE);
    _settextcolor(COLOR_RED);

    // Print the window
    _settextposition(7, 14);
    window(7, 14, 52, 10);

    // Print the text
    print(" Are you sure you want to quit?");
    status(screen_rows, "  F3 = Quit  Enter = Cancel ");

    int key = 0;
    while (key != 13 && key != 61) key = getch();

    if (key == 13) {
        // Restore previous screen
        restore_screen();
        // Restore position and color
        _setbkcolor(current_bkgd_color);
        _settextcolor(current_fore_color);
        _settextposition(current_position.row, current_position.col);
        return; // Cancel quit
    } else if (key == 61) {
        // Proceed to quit
        status(screen_rows, "");
        intro_reverse();
        dbg("Session terminated due to quit() request.");
        exit(0);
    }
}

void window(const int y, const int x, const int width, const int height) {
    // Draw a grey window with animation. That's all.

    // Capture current position and color
    struct rccoord current_position = _gettextposition();
    int current_bkgd_color = _getbkcolor(),
        i = 0;

    // Go to specified coords
    _settextposition(y, x);

    int mid_row = height / 2 + y;
    int mid_col = width / 2 + x;

    // Animate vertical center column
    for (int i = 0; i <= height / 2; i++) {
        _setbkcolor(COLOR_WHITE); // Window color
        _settextposition(mid_row - i, mid_col); print(" ");
        _settextposition(mid_row + i, mid_col); print(" ");
        // Shadow
        _setbkcolor(COLOR_BLACK); // Shadow color
        _settextposition(mid_row - i + 1, mid_col + 1); print("  "); // Top shadow
        _settextposition(mid_row + i + 1, mid_col + 1); print("  "); // Bottom shadow
        
        if (flags.animate && (i % 2 == 0))  // delay every 2nd step
            delay(1);
    }

    // Expand horizontally
    for (int offset = 1; offset <= width / 2; offset++) {
        int left_col  = mid_col - offset;
        int right_col = mid_col + offset;

        for (int i = 0; i <= height; i++) {
            _setbkcolor(COLOR_WHITE); // Window color
            _settextposition(y + i, left_col);  print(" ");
            _settextposition(y + i, right_col); print(" ");
            // Shadow
            _setbkcolor(COLOR_BLACK); // Shadow color
            _settextposition(y + i + 1, right_col + 1); print("  "); // RIGHT side shadow
        }

        _setbkcolor(COLOR_BLACK); // Shadow color
        _settextposition(y + height + 1, left_col + 1); print(" ");   // LEFT side shadow

        // Delay every 2nd loop only
        if (flags.animate && (offset % 2 == 0)) {
            delay(5);
        }
    }

    // Restore position and color
    _setbkcolor(current_bkgd_color);
    _settextposition(current_position.row, current_position.col);
}

int file_exists(const char *fmt, ...) {
    char path[PATH_MAX];  // buffer for formatted path
    va_list args;
    va_start(args, fmt);
    vsnprintf(path, sizeof(path), fmt, args);
    va_end(args);

    dbg("Checking for file: %s", path);
    FILE *f = fopen(path, "r");
    if (f) { fclose(f); return 1; }
    return 0;
}

int get_entries(char **menus, char **entries, const char *folder, int max_items) {
    //
    // This function dumps all folders that have the Name= variable
    // (lfn.ini) in them, in the variable 'menus'.
    //
    // Folders which have 'info.ini' in them will be added to 'entries'.
    // 
    struct find_t fblock;
    char path[PATH_MAX];
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
                menus[menu_count] = malloc(strlen(fblock.name) + 1);
                if (!menus[menu_count]) break;
                strcpy(menus[menu_count], fblock.name);
                menu_count++;
            } 
            else if (file_exists("%s\\%s\\info.ini", folder, fblock.name)) {
                entries[entry_count] = malloc(strlen(fblock.name) + 1);
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

int count_arrays(char *arr[]) {
    int count = 0;
    while (arr[count] != NULL)
        count++;
    return count;
}

char* get_parent_dir(const char *path) {
    // This function returns the name of the parent directory of the given path.

    static char buf[128];
    char *last, *prev;

    // Expand relative path ".." into absolute
    if (_fullpath(buf, path, sizeof(buf)) == NULL)
        return NULL;

    // Find last backslash
    last = strrchr(buf, '\\');
    if (!last) return NULL;
    *last = '\0'; // cut off filename / last folder

    // Now find previous backslash (end of parent directory)
    prev = strrchr(buf, '\\');
    if (!prev) return buf; // root case (like "C:")

    return prev + 1; // parent directory name
}

int crash(const char* fmt, ...) {
// Crashes the application.
    char buf[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    status(2, "Crash!: %s", buf);
    dbg("Session crash: %s", buf);
    exit(-1);
}

int selector(char *items[]) {
    // A simple selector function.
    // Returns:
    //  index of the selected item if ENTER,
    //  -1 if ESC is pressed.

    int total_size_of_items = count_arrays(items);
    // If there is nothing in items, quit.
    if (total_size_of_items == 0) return -1;

    // Capture current position and color scheme
    struct rccoord current_position = _gettextposition();
    int current_bkgd_color = _getbkcolor();
    int current_fore_color = _gettextcolor();

    // Check if the total amount goes beyond screen limit (+1 is so it would not print on status bar and line before it)
    if (current_position.row + total_size_of_items + 1 > screen_rows) {
        dbg("Too many items to display! (%d items)", total_size_of_items);
        crash("Scrollable functionality not implemented yet.");
    }

    // Print everything in *items[] initially
    int selected_item = 0, i = 0;
    while (items[i] != NULL) {
        _settextposition(current_position.row + i, current_position.col);
        print(items[i]);
        i++;
    }

    while (true) {
        // Highlight the selected entry
        _settextposition(current_position.row + selected_item, current_position.col);
        _setbkcolor(COLOR_WHITE);
        _settextcolor(COLOR_BLACK);
        print(items[selected_item]);

        // Wait for user input
        int key = getch();
        if (key == 0) { // extended key
            key = getch();
            if (key == 72) { // Up arrow
                // Remove highlight from current entry
                _settextposition(current_position.row + selected_item, current_position.col);
                _setbkcolor(COLOR_BLUE);
                _settextcolor(COLOR_WHITE);
                print(items[selected_item]);

                selected_item--;
                if (selected_item < 0) selected_item = total_size_of_items - 1; // wrap around
            } else if (key == 80) { // Down arrow
                // Remove highlight from current entry
                _settextposition(current_position.row + selected_item, current_position.col);
                _setbkcolor(COLOR_BLUE);
                _settextcolor(COLOR_WHITE);
                print(items[selected_item]);

                selected_item++;
                if (selected_item >= total_size_of_items) selected_item = 0; // wrap around
            } else if (key == 61) { // F3 Key
                quit();
            }
        } else if (key == 13) { // Enter key
            break; // selection made
        } else if (key == 27) { // ESC key
            return -1; // cancel selection
        }
    }

    return selected_item;
}

bool presence_in_array(char* arr[], char* item) {
// Checks for the specified string in an array of strings.
    int size = count_arrays(arr);
    if (size < 0) return false; // No arguments

    for (int i = 0; i < size; i++)
        if (strcmp(arr[i], item) == 0) return true;
    
    return false;
}

bool arg_check(char* arr[], char* item) {
// presence_in_array but Case-InSenSiTive
    for (int i = 0; arr[i]; i++)
        for (char *p = arr[i]; *p; p++)
            *p = tolower((unsigned char)*p);

    return presence_in_array(arr, item);
}

void combine(char *arr1[], char *arr2[], char *out[]) {
// Joins two *arrays[] together into one array
    int n1 = count_arrays(arr1);
    int n2 = count_arrays(arr2);

    for (int i = 0; i < n1; i++) out[i] = arr1[i];
    for (int j = 0; j < n2; j++) out[n1 + j] = arr2[j];
    out[n1 + n2] = NULL;   // keep it NULL-terminated
}

void save_screen(void) {
    if (!screen_snapshot) {
        screen_snapshot = malloc(SCREEN_SIZE);
        if (!screen_snapshot) return;  // allocation failed
    }
    movedata(0xB800, 0, FP_SEG(screen_snapshot), FP_OFF(screen_snapshot), SCREEN_SIZE);
}

void restore_screen(void) {
    if (!screen_snapshot) return;
    movedata(FP_SEG(screen_snapshot), FP_OFF(screen_snapshot), 0xB800, 0, SCREEN_SIZE);
}
