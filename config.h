#ifndef CONFIG_H
#define CONFIG_H

#define PATH_ENV       "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
#define SESSION_CMD    "start-hyprland"
#define UI_INPUT_WIDTH 50
#define CANVAS_HEIGHT  32
#define LOGO_LINES     13

__attribute__((unused)) static const char *DAEMON_LOGO[] = {
    "    `               `          ",
    "`.....---.......--.``   -/     ",
    "+o   .--`         /y:`      +. ",
    " yo`:.            :o      `+-  ",
    "  y/               -/`   -o/   ",
    " .-                 ::/sy+:.   ",
    " /                    `--  /   ",
    "`:                         :`  ",
    " /                         /   ",
    " .-                       -.   ",
    "  `:`                 `:`      ",
    "    .--             `--.       ",
    "       .---.....----.           "
};

#endif