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

// ---[ Function declarations ]--- //
void get_screen_size(void);
void save_position(void);
void save_color(void);
void restore_position(void);
void restore_color(void);
void dbg(const char* fmt, ...);

// End of extern "C" block
#ifdef __cplusplus
}
#endif

#endif // PATCHRESS_UTILS_H