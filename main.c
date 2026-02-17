#include <windows.h>
#include "admin_port.h"

int main(void)
{
    SetConsoleOutputCP(936);
    SetConsoleCP(936);

    AccountNode* accHead = creatAccountList();
    loadAccountsFromFile(accHead, "accounts.dat");

    //管理员账号最特殊，选择内置
    if (searchAccount(accHead, "admin") == NULL)
    {
        Account adminAcc = {
            .username = "admin",
            .password = "admin123",
            .role = ROLE_ADMIN,
            .classId = "",
            .securityQuestion = "中国有嘻哈，你最喜欢谁？",
            .securityAnswer = "pgone"
        };
        addAccount(accHead, adminAcc);
        printf("内置管理员账号已创建，账号：admin / 密码：admin123\n");
    }

    Node* stuHead = createList();
    loadStudentsFromFile(stuHead, "students.dat");

    //-----------------------登陆主界面--------------------------------
    printf("\n===== 学生信息管理系统 =====\n");
    printf("1. 学生登录\n");
    printf("2. 教师登录\n");
    printf("3. 管理员登录\n");
    printf("4. 账号注册\n");
    printf("5. 密码找回\n");
    printf("6. 密码修改（需先登录）\n");
    printf("0. 退出系统\n");

    int isRunning = 1;
    while (isRunning)
    {
        int mainChoice = readInt("请输入选项：");

        Account loginUser;
        int loginSuccess = 0;

        switch (mainChoice)
        {
            case 1:
                loginSuccess = loginAccount(accHead, &loginUser);
                if (loginSuccess == 1)
                {
                    studentMainMenu(&loginUser, stuHead);
                }
                break;
        case 2:
                loginSuccess = loginAccount(accHead, &loginUser);
                if (loginSuccess) {
                    teacherMainMenu(&loginUser, stuHead);
                }
                break;
        case 3:
            loginSuccess = loginAccount(accHead, &loginUser);
            if (loginSuccess) {
                adminMainMenu(accHead, stuHead);
            }
            break;
        case 4:
            registerAccounts(accHead);
            break;

        case 5:
            findPassword(accHead);
            break;
        case 6:
            loginSuccess = loginAccount(accHead, &loginUser);
            if (loginSuccess == 1) {
                modifyPassword(accHead, &loginUser);
            }
            break;
        case 0:
            saveAccountsToFile(accHead, "accounts.dat");
            saveStudentsToFile(stuHead, "students.dat");
            destroyAccountList(accHead);
            destroyList(stuHead);
            printf("系统已退出，数据已保存！\n");
            isRunning = 0;
            break;

        default:
            printf("无效选项！\n");
            break;
        }
    }
    return 0;
}