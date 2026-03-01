//
// Created by Megumin on 2026/2/18.
//
#include "safe_stdin.h"

int readInt(const char* prompt) {
    int num;
    char input[100];

    while (1) {
        printf("%s", prompt);
        int ret = safeInputString(input, sizeof(input));

        if (ret != 0) {
            fflush(stdin);
            continue;
        }

        if (StrToInt(&num, input)) {
            return num;
        }

        fflush(stdin);
    }
}

// 读取字符串：强制非空，循环直到有效输入
void readString(char* buffer, int size, const char* prompt) {
    while (1) {
        printf("%s", prompt);
        int ret = safeInputString(buffer, size);

        if (ret == 0) {
            return;
        }

        fflush(stdin);
    }
}

// 字符串安全转整数，带错误检查
int StrToInt(int* num, char* input) {
    char *end;
    errno = 0;
    long val = strtol(input, &end, 10);

    if (end == input || errno == ERANGE || val < INT_MIN || val > INT_MAX) {
        printf("输入错误！请输入合法整数！\n");
        return 0;
    }

    while (*end != '\0') {
        if (!isspace((unsigned char)*end)) {
            printf("输入错误！不能包含非数字字符！\n");
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
        printf("读取失败，请重试！\n");
        return -2;
    }

    char *newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
    } else {
        int c;
        int maxFlush = 10000;
        while (maxFlush-- > 0 && (c = getchar()) != '\n' && c != EOF);
        printf("输入过长，已自动截断并清空缓冲区！\n");
    }

    if (strlen(buffer) == 0) {
        printf("输入不能为空！请重新输入！\n");
        return -2;
    }

    return 0;
}
