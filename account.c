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
    int roleChoice;
    char choice[3];
    char confirm_pwd[50];

    printf("\n===== 用户注册 =====\n");
    printf("请选择注册角色：1.学生 2.教师\n");
    StrToInt(&roleChoice, choice);
    if (roleChoice != 1 && roleChoice != 2)
    {
        printf("输入错误！");
        return 0;
    }
    newAcc.role = (roleChoice == 1) ? ROLE_STUDENT : ROLE_TEACHER;

    printf("请输入用户名（学生 = 学号 ， 教师 = 工号）: ");
    fgets(newAcc.username, sizeof(newAcc.username), stdin);
    if (searchAccount(head, newAcc.username) != NULL)
    {
        printf("该用户已存在！请登录！\n");
        return 0;
    }

    printf("请输入密码: ");
    fgets(newAcc.password, sizeof(newAcc.password), stdin);
    printf("请确认密码: ");
    fgets(confirm_pwd, sizeof(confirm_pwd), stdin);
    while (true)
    {
        if (strcmp(newAcc.password, confirm_pwd) != 0)
        {
            printf("两次输入的密码不一致！请重新输入！");
        }
        else
        {
            break;
        }
    }
    printf("请输入所属班级号：");
    fgets(newAcc.classId, sizeof(newAcc.classId), stdin);
    printf("请输入密保问题（用于找回密码）：");
    fgets(newAcc.securityQuestion, sizeof(newAcc.securityQuestion), stdin);
    printf("请输入密保答案：");
    fgets(newAcc.securityAnswer, sizeof(newAcc.securityAnswer), stdin);

    addAccount(head, newAcc);
    printf("注册成功！\n");
    return 1;
}

//登录功能
int loginAccount(AccountNode* head, Account* loginAcc)
{
    Account acc;

    printf("===== 用户登录 =====\n");
    printf("请输入用户名: ");
    fgets(acc.username, sizeof(acc.username), stdin);
    printf("请输入密码: ");
    fgets(acc.password, sizeof(acc.password), stdin);

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
int findPassword()
{

}