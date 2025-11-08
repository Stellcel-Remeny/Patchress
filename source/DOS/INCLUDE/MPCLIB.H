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

// ---[ Other Defines ]--- //
#define MIN_SCREEN_COLS 80
#define MIN_SCREEN_ROWS 25
#define MAX_SCREEN_COLS 132 // Apparently 50*132 is the max possible vid out for dos
#define MAX_SCREEN_ROWS 50

#define save_pos_and_color()        save_position();save_color();
#define restore_pos_and_color()     restore_position();restore_color();

#define LOGFILE "LOGFILE.TXT" // <--- File to be used if logging is enabled

// ---[ Structures ]--- //
typedef struct {
    bool animate;
    bool verbose;
    bool v_pause;
    bool v_log;
    bool v_word_by_word;
} Flags;

typedef struct {
    unsigned char row;
    unsigned char col;
    unsigned char colors;
} TTYAttr;

// ---[ Global Variables ]--- //
extern Flags flags;
extern int screen_rows, screen_cols;

// ---[ Function declarations ]--- //
void get_screen_size(void);
void save_position(void);
void save_color(void);
void restore_position(void);
void restore_color(void);
void save_screen(void);
void restore_screen(void);
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
void window(const int x, const int y, const int width, const int height);
void window_off(const int x, const int y, const int width, const int height);
void quit(void);

// End of extern "C" block
#ifdef __cplusplus
}
#endif

#endif // PATCHRESS_UTILS_H