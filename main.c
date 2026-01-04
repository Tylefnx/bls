#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "ui_core.h"
#include "widgets.h"
#include "auth.h"
#include "system_utils.h"
#include "config.h"

int main() {
    char password[256] = {0};
    struct passwd *user_pw = get_default_real_user();
    if (!user_pw) return 1;

    init_visual_core();
    while (1) {
        clear();
        int cx = COLS / 2, sy = (LINES - CANVAS_HEIGHT) / 2;
        if (sy < 0) sy = 0;

        draw_logo(sy, cx);
        draw_title_card(sy + 14, cx);
        draw_status_bar(LINES - 2, cx);
        
        // Senin text formların (kutulu UI)
        draw_input_field(sy + 20, cx - 25, UI_INPUT_WIDTH, "USER", user_pw->pw_name, 0, 0);
        draw_input_field(sy + 25, cx - 25, UI_INPUT_WIDTH, "PASS", "", 1, 1);
        draw_hint(sy + 30, cx, "Press ENTER to authenticate");
        refresh();

        memset(password, 0, sizeof(password));
        read_password_live(password, sizeof(password), sy + 27, cx - 21, UI_INPUT_WIDTH);

        if (verify_password(user_pw->pw_name, password)) {
            show_result_banner(LINES/2, cx, 1);
            endwin();
            system("clear && tput reset");
            start_user_session(user_pw); // Oturumu fırlat
            exit(0);
        } else {
            show_result_banner(LINES/2, cx, 0);
        }
    }
    return 0;
}