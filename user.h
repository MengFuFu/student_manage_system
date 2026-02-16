//
// Created by Megumin on 2026/2/17.
//

#ifndef STUDENT_MANAGE_SYSTEM_USER_H
#define STUDENT_MANAGE_SYSTEM_USER_H
#include <stdbool.h>

#endif //STUDENT_MANAGE_SYSTEM_USER_H

typedef struct User
{
    char username[20];
    char password[20];
}User;

bool register_user();
bool login_user();