// Application to change the reported DOS version (unnecessary app but ok)
// remeny

#include <patchress_dos.h>

#define SCREEN_HEIGHT 25

int main() {
    screen_rows = SCREEN_HEIGHT;

    char win_path[60] = {0};
    int key = 0;

    intro();
    title("Set reported DOS version for Windows 1.0");

    page1:
    print_page("This application runs SETVER.EXE on WIN100.BIN\n"
               "to set the reported DOS version to 3.0.\n\n"
               "This ASSUMES that SETVER.EXE IS LOADED in CONFIG.SYS,\n"
               "and that it is present in PATH.\n\n");
    print("  Please enter the path to your Windows 1.0 installation.\n\n");
    print("     ");
    input(win_path, sizeof(win_path), "C:\\WINDOWS");

    wipe();
    print_page("The path you entered is: %s\n\n"
               "If this is correct, press ENTER to continue, or ESC to re-enter the path.\n"
               "You can also press F3 to quit now.\n", win_path);

    while (key != 13) {
        key = getch();
        if (key == 27) {
            wipe();
            goto page1;
        } else if (key == 61) {
            exit(0);
        }
    }

    wipe();
    print_page("Running SETVER.EXE on WIN100.BIN to set reported DOS version to 3.0...\n\n");
    getch();
    return 0;
}