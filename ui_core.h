#ifndef UI_CORE_H
#define UI_CORE_H
#include <ncurses.h>

#define C_PRIMARY 1
#define C_SECONDARY 2
#define C_ACCENT 3
#define C_SUCCESS 4
#define C_ERROR 5
#define C_TEXT 6
#define C_MUTED 7
#define C_HIGHLIGHT 8

void init_visual_core();
void draw_horizontal_line(int y, int x, int width, char ch, int color, int bold);
void show_result_banner(int y, int center_x, int success);
void read_password_live(char *buffer, size_t size, int y, int x, int width);
#endif