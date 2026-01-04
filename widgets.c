#include "widgets.h"
#include "ui_core.h"
#include "config.h"
#include <string.h>
#include <time.h>

void draw_logo(int sy, int cx) {
    attron(COLOR_PAIR(C_ERROR) | A_BOLD);
    for (int i = 0; i < LOGO_LINES; i++) {
        mvprintw(sy + i, cx - (strlen(DAEMON_LOGO[i])/2), "%s", DAEMON_LOGO[i]);
    }
    attroff(COLOR_PAIR(C_ERROR) | A_BOLD);
}

void draw_title_card(int y, int center_x) {
    int width = 60;
    int x = center_x - width/2;
    attron(COLOR_PAIR(C_PRIMARY) | A_BOLD);
    mvaddch(y+1, x, '/');
    draw_horizontal_line(y+1, x+1, width-2, '=', C_PRIMARY, 1);
    mvaddch(y+1, x+width-1, '\\');
    mvaddch(y+2, x, '|'); mvaddch(y+2, x+width-1, '|');
    attroff(COLOR_PAIR(C_PRIMARY) | A_BOLD);
    attron(COLOR_PAIR(C_TEXT) | A_BOLD);
    mvprintw(y+2, center_x - 12, "B A S E D   L O G I N");
    attroff(COLOR_PAIR(C_TEXT) | A_BOLD);
    attron(COLOR_PAIR(C_PRIMARY) | A_BOLD);
    mvaddch(y+3, x, '|'); mvaddch(y+3, x+width-1, '|');
    mvaddch(y+4, x, '\\');
    draw_horizontal_line(y+4, x+1, width-2, '=', C_PRIMARY, 1);
    mvaddch(y+4, x+width-1, '/');
    attroff(COLOR_PAIR(C_PRIMARY) | A_BOLD);
}

void draw_input_field(int y, int x, int width, const char *label, const char *value, int focused, int is_password) {
    if (focused) { attron(COLOR_PAIR(C_HIGHLIGHT) | A_BOLD); mvprintw(y, x, ">> %s", label); attroff(COLOR_PAIR(C_HIGHLIGHT) | A_BOLD); }
    else { attron(COLOR_PAIR(C_MUTED)); mvprintw(y, x, "   %s", label); attroff(COLOR_PAIR(C_MUTED)); }
    int border_color = focused ? C_HIGHLIGHT : C_PRIMARY;
    attron(COLOR_PAIR(border_color) | (focused ? A_BOLD : A_NORMAL));
    mvaddch(y+1, x+2, '.'); draw_horizontal_line(y+1, x+3, width-4, '-', border_color, focused); mvaddch(y+1, x+width-2, '.');
    mvaddch(y+2, x+2, '|'); mvaddch(y+2, x+width-2, '|');
    mvaddch(y+3, x+2, '\''); draw_horizontal_line(y+3, x+3, width-4, '-', border_color, focused); mvaddch(y+3, x+width-2, '\'');
    attroff(COLOR_PAIR(border_color) | (focused ? A_BOLD : A_NORMAL));
    if (value && strlen(value) > 0) {
        attron(COLOR_PAIR(focused ? C_HIGHLIGHT : C_SUCCESS) | A_BOLD);
        if (is_password) {
            char stars[256] = {0}; int len = strlen(value);
            for (int i = 0; i < len && i < 35; i++) stars[i] = '*';
            mvprintw(y+2, x+4, "%-*s", width-8, stars);
        } else mvprintw(y+2, x+4, "%-*s", width-8, value);
        attroff(COLOR_PAIR(focused ? C_HIGHLIGHT : C_SUCCESS) | A_BOLD);
    }
}

void draw_status_bar(int y, int center_x) {
    attron(COLOR_PAIR(C_MUTED) | A_DIM);
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestr[64], status_msg[128];
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", t);
    snprintf(status_msg, sizeof(status_msg), "System: Linux | %s", timestr);
    mvprintw(y, center_x - (strlen(status_msg)/2), "%s", status_msg);
    attroff(COLOR_PAIR(C_MUTED) | A_DIM);
}

void draw_hint(int y, int center_x, const char *hint) {
    attron(COLOR_PAIR(C_ACCENT) | A_DIM);
    mvprintw(y, center_x - strlen(hint)/2, "%s", hint);
    attroff(COLOR_PAIR(C_ACCENT) | A_DIM);
}