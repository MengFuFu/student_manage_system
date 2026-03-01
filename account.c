//
// Created by Megumin on 2026/2/17.
//
#include "account.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//创建账号链表
AccountNode* creatAccountList()
{
    AccountNode* head = (AccountNode*)malloc(sizeof(AccountNode));
    head->next = NULL;

    return head;
}

//添加账户
void addAccount(AccountNode* head, Account acc)
{
    AccountNode* p = (AccountNode*)malloc(sizeof(AccountNode));
    if (p == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    p->data = acc;
    p->next = head->next;
    head->next = p;
}

//查找用户
AccountNode* searchAccount(AccountNode* head, char* username)
{
    AccountNode* p = head->next;
    while (p != NULL) {
        if (strcmp(p->data.username, username) == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

//删除用户
void deleteAccount(AccountNode* head, char* username)
{
    AccountNode* p = head;
    while (p->next != NULL) {
        if (strcmp(p->next->data.username, username) == 0) {
            AccountNode* q = p->next;
            p->next = q->next;
            printf("账号删除成功！\n");
            return;
        }
        p = p->next;
    }
    printf("未找到该账号！\n");
}

//清空所有账户信息
void destroyAccountList(AccountNode* head)
{
    AccountNode* p = head;
    AccountNode* q = NULL;
    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
}

//===========================主业务功能区==================================
//注册功能实现->实现分角色注册
int registerAccounts(AccountNode* head)
{
    Account newAcc;
    char confirmPwd[50];

    printf("\n===== 用户注册 =====\n");
    int roleChoice = readInt("请选择注册角色：1.学生 2.教师\n");
    if (roleChoice != 1 && roleChoice != 2)
    {
        printf("输入错误！");
        return 0;
    }
    newAcc.role = (roleChoice == 1) ? ROLE_STUDENT : ROLE_TEACHER;

    readString(newAcc.username, sizeof(newAcc.username), "请输入用户名（学生 = 学号 ， 教师 = 工号）: ");
    if (searchAccount(head, newAcc.username) != NULL)
    {
        printf("该用户已存在！请登录！\n");
        return 0;
    }

    readString(newAcc.password, sizeof(newAcc.password), "请输入密码: ");

    while (true)
    {
        readString(confirmPwd, sizeof(confirmPwd), "请确认密码: ");
        if (strcmp(newAcc.password, confirmPwd) == 0)
        {
            break;
        }
        printf("两次输入的密码不一致！请重新输入！");
    }

    readString(newAcc.classId, sizeof(newAcc.classId), "请输入所属班级号：");
    readString(newAcc.securityQuestion, sizeof(newAcc.securityQuestion), "请输入密保问题（用于找回密码）：");
    readString(newAcc.securityAnswer, sizeof(newAcc.securityAnswer), "请输入密保答案：");

    addAccount(head, newAcc);
    printf("注册成功！\n");
    return 1;
}

//登录功能
int loginAccount(AccountNode* head, Account* loginAcc)
{
    Account acc;

    printf("===== 用户登录 =====\n");
    readString(acc.username, sizeof(acc.username), "请输入用户名: ");
    readString(acc.password, sizeof(acc.password), "请输入密码: ");

    AccountNode* p = searchAccount(head, acc.username);
    if (p == NULL || strcmp(p->data.password, acc.password) != 0)
    {
        printf("用户名或密码错误！\n");
        return 0;
    }

    *loginAcc = p->data;
    printf("登陆成功！欢迎你，%s！\n", p->data.username);
    return 1;
}

//找回密码（管理员）
int findPassword(AccountNode* head)
{
    char username[20];
    char answer[50];
    char newPwd[20];

    printf("\n===== 密码找回 =====\n");

    readString(username, sizeof(username), "请输入用户名：");

    AccountNode* p = searchAccount(head, username);
    if (p == NULL)
    {
        printf("用户名输入错误\n");
        return 0;
    }

    printf("账号的密保问题为：%s\n", p->data.securityQuestion);

    int attempts = 3;
    int verified = 0;

    while (attempts > 0)
    {
        printf("请输入密保答案（剩余%d次机会）：", attempts);
        readString(answer, sizeof(answer), "");

        if (strcmp(answer, p->data.securityAnswer) == 0)
        {
            verified = 1;
            break;
        }
        attempts--;
        if (attempts > 0)
        {
            printf("答案错误！请重新输入！\n");
        }
    }

    if (!verified)
    {
        printf("机会用尽，找回失败！\n");
        return 0;
    }

    readString(newPwd, sizeof(newPwd), "请输入新密码：");

    strcpy(p->data.password, newPwd);
    printf("密码修改成功！\n");

    return 1;
}

//登陆后修改密码
int modifyPassword(AccountNode* head, Account* loginAcc)
{
    char oldPwd[20];
    char newPwd[20];
    char confirmPwd[20];

    printf("\n===== 密码修改 =====\n");
    readString(oldPwd, sizeof(oldPwd), "请输入原密码：");

    if (strcmp(loginAcc->password, oldPwd) != 0) {
        printf("原密码错误！\n");
        return 0;
    }

    readString(newPwd, sizeof(newPwd), "请输入新密码：");
    readString(confirmPwd, sizeof(confirmPwd), "请确认新密码：");

    if (strcmp(newPwd, confirmPwd) != 0) {
        printf("两次密码不一致！\n");
        return 0;
    }

    AccountNode* p = searchAccount(head, loginAcc->username);
    strcpy(p->data.password, newPwd);
    strcpy(loginAcc->password, newPwd);
    printf("密码修改成功！\n");
    return 1;
}