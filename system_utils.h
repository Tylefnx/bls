#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H
#include <pwd.h>

struct passwd* get_default_real_user();
void start_user_session(struct passwd *pw);
#endif