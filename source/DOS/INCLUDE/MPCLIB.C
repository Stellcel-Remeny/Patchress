// Multipatcher library
// 2025 remeny

// ---[ Include ]--- //
#include <conio.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <ctype.h>
#include <mem.h>
#include <dir.h>

#include "mpclib.h"

// ---[ Global variables ]--- //
int screen_rows = 0, screen_cols = 0;
Flags flags = { false, false, false, false, false };

// ---[ Functions ]--- //

// Gets screen cols and rows, saves into global variables
void get_screen_size(void) {
    struct text_info info;  // local: auto destroyed when function returns
    gettextinfo(&info);

    if (info.screenheight < MIN_SCREEN_ROWS ||
        info.screenwidth  < MIN_SCREEN_COLS) {
        crash("TINY SCREEN! Min: %dx%d.",
              MIN_SCREEN_COLS, MIN_SCREEN_ROWS);
    }

    screen_rows = info.screenheight;
    screen_cols = info.screenwidth;
}

// Save screen contents to memory
// Please declare buffer as 'unsigned char screen_buffer[MAX_SCREEN_COLS * MAX_SCREEN_ROWS * 2]'
void save_screen(unsigned char *screen_buffer) {
    if(screen_rows == 0 || screen_cols == 0)
        get_screen_size(); // ensure we have screen size
    // Copy from video memory segment 0xB800 to our buffer
    movedata(0xB800, 0, FP_SEG(screen_buffer), FP_OFF(screen_buffer), screen_rows * screen_cols * 2);
}

// Restore screen contents from memory
void restore_screen(unsigned char *screen_buffer) {
    // Copy from our buffer back to video memory
    movedata(FP_SEG(screen_buffer), FP_OFF(screen_buffer), 0xB800, 0, screen_rows * screen_cols * 2);
}

// Logs a message into LOGFILE
void log(const char* fmt, ...) {
    va_list args;
    FILE *f;
    if (!flags.v_log) return;
    // Append to logfile
    f = fopen(LOGFILE, "a");   // "a" = append mode
    if (!f) {
        perror("fopen");
        // Do not use crash() here to avoid recursion
        printf("Cannot open %s to write logs", LOGFILE);
        exit(-1);
    }
    va_start(args, fmt);
    vfprintf(f, fmt, args);
    fprintf(f, "\n");
    va_end(args);
    fclose(f);
}

// Crashes the application.
void crash(const char* fmt, ...) {
    va_list args;
    gotoxy(1, 2); // Go to second line

    // Set color scheme
    textcolor(BLACK);
    textbackground(WHITE);

    // Clear the line and print message
    clreol();
    cprintf(" Crash: ");
    va_start(args, fmt);
    vprintf(fmt, args);
    log("Crash:");
    log(fmt, args);
    va_end(args);
    exit(-1);
}

// Prints a message if verbose is enabled
void dbg(const char* fmt, ...) {
    va_list args;
    struct text_info saved_attr;
    char buffer[128];
    if (!flags.verbose) return; // Quit if verbose mode is not enabled.

    // Save current position and color scheme
    save_pos_and_color(saved_attr);

    // Set color scheme
    textcolor(LIGHTGREEN);
    textbackground(BLACK);

    // Move cursor to the bottom.
    gotoxy(2, screen_rows);

    // Clear previous text
    clreol();

    // Print new text
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);  // format
    va_end(args);

    cprintf("%s", buffer);  // display
    log("%s", buffer);      // log

    // Restore position and color
    restore_pos_and_color(saved_attr);

    // Wait a bit so the user can see it
    if (flags.v_pause) {
        getch();
    } else {
        delay(300);
    }
}

// Counts the number of arrays in a pointer to arrays
int count_arrays(char *arr[]) {
    int count = 0;
    while (arr[count] != NULL)
        count++;
    return count;
}

// Checks for the specified string in an array of strings.
bool presence_in_array(char* arr[], char* item) {
    int i;
    int size = count_arrays(arr);
    if (size < 0) return false; // No arguments

    for (i = 0; i < size; i++)
        if (strcmp(arr[i], item) == 0) return true;
    
    return false;
}

// presence_in_array but Case-InSenSiTive
bool arg_check(char* arr[], char* item) {
    int i;
    char temp[64];
    char temp2[64];
    char *a = NULL;

    // copy arr → temp
    strncpy(temp2, item, sizeof(temp2)-1);
    temp2[sizeof(temp2)-1] = 0;

    // Lowercase item in temp2
    strlwr(temp2);

    for (i = 0; arr[i]; i++) {
        a = arr[i];

        // copy arg → temp
        strncpy(temp, a, sizeof(temp)-1);
        temp[sizeof(temp)-1] = 0;

        // lowercase temp only
        strlwr(temp);

        if (strcmp(temp, temp2) == 0)
            return true;
    }
    return false;
}

// Updates the status bar
void status(const char *fmt, ...) {
    va_list args;
    struct text_info saved_attr;
    // Save current position and color scheme
    save_pos_and_color(saved_attr);

    // Set color scheme
    textbackground(WHITE);
    textcolor(BLACK);

    // Move cursor to the bottom and clear it
    gotoxy(1, screen_rows);
    clreol();
    gotoxy(2, screen_rows);

    // Print new text
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    // Restore position and color
    restore_pos_and_color(saved_attr);
}

// Intro animation
void intro(void) {
    int i;
    textbackground(BLACK);
    clrscr();
    status("");

    // Intro Animation!
    textbackground(BLUE);
    for (i = 0; i < screen_rows; i++) {
        gotoxy(1, i);
        if (flags.animate)
            delay(30);
        clreol();
    }

    textcolor(WHITE);
    gotoxy(1, 5);
}

// Reversed intro (exit animation)
void intro_reverse(void) {
    int i;
    status("");
    textbackground(BLACK);
    for (i = screen_rows - 1; i > 0; i--) {
        gotoxy(1, i);
        if (flags.animate)
            delay(30);
        clreol();
    }
    textcolor(WHITE);
    textbackground(BLACK);
    clrscr();
}

// Title printing function
void title(const char* fmt, ...) {
    va_list args;
    size_t i;
    char buffer[MIN_SCREEN_COLS - 10];
    struct text_info saved_attr;
    // Capture current position and color
    save_pos_and_color(saved_attr);

    // Color scheme: White on blue
    textcolor(WHITE);
    textbackground(BLUE);

    // Format the title into a buffer
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);

    // Print title at row 2, col 2
    gotoxy(1, 2);
    clreol();
    gotoxy(2, 2);
    cprintf(buffer);

    // Print underline at row 3
    gotoxy(1, 3);
    clreol();
    for (i = 0; i < strlen(buffer) + 2; i++) {
        cprintf("%c", 205);
        if (flags.animate) delay(10);
    }

    // Restore previous cursor position and color
    restore_pos_and_color(saved_attr);
}

// Prints text page with optional animation
void print_page(const char* fmt, ...) {
    char text[MAX_SCREEN_COLS * MAX_SCREEN_ROWS];    // buffer for full page text
    char buffer[MAX_SCREEN_COLS];   // buffer for each word
    va_list args;
    size_t pos = 0, len = 0;
    int i = 0, col = 0;

    va_start(args, fmt);
    vsprintf(text, fmt, args);  // safe: text is allocated
    va_end(args);

    len = strlen(text);

    cprintf(" ");  // initial space

    while (pos < len) {
        // handle explicit newlines
        if (text[pos] == '\n') {
            cprintf("\r\n ");
            col = 0;
            pos++;
            continue;
        }

        // collect a word
        i = 0;
        while (pos < len && text[pos] != '\n' &&
               !isspace((unsigned char)text[pos]) &&
               i < screen_cols - 1) {
            buffer[i++] = text[pos++];
        }
        buffer[i] = '\0';

        // if nothing collected, print the space
        if (i == 0) {
            cprintf(" ");
            col++;
            pos++;
            continue;
        }

        // wrap line if needed
        if (col + i > screen_cols) {
            cprintf("\r\n ");
            col = 0;
        }

        // print word
        if (flags.v_word_by_word)
            dbg("PRINTING WORD: '%s' (len=%d)", buffer, i);
        cprintf(buffer);
        col += i;

        // handle space after word
        if (pos < len && text[pos] == ' ') {
            if (col + 1 > screen_cols) {
                cprintf("\r\n ");
                col = 0;
            } else {
                cprintf(" ");
                col++;
            }
            pos++;
        }

        if (flags.animate) delay(30);
    }
    cprintf("\r\n"); // final newline
}

// Wipes the screen with blue color
void wipe(void) {
    int i;
    textbackground(BLUE);
    for (i = screen_rows - 1; i > 4; i--) {
        gotoxy(1, i);
        clreol();
        if (flags.animate) delay(30);
    }
    textbackground(BLUE);
    textcolor(LIGHTGRAY);
}

// Wipe without animation. Made for one dumb little thing.
void quick_wipe(void) {
    int i;
    textbackground(BLUE);
    for (i = screen_rows - 1; i > 4; i--) {
        gotoxy(1, i);
        clreol();
    }
    textbackground(BLUE);
    textcolor(LIGHTGRAY);
}

// Draw a grey window with animation. That's all.
void window(const int x, const int y, const int width, const int height) {
    // Init variables
    int mid_row, mid_col, i, offset, left_col, right_col;

    // Go to specified coords
    gotoxy(x, y);

    mid_row = height / 2 + y;
    mid_col = width / 2 + x;

    // Animate vertical center column
    for (i = 0; i <= height / 2; i++) {
        textbackground(WHITE); // Window color
        gotoxy(mid_col, mid_row - i); cprintf(" ");
        gotoxy(mid_col, mid_row + i); cprintf(" ");
        // Shadow
        textbackground(BLACK); // Shadow color
        gotoxy(mid_col + 1, mid_row - i + 1); cprintf("  "); // Top shadow
        gotoxy(mid_col + 1, mid_row + i + 1); cprintf("  "); // Bottom shadow

        if (flags.animate) delay(10); // Animate
    }

    // Expand horizontally
    for (offset = 1; offset <= width / 2; offset++) {
        left_col  = mid_col - offset;
        right_col = mid_col + offset;

        for (i = 0; i <= height; i++) {
            textbackground(WHITE); // Window color
            gotoxy(left_col, y + i);  cprintf(" ");
            gotoxy(right_col, y + i); cprintf(" ");
            // Shadow
            textbackground(BLACK); // Shadow color
            gotoxy(right_col + 1, y + i + 1); cprintf("  "); // RIGHT side shadow
        }

        textbackground(BLACK); // Shadow color
        gotoxy(left_col + 1, y + height + 1); cprintf(" ");   // LEFT side shadow

        // Animate
        if (flags.animate) delay(10);
    }

    // Goto top left of window
    textbackground(WHITE); // To make sure.
    gotoxy(x, y);
}

// Window close animation
void window_off(const int x, const int y, const int width, const int height) {
    int mid_row, mid_col, i, offset, left_col, right_col;

    gotoxy(x, y);

    mid_row = height / 2 + y;
    mid_col = width / 2 + x;

    // Collapse horizontally first (reverse of window())
    for (offset = width / 2; offset >= 1; offset--) {
        left_col  = mid_col - offset;
        right_col = mid_col + offset;

        for (i = 0; i <= height; i++) {
            textbackground(BLUE); // Closing color
            gotoxy(left_col, y + i);  cprintf(" ");
            textbackground(BLACK);
            gotoxy(right_col, y + i); cprintf(" ");
            // Clear shadows as we collapse
            textbackground(BLACK);
            gotoxy(right_col + 1, y + i + 1); cprintf(" ");
            textbackground(BLUE);
            gotoxy(right_col + 2, y + i + 1); cprintf(" ");
        }

        textbackground(BLUE);
        gotoxy(left_col + 1, y + height + 1); cprintf(" ");
        gotoxy(right_col, y); cprintf(" "); // Get rid of pesky shadow residue
        if (flags.animate) delay(10);
    }

    // Collapse vertical center (reverse of initial vertical open)
    for (i = height / 2; i >= 0; i--) {
        textbackground(BLUE); // Closing color
        gotoxy(mid_col, mid_row - i); cprintf(" ");
        gotoxy(mid_col, mid_row + i); cprintf(" ");
        // Clear old shadows
        gotoxy(mid_col + 1, mid_row - i + 1); cprintf("  ");
        gotoxy(mid_col + 1, mid_row + i + 1); cprintf("  ");

        if (flags.animate) delay(10);
    }
    gotoxy(x, y);
}

// A simple selector function.
// Returns:
//  index of the selected item if ENTER,
//  -1 if ESC is pressed.
int selector(char *items[]) {
    int total_size_of_items = count_arrays(items);
    int selected_item = 0, i = 0;
    int key;
    struct text_info saved_attr;
    // If there is nothing in items, quit.
    if (total_size_of_items == 0) return -1;

    // Capture current position and color scheme
    save_pos_and_color(saved_attr);

    // Check if the total amount goes beyond screen limit (+1 is so it would not print on status bar and line before it)
    if (saved_attr.cury + total_size_of_items + 1 > screen_rows) {
        dbg("Too many items to display! (%d items)", total_size_of_items);
        crash("Scrollable functionality not implemented yet.");
    }

    // Print everything in *items[] initially
    while (items[i] != NULL) {
        gotoxy(saved_attr.curx, saved_attr.cury + i);
        cprintf(items[i]);
        i++;
    }

    while (true) {
        // Highlight the selected entry
        gotoxy(saved_attr.curx, saved_attr.cury + selected_item);
        textbackground(WHITE);
        textcolor(BLACK);
        cprintf(items[selected_item]);

        // Wait for user input
        key = getch();
        if (key == 0) { // extended key
            key = getch();
            if (key == 72) { // Up arrow
                // Remove highlight from current entry
                gotoxy(saved_attr.curx, saved_attr.cury + selected_item);
                textattr(saved_attr.attribute);
                cprintf(items[selected_item]);

                selected_item--;
                if (selected_item < 0) selected_item = total_size_of_items - 1; // wrap around
            } else if (key == 80) { // Down arrow
                // Remove highlight from current entry
                gotoxy(saved_attr.curx, saved_attr.cury + selected_item);
                textattr(saved_attr.attribute);
                cprintf(items[selected_item]);

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

// Checks if a file exists. 
int file_exists(const char *fmt, ...) {
    char path[MAXPATH];  // buffer for formatted path
    FILE *f;
    va_list args;
    va_start(args, fmt);
    vsprintf(path, fmt, args);
    va_end(args);

    dbg("Checking for file: %s", path);
    f = fopen(path, "r");
    if (f) { fclose(f); return 1; }
    return 0;
}

// Checks if a directory exists.
int dir_exists(const char *fmt, ...) {
    char path[128];
    struct find_t f;
    va_list args;

    va_start(args, fmt);
    vsprintf(path, fmt, args);
    va_end(args);

    return findfirst(path, &f, FA_DIREC) == 0 && (f.attrib & FA_DIREC);
}

// Copies a file from src to dst
int copy_file(const char *src, const char *dst) {
    FILE *in = fopen(src, "rb");
    FILE *out = fopen(dst, "wb");
    char buf[4096];
    size_t n;
    
    if (!in) return 1;

    if (!out) {
        fclose(in);
        return 2;
    }

    while ((n = fread(buf, 1, sizeof(buf), in)) > 0) {
        if (fwrite(buf, 1, n, out) != n) {
            fclose(in);
            fclose(out);
            return 3;
        }
    }

    fclose(in);
    fclose(out);
    return 0;   // success
}

// Deletes a file
int remove_file(const char *fmt, ...) {
    char path[MAXPATH + 32];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(path, fmt, ap);
    va_end(ap);

    return remove(path);
}

// Splits a string into argv array
char **build_argv(const char *prog_name, const char *arg_str) {
    int argc = 0;
    char **argv;
    char *token;
    argv[argc++] = (char *)prog_name;       // argv[0] = program name

    token = strtok(arg_str, " ");
    while(token) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    argv[argc] = NULL;                      // terminate argv
    return argv;                            // return number of args
}

// Joins an array of strings into a single string with spaces
void join(char *o, char *a[]) {
    int i = 0;
    o[0] = 0;
    for (i = 0; a[i]; i++) {
        if (i) strcat(o, " ");
        strcat(o, a[i]);
    }
}

// Shows an input box and captures user input
void input(char buf[], int maxlen, const char *def) {
    struct text_info s;
    int pos = 0, key, space, i;

    // By the way, blame me not, fix my cgpt guru

    save_color(s);

    /* Clamp maxlen to visible screen space */
    space = screen_cols - s.curx - 1;
    if (maxlen > space)
        maxlen = space;

    if (maxlen < 2)
        maxlen = 2;

    /* Apply default string */
    strncpy(buf, def, maxlen - 1);
    buf[maxlen - 1] = 0;
    
    /* Draw box */
    textbackground(WHITE);
    textcolor(BLACK);
    for (i = 0; i < maxlen - 1; i++)
        cprintf(" ");

    /* Print existing text */
    gotoxy(s.curx, s.cury);
    cprintf("%s", buf);

    /* Input edit */
    for (;;) {
        key = getch();
        // Skip all extended keys. We not cool with the bad guys!
        if (key == 0) {
            getch();
            continue;
        }
        if (key == 13) break; /* ENTER */

        if (key == 8) { /* BACKSPACE */
            pos = strlen(buf);
            if (pos > 0) {
                buf[pos - 1] = 0;
                gotoxy(s.curx + pos - 1, s.cury);
                cprintf(" ");
                gotoxy(s.curx + pos - 1, s.cury);
            }
        }
        else if (isprint(key)) {
            pos = strlen(buf);
            if (pos < maxlen - 2) {
                buf[pos] = key;
                buf[pos + 1] = 0;
                gotoxy(s.curx, s.cury);
                cprintf("%s", buf);
            }
        }
    }

    textattr(s.attribute);
    cprintf("\r\n");
}
