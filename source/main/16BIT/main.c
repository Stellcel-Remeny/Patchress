/*
    Remeny Patchress
    16-Bit Application for MS-DOS

    (C) Remeny 2025
    // 31st August, 2025
*/

#include <graph.h>
#include <dos.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

// Color codes
#define COLOR_BLACK        0
#define COLOR_BLUE         1
#define COLOR_GREEN        2
#define COLOR_AQUA         3
#define COLOR_RED          4
#define COLOR_PURPLE       5
#define COLOR_YELLOW       6
#define COLOR_WHITE        7
#define COLOR_GRAY         8
#define COLOR_LIGHT_BLUE   9
#define COLOR_LIGHT_GREEN  10
#define COLOR_LIGHT_AQUA   11
#define COLOR_LIGHT_RED    12
#define COLOR_LIGHT_PURPLE 13
#define COLOR_LIGHT_YELLOW 14
#define COLOR_BRIGHT_WHITE 15

// Other
#define print _outtext
typedef int bool;
#define true  1
#define false 0

// ---[ Global variables ]--- //
int screen_rows = 0;
bool animate = true;

// ---[ Functions ]--- //
void clear_line(int row) {
    if (row < 1 || row > screen_rows) return; // Invalid row
    _settextposition(row, 1);
    char blank[81]; // 80 chars + null terminator 
    for(int i = 0; i < 80; i++)
        blank[i] = ' ';
    blank[80] = '\0';
    print(blank);
    _settextposition(row, 1);           // reset cursor to start
}

void intro() {
    // Navigation Bar
    _setbkcolor(COLOR_WHITE);
    _clearscreen(_GCLEARSCREEN);

    _setbkcolor(COLOR_GRAY);
    for (int i = 0; i < screen_rows; i++) {
        clear_line(i);
    }

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

void title(const char* title) {
    // Prints the title at the top, similar to Windows XP Setup

    // Capture current position
    struct rccoord current_position;
    current_position = _gettextposition();   // returns struct rccoord

    // Now print title
    clear_line(2);
    _settextposition(2, 2);
    print((char *)title);

    // Now print the line beneath
    clear_line(3);
    int i = 0;
    char underline[2] = { 205, '\0' };
    while (i < strlen(title) + 3) {
        print(underline);
        i++;
    }

    _settextposition(3, 1);

    // Restore position
    _settextposition(current_position.row, current_position.col);
}

void print_page(const char* text) {
    const int LINE_WIDTH = 79;
    char buffer[81]; // 80 chars + null terminator
    int i = 0, col = 0; 
    size_t pos = 0, len = strlen(text);
    print(" ");

    while (pos < len) {
        // skip leading spaces
        while (pos < len && isspace((unsigned char)text[pos])) pos++;

        // collect a word into buffer
        i = 0;
        while (pos < len && !isspace((unsigned char)text[pos]) && i < 80) {
            buffer[i++] = text[pos++];
        }
        buffer[i] = '\0'; // null terminate

        if (i == 0) break; // no word collected -> done

        // wrap line if needed
        if (col + i > LINE_WIDTH) {
            print("\r\n ");
            col = 0;
        }

        // print word
        print(buffer);
        col += i;

        // add a space if next char is not end and fits in line
        if (pos < len) {
            if (col + 1 > LINE_WIDTH) {
                print("\n");
                col = 0;
            } else {
                print(" ");
                col++;
            }
        }
    }
    print("\n"); // final newline
}

int main() {
    screen_rows = _setvideomode(_TEXTC80);
    
    if (screen_rows == 0) {
       print("I was unable to set the video mode.\r\n");
       return -1;
    }

    intro();
    title("Remeny Patchress [MS-DOS]");

    delay(100);
    _settextposition(5, 1);

    char *page = "This is a 16-bit application running on MS-DOS."
                 "Is this a continuation?"
                 "Press any key to continue...";
    print_page(page);

    print_page("The Mitochondria is the Powerhouse of the Cell.");

    getch();
    return 0;
}
