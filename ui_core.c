#include "ui_core.h"
#include <string.h>

void init_visual_core() {
    initscr();
    start_color();
    use_default_colors();
    init_pair(C_PRIMARY, COLOR_CYAN, -1);
    init_pair(C_SECONDARY, COLOR_BLUE, -1);
    init_pair(C_ACCENT, COLOR_MAGENTA, -1);
    init_pair(C_SUCCESS, COLOR_GREEN, -1);
    init_pair(C_ERROR, COLOR_RED, -1);
    init_pair(C_TEXT, COLOR_WHITE, -1);
    init_pair(C_MUTED, COLOR_WHITE, -1);
    init_pair(C_HIGHLIGHT, COLOR_YELLOW, -1);
    cbreak(); noecho(); curs_set(0); keypad(stdscr, TRUE);
}

void draw_horizontal_line(int y, int x, int width, char ch, int color, int bold) {
    if (bold) attron(COLOR_PAIR(color) | A_BOLD);
    else attron(COLOR_PAIR(color));
    for (int i = 0; i < width; i++) mvaddch(y, x + i, ch);
    if (bold) attroff(COLOR_PAIR(color) | A_BOLD);
    else attroff(COLOR_PAIR(color));
}

void show_result_banner(int y, int center_x, int success) {
    int color = success ? C_SUCCESS : C_ERROR;
    const char *msg = success ? "  ACCESS GRANTED  " : "  ACCESS DENIED  ";
    attron(COLOR_PAIR(color) | A_BOLD | A_REVERSE);
    mvprintw(y, center_x - strlen(msg)/2, "%s", msg);
    attroff(COLOR_PAIR(color) | A_BOLD | A_REVERSE);
    refresh();
    napms(success ? 200 : 1000);
}

void read_password_live(char *buffer, size_t size, int y, int x, int width) {
    size_t pos = 0; int ch;
    while ((ch = getch()) != '\n' && ch != '\r' && ch != KEY_ENTER) {
        if ((ch == KEY_BACKSPACE || ch == 127 || ch == 8) && pos > 0) { pos--; buffer[pos] = '\0'; }
        else if (ch >= 32 && ch <= 126 && pos < size - 1 && pos < 35) { buffer[pos++] = ch; buffer[pos] = '\0'; }
        attron(COLOR_PAIR(C_HIGHLIGHT) | A_BOLD);
        char stars[256] = {0}; for (size_t i = 0; i < pos; i++) stars[i] = '*';
        mvprintw(y, x, "%-*s", width-8, stars);
        attron(A_BLINK); mvaddch(y, x + pos, '_'); attroff(A_BLINK);
        attroff(COLOR_PAIR(C_HIGHLIGHT) | A_BOLD);
        refresh();
    }
}