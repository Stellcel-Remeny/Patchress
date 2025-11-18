// Header for MPCLIB.C
// 2025 remeny

#ifndef PATCHRESS_UTILS_H
#define PATCHRESS_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

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

// ---[ Save and restore screen items ]--- //
// Save position:
#define save_pos(var) save_pos_and_color(var);
// Save color:
#define save_color(var) save_pos_and_color(var);
// Save position and color (text attributes):
#define save_pos_and_color(var) gettextinfo(&var);
// Restore position:
#define restore_pos(var) gotoxy(var.curx, var.cury);
// Restore color:
#define restore_color(var) textattr(var.attribute);
// Restore position and color:
#define restore_pos_and_color(var) { restore_pos(var); restore_color(var); }

// ---[ Other Defines ]--- //
#define MIN_SCREEN_COLS 80
#define MIN_SCREEN_ROWS 25
#define MAX_SCREEN_COLS 132 // Apparently 60*132 is the max possible vid out for dos
#define MAX_SCREEN_ROWS 60

#define LOGFILE "LOGFILE.TXT" // <--- File to be used if logging is enabled

// ---[ Structures ]--- //
typedef struct {
    bool animate;
    bool verbose;
    bool v_pause;
    bool v_log;
    bool v_word_by_word;
} Flags;

// ---[ Global Variables ]--- //
extern Flags flags;
extern int screen_rows, screen_cols;

// ---[ Function declarations ]--- //
void get_screen_size(void);
void save_screen(unsigned char *screen_buffer);
void restore_screen(unsigned char *screen_buffer);
void log(const char* fmt, ...);
void crash(const char* fmt, ...);
void dbg(const char* fmt, ...);
int count_arrays(char *arr[]);
bool presence_in_array(char* arr[], char* item);
bool arg_check(char* arr[], char* item);
void status(const char *fmt, ...);
void intro(void);
void intro_reverse(void);
void title(const char* fmt, ...);
void print_page(const char* fmt, ...);
void wipe(void);
void quick_wipe(void);
void window(const int x, const int y, const int width, const int height);
void window_off(const int x, const int y, const int width, const int height);
int selector(char *items[]);
int file_exists(const char *fmt, ...);
int copy_file(const char *src, const char *dst);
char **build_argv(const char *prog_name, const char *arg_str);
void join(char *o, char *a[]);
void input(char str_buffer[], const int length, const char *default_str);
void quit(void);

// End of extern "C" block
#ifdef __cplusplus
}
#endif

#endif // PATCHRESS_UTILS_H