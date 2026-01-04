#ifndef WIDGETS_H
#define WIDGETS_H
void draw_logo(int sy, int cx);
void draw_title_card(int y, int center_x);
void draw_input_field(int y, int x, int width, const char *label, const char *value, int focused, int is_password);
void draw_status_bar(int y, int center_x);
void draw_hint(int y, int center_x, const char *hint);
#endif