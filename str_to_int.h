//
// Created by Megumin on 2026/2/17.
//

#ifndef STUDENT_MANAGE_SYSTEM_STR_TO_INT_H
#define STUDENT_MANAGE_SYSTEM_STR_TO_INT_H
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#endif //STUDENT_MANAGE_SYSTEM_STR_TO_INT_H

static int StrToInt(int* num, char* input)
{
    char *end;
    long val;
    errno = 0;

    val = strtol(input, &end, 10);
    if (end == input || errno == ERANGE || val < INT_MIN || val > INT_MAX) {
        printf("输入错误！请输入合法的整数\n");
        return 0;
    }
    while (*end != '\0') {
        if (!isspace((unsigned char)*end)) {
            printf("输入错误！不能包含非数字字符\n");
            return 0;
        }
        end++;
    }

    *num = (int)val;
    return 1;
}