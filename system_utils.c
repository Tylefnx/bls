#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include "system_utils.h"
#include "config.h"

struct passwd* get_default_real_user() {
    struct passwd *pw;
    setpwent();
    while ((pw = getpwent())) {
        if (pw->pw_uid >= 1000 && pw->pw_uid < 60000) {
            endpwent();
            return pw;
        }
    }
    endpwent();
    return NULL;
}

void start_user_session(struct passwd *pw) {
    initgroups(pw->pw_name, pw->pw_gid); // Grupları devral
    setgid(pw->pw_gid);
    setuid(pw->pw_uid);
    chdir(pw->pw_dir);

    char rdir[64];
    snprintf(rdir, sizeof(rdir), "/run/user/%d", pw->pw_uid);
    
    // SUID tarafından silinenleri geri yükle
    setenv("USER", pw->pw_name, 1);
    setenv("HOME", pw->pw_dir, 1);
    setenv("SHELL", pw->pw_shell, 1);
    setenv("XDG_RUNTIME_DIR", rdir, 1);
    setenv("XDG_SESSION_TYPE", "wayland", 1);
    setenv("XDG_CURRENT_DESKTOP", "Hyprland", 1);
    setenv("LIBSEAT_BACKEND", "seatd", 1);
    setenv("PATH", PATH_ENV, 1);

    execlp(SESSION_CMD, SESSION_CMD, NULL);
    perror("Session launch failed");
    execlp("/bin/bash", "bash", NULL);
}