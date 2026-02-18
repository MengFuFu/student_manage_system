//
// Created by Megumin on 2026/2/18.
//
#include "safe_stdin.h"

int readInt(const char* prompt)
{
    int num;
    char input[100];

    while (1)
    {
        printf("%s", prompt);
        int result = safeInputString(input, sizeof(input));

        if (result != 0) {
            continue;
        }

        if (StrToInt(&num, input))
        {
            return num;
        }
    }
}

void readString(char* buffer, int size, const char* prompt)
{
    while (1)
    {
        printf("%s", prompt);
        int result = safeInputString(buffer, size);

        if (result == 0) {
            return;
        }
    }
}

int StrToInt(int* num, char* input)
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

int safeInputString(char *buffer, int size) {
    buffer[0] = '\0';

    if (fgets(buffer, size, stdin) == NULL) {
        printf("读取失败 / 输入为空，请重新输入！\n");
        return -2;
    }

    char* newline = strchr(buffer, '\n');
    int inputWasTruncated = 0;

    if (newline != NULL) {
        *newline = '\0';
    } else {
        inputWasTruncated = 1;

        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    if (strlen(buffer) == 0) {
        printf("空输入！请重新输入！\n");
        return -2;
    }

    if (inputWasTruncated) {
        printf("警告：输入太长，已自动截断！\n");
        return -1;
    }

    return 0;
}