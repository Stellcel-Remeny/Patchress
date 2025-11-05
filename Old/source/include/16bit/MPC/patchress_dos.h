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
#include <limits.h>

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
#define SCREEN_SIZE (80*25*2)

// ---[ Structures ]--- //
typedef struct {
    bool animate;
    bool verbose;
    bool v_pause;
    bool v_log;
    bool v_word_by_word;
} Flags;

// ---[ Global variables ]--- //
extern int screen_rows;
extern char logfile[128];
extern char starting_directory[PATH_MAX];
extern Flags flags;
unsigned char *screen_snapshot = NULL;

// ---[ Function declarations ]--- //
void dbg(const char* fmt, ...);
void clear_line(int row);
void status(int screen_row, const char *fmt, ...);
void intro();
void intro_reverse();
void title(const char* fmt, ...);
void print_page(const char* fmt, ...);
void wipe(void);
void quit(void);
void window(const int x, const int y, const int width, const int height);
int file_exists(const char *fmt, ...);
int get_entries(char **menus, char **entries, const char *folder, int max_entries);
int count_arrays(char *arr[]);
char* get_parent_dir(const char *path);
void crash(const char* fmt, ...);
int selector(char *entries[]);
bool presence_in_array(char* arr[], char* item);
bool arg_check(char* arr[], char* item);
void combine(char *arr1[], char *arr2[], char *out[]);
void save_screen(void);
void restore_screen(void);
void input(char str_buffer[], const int length, const char *default_str);
int build_argv(const char *str, char *argv[], const char *prog_name);

#ifdef __cplusplus
}
#endif

#endif // PATCHRESS_UTILS_H
