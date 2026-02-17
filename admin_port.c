//
// Created by Megumin on 2026/2/18.
//
#include "admin_port.h"
void adminMainMenu(AccountNode* accHead, Node* stuHead)
{
    printf("\n===== 管理员端 =====\n");
    printf("1. 增删改查账号及学生信息\n");
    printf("2. 从文件导入所有账号密码\n");
    printf("3. 从文件导出所有账号密码\n");
    printf("4. 登录教师端进行信息更改\n");
    printf("5. 返回上一级\n");

    while (1)
    {
        int choice = readInt("请输入选项：");
        switch (choice)
        {
        case 1:
            {
                printf("\n===== 账号管理 =====\n");
                printf("1. 新增账号 2. 删除账号 3. 查找账号\n");

                int newChoice = readInt("请输入选项：");
                if (newChoice == 1)
                {
                    Account acc;

                    readString(acc.username, sizeof(acc.username), "请输入用户名：");
                    readString(acc.password, sizeof(acc.password), "请输入密码：");

                    int roleNum = readInt("请输入角色（0学生 1教师 2管理员）：");
                    acc.role = (UserRole)roleNum;
                    readString(acc.classId, sizeof(acc.classId), "请输入班级号（管理员留空）：");
                    readString(acc.securityQuestion, sizeof(acc.securityQuestion), "请输入密保问题：");
                    readString(acc.securityAnswer, sizeof(acc.securityAnswer), "请输入密保答案：");
                    addAccount(accHead, acc);
                    printf("账号新增成功！\n");
                }
                else if (newChoice == 2)
                {
                    char username[20];
                    readString(username, sizeof(username), "请输入要删除的用户名：");
                    deleteAccount(accHead, username);
                }
                else if (newChoice == 3)
                {
                    char username[20];
                    readString(username, sizeof(username), "请输入要查找的用户名：");
                    AccountNode *p = searchAccount(accHead, username);
                    if (p != NULL) {
                        printf("找到账号：%s, 角色：%d, 班级：%s\n",
                            p->data.username, p->data.role, p->data.classId);
                    } else {
                        printf("未找到！\n");
                    }
                }
                break;
            }
        case 2: {
                char filename[50];
                readString(filename, sizeof(filename), "请输入导入文件名：");
                batchImportAccounts(accHead, filename);
                break;
        }
        case 3: {
                char filename[50];
                readString(filename, sizeof(filename), "请输入导出文件名：");
                batchExportAccounts(accHead, filename);
                break;
        }
        case 4:
            {
                char teacherId[20];
                readString(teacherId, sizeof(teacherId), "请输入要登录的教师工号：");
                AccountNode* p = searchAccount(accHead, teacherId);
                if (p == NULL || p->data.role != ROLE_TEACHER) {
                    printf("教师账号不存在！\n");
                    break;
                }
                teacherMainMenu(&p->data, stuHead);
                break;
            }
        case 5:
            printf("正在返回登录界面...\n");
            return;
        default:
            printf("无效选项！\n");
        }
    }
}