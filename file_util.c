//
// Created by Megumin on 2026/2/16.
//


#include "file_util.h"

//学生数据
//把链表中的数据用二进制保存在文件中
void saveStudentsToFile(const Node* head, const char* filename)
{
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("学生数据文件打开失败！");
        return;
    }

    Node* p = head->next;
    while (p != NULL)
    {
        fwrite(&p->data, sizeof(Student), 1, fp);
        p = p->next;
    }

    fclose(fp);
    printf("学生数据已保存到 %s\n", filename);
}

//数据重载，从文件加载到链表
void loadStudentsFromFile(Node* head, const char* filename)
{
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        return;
    }

    int count = 0;
    Student s;
    while (fread(&s, sizeof(Student), 1, fp) == 1)
    {
        insertNode(head, s);
        count++;
    }

    fclose(fp);

    printf("加载到%d个学生数据", count);
}

//账号数据文件操作
//保存数据
void saveAccountsToFile(AccountNode *head, const char *filename)
{
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("账号数据文件打开失败！");
        return;
    }

    AccountNode* p = head->next;
    while (p != NULL)
    {
        fwrite(&p->data, sizeof(p->data), 1, fp);
        p = p->next;
    }

    fclose(fp);
    printf("数据已保存到 %s\n", filename);
}

//加载数据
void loadAccountsFromFile(AccountNode *head, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return;
    }

    Account acc;
    while (fread(&acc, sizeof(Account), 1, fp) == 1) {
        addAccount(head, acc);
    }

    fclose(fp);
}


//管理员批量导入 / 导出账号
void batchImportAccounts(AccountNode* head, const char* filename)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("导入文件不存在！\n");
        return;
    }
    Account acc;
    int roleNum;
    //用户名,密码,角色编号,班级,密保问题,密保答案
    while (fscanf(fp, "%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
                  acc.username, acc.password, &roleNum, acc.classId,
                  acc.securityQuestion, acc.securityAnswer) != EOF)
    {
        acc.role = (UserRole)roleNum;
        if (searchAccount(head, acc.username) == NULL)
        {
            addAccount(head, acc);
        }
    }
    fclose(fp);
    printf("账号批量导入完成！\n");
}

void batchExportAccounts(AccountNode* head, const char* filename)
{
    FILE* fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("文件打开失败！\n");
        return;
    }
    AccountNode* p = head->next;
    while (p != NULL)
    {
        fprintf(fp, "%s,%s,%d,%s,%s,%s\n",
                p->data.username, p->data.password, p->data.role, p->data.classId,
                p->data.securityQuestion, p->data.securityAnswer);
        p = p->next;
    }
    fclose(fp);
    printf("账号批量导出完成！\n");
}