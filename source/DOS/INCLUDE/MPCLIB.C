// Multipatcher library
// 2025 remeny

// ---[ Include ]--- //
#include <conio.h>
#include <stdio.h>
#include <stdarg.h>
#include <dos.h>

#include "mpclib.h"

// ---[ Global variables ]--- //
int screen_rows = 0, screen_cols = 0;
Flags flags = { false, false, false, false, false };
TTYAttr saved_attr = { 1, 1, 0x8F };

// ---[ Functions ]--- //

// Gets screen cols and rows, saves into global variables
void get_screen_size(void) {
    struct text_info info;  // local: auto destroyed when function returns
    gettextinfo(&info);

    screen_rows = info.screenheight;
    screen_cols = info.screenwidth;
}

void save_position(void) {
    struct text_info info;
    gettextinfo(&info);
    saved_attr.row = info.cury;
    saved_attr.col = info.curx;
}

void save_color(void) {
    struct text_info info;
    gettextinfo(&info);
    saved_attr.colors = info.attribute;
}

void restore_position(void) {
    gotoxy(saved_attr.col, saved_attr.row);
}

void restore_color(void) {
    textattr(saved_attr.colors);
}

void dbg(const char* fmt, ...) {
    if (!flags.verbose) return; // Quit if verbose mode is not enabled.

    va_list args;

    // Save current position and color scheme
    save_position();
    save_color();

    // Set color scheme
    textcolor(LIGHTGREEN);
    textbackground(BLACK);

    // Move cursor to the bottom.
    gotoxy(screen_rows, 2);

    // Clear previous text
    clreol();

    // Print new text
    vprintf(fmt, args);

    // Log if we have to
    /*if (flags.v_log && logfile[0] != '\0') {
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
    }*/

    // Restore position and color
    /*_setbkcolor(current_bkgd_color);
    _settextcolor(current_fore_color);
    _settextposition(current_position.row, current_position.col);*/

    // Wait a bit so the user can see it
    if (flags.v_pause) {
        getch();
    } else {
        delay(100);
    }
}