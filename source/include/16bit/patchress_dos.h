// Header file for patchress_dos.c
//

#ifndef PATCHRESS_UTILS_H
#define PATCHRESS_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

// ---[ Standard Libraries ]--- //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <graph.h>
#include <dos.h>
#include <conio.h>

// ---[ Boolean type ]--- //
#if !defined(__cplusplus)
  #if __STDC_VERSION__ >= 199901L
    #include <stdbool.h>
  #else
    typedef int bool;
    #define true  1
    #define false 0
  #endif
#endif

// ---[ Color codes ]--- //
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

// ---[ Other defines ]--- //
#define print _outtext          // Alias for DOS _outtext
#define SCREEN_COLUMNS 80       // Default screen width
#define MAX_ENTRIES 100         // Max menu/entry items

// ---[ Function declarations ]--- //
void clear_line(int row);
void status(int screen_row, const char *fmt, ...);
void intro(int screen_rows, bool animate);
void title(const char* fmt, ...);
void print_page(const char* fmt, ...);
void wipe(void);
void quit(void);
int file_exists(const char *fmt, ...);
int get_entries(char **menus, char **entries, const char *folder, int max_entries);
int count_arrays(char *arr[]);

#ifdef __cplusplus
}
#endif

#endif // PATCHRESS_UTILS_H
