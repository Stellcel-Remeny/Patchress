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

#include "mpclib.h"

// ---[ Global variables ]--- //
int screen_rows = 0, screen_cols = 0;
Flags flags = { false, false, false, false, false };
TTYAttr saved_attr = { 1, 1, 0x8F };
unsigned char screen_buffer[MAX_SCREEN_COLS * MAX_SCREEN_ROWS * 2];

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

// Saves cursor's XY coords
void save_position(void) {
    saved_attr.row = wherey();
    saved_attr.col = wherex();
}

// Saves cursor color
void save_color(void) {
    struct text_info info;
    gettextinfo(&info);
    saved_attr.colors = info.attribute;
}

// Restores cursor's XY coords
void restore_position(void) {
    if (saved_attr.col < 1 || saved_attr.row < 1)
        return; // invalid position
    
    gotoxy(saved_attr.col, saved_attr.row);
}

// Restores cursor color
void restore_color(void) {
    textattr(saved_attr.colors);
}

// Save screen contents to memory
void save_screen(void) {
    // Copy from video memory segment 0xB800 to our buffer
    movedata(0xB800, 0, FP_SEG(screen_buffer), FP_OFF(screen_buffer), screen_rows * screen_cols * 2);
}

// Restore screen contents from memory
void restore_screen(void) {
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
    cprintf("Crash: ");
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
    char buffer[128];
    if (!flags.verbose) return; // Quit if verbose mode is not enabled.

    // Save current position and color scheme
    save_pos_and_color();

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
    restore_pos_and_color();

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
    char *p;
    for (i = 0; arr[i]; i++)
        for (p = arr[i]; *p; p++)
            *p = tolower((unsigned char)*p);

    return presence_in_array(arr, item);
}

// Updates the status bar
void status(const char *fmt, ...) {
    va_list args;
    // Save current position and color scheme
    save_pos_and_color();

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
    restore_pos_and_color();
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
}

// Title printing function
void title(const char* fmt, ...) {
    va_list args;
    size_t i;
    char buffer[MIN_SCREEN_COLS - 10];
    // Capture current position and color
    save_pos_and_color();

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
    restore_pos_and_color();
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

        if (flags.animate) delay(50);
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
            gotoxy(right_col, y + i); cprintf(" ");
            // Clear shadows as we collapse
            textbackground(BLACK);
            gotoxy(right_col + 1, y + i + 1); cprintf(" ");
            textbackground(BLUE);
            gotoxy(right_col + 2, y + i + 1); cprintf(" ");
        }

        gotoxy(left_col + 1, y + height + 1); cprintf(" ");
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

// Displays quit dialog
void quit(void) {
    // Init variables
    int key;
    // Save current screen
    save_screen();

    // Capture current position and color
    save_pos_and_color();

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

    key = 0;
    while (key != 13 && key != 61) key = getch();

    if (key == 13) {
        // Window off animation
        window_off(14, 7, 52, 10);
        // Restore previous screen
        restore_screen();
        // Restore position and color
        restore_pos_and_color();
        return; // Cancel quit
    } else if (key == 61) {
        // Proceed to quit
        status("Goodbye!");
        //chdir(starting_directory); // Return to starting directory
        intro_reverse();
        dbg("Terminated due to quit() request.");
        exit(0);
    }
}