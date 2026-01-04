#include <shadow.h>
#include <crypt.h>
#include <pwd.h>
#include <string.h>
#include "auth.h"

int verify_password(const char *username, const char *password) {
    struct passwd *pw = getpwnam(username);
    if (!pw) return 0;
    struct spwd *sp = getspnam(username);
    if (!sp) return 0;
    char *encrypted = crypt(password, sp->sp_pwdp);
    return (encrypted && strcmp(encrypted, sp->sp_pwdp) == 0);
}