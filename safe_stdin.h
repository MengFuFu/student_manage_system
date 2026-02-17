#ifndef STUDENT_MANAGE_SYSTEM_STR_TO_INT_H
#define STUDENT_MANAGE_SYSTEM_STR_TO_INT_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
int readInt(const char* prompt);
void readString(char* buffer, int size, const char* prompt);
int StrToInt(int* num, char* input);
int safeInputString(char *buffer, int size);

#endif //STUDENT_MANAGE_SYSTEM_STR_TO_INT_H