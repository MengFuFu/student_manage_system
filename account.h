//
// Created by Megumin on 2026/2/17.
//

#ifndef STUDENT_MANAGE_SYSTEM_USER_H
#define STUDENT_MANAGE_SYSTEM_USER_H
#include <stdbool.h>
#include "link_list.h"
typedef struct Account
{
    char username[20];
    char password[20];
    UserRole role;
    char classId[20];
    char securityQuestion[50];//密码找回：密保问题
    char securityAnswer[50];
}Account;

typedef struct AccountNode
{
    Account data;
    struct AccountNode* next;
}AccountNode;

AccountNode* creatAccountList();
void addAccount(AccountNode* head, Account acc);
AccountNode* searchAccount(AccountNode* head, char* username);
void deleteAccount(AccountNode* head, char* username);
void destroyAccountList(AccountNode* head);
int registerAccounts(AccountNode* head);
int loginAccount(AccountNode* head, Account* loginAcc);
int findPassword(AccountNode* head);
int modifyPassword(AccountNode* head, Account* loginAcc);

#endif //STUDENT_MANAGE_SYSTEM_USER_H