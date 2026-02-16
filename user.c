//
// Created by Megumin on 2026/2/17.
//

#include "user.h"

#include <stdio.h>
#include <string.h>

//注册功能实现
bool register_user()
{
    User u;
    char confirm_pwd[50];

    printf("===== 用户注册 =====\n");
    printf("请输入用户名: ");
    scanf("%s", u.username);

    FILE* fp = fopen("user.dat", "rb");
    if (fp == NULL)
    {
        printf("程序错误！请检查用户信息文件！");
        return false;
    }
    User temp;
    while (fread(&temp, sizeof(User), 1, fp) == 1)
    {
        if (strcmp(u.username, temp.username) == 0)
        {
            printf("用户名重复！请登录！");
            fclose(fp);
            return false;
        }
    }

    printf("请输入密码: ");
    scanf("%s", u.password);
    printf("请确认密码: ");
    scanf("%s", confirm_pwd);
    while (true)
    {
        if (strcmp(u.password, confirm_pwd) != 0)
        {
            printf("两次输入的密码不一致！请重新输入！");
        }
        else
        {
            FILE* fp = fopen("user.dat", "ab");
            if (fp == NULL)
            {
                printf("程序错误，写入信息失败！");
                return false;
            }

            fwrite(&u, sizeof(User), 1, fp);
            fclose(fp);

            printf("注册成功！请登录！");
            return true;
        }
    }
}

//登录功能
bool login_user()
{
    User u;

    printf("===== 用户登录 =====\n");
    printf("请输入用户名: ");
    scanf("%s", u.username);
    printf("请输入密码: ");
    scanf("%s", u.password);

    FILE* fp = fopen("users.dat", "rb");
    if (fp == NULL)
    {
        printf("读取用户数据失败！");
        return false;
    }

    User temp;
    while (fread(&temp, sizeof(User), 1, fp) == 1)
    {
        if (strcmp(u.username, temp.username) == 0 && strcmp(u.password, temp.password) == 0)
        {
            fclose(fp);
            printf("登录成功！欢迎 %s 使用系统。\n", u.username);
            return true;
        }
    }

    fclose(fp);
    printf("用户名或密码错误！\n");
    return 0;
}