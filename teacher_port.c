//
// Created by Megumin on 2026/2/18.
//
#include "teacher_port.h"
void teacherMainMenu(Account* loginAcc, Node* stuHead)
{
    printf("\n===== 教师端 =====\n");
    printf("1. 增删改查学生信息\n");
    printf("2. 查看班内成绩\n");
    printf("3. 成绩分析\n");
    printf("4. 返回上一级\n");

    while (1)
    {
        int choice = readInt("请输入选项：");

        switch (choice)
        {
        case 1:
            {
                printf("\n===== 学生信息管理 =====\n");
                printf("1. 新增学生 2. 修改学生 3. 删除学生 4. 查找学生\n");
                int newChoice = readInt("请输入选项：");

                if (newChoice == 1)
                {
                    Student s;
                    strcpy(s.classId, loginAcc->classId);
                    readString(s.id, sizeof(s.id), "请输入学号：");
                    readString(s.name, sizeof(s.name), "请输入姓名：");
                    for (int i = 0; i < SUBJECT; i++)
                    {
                        printf("请输入科目%d成绩：", i + 1);
                        s.subjectScores[i] = readInt("");
                    }
                    insertNode(stuHead, s);
                    printf("添加成功！");
                }
                else if (newChoice == 2)
                {
                    Student newS;
                    strcpy(newS.classId, loginAcc->classId);
                    newS.totalScore = 0;
                    readString(newS.id, sizeof(newS.id), "请输入目标学生的学号：");
                    readString(newS.name, sizeof(newS.name), "请输入新的姓名：");
                    for (int i = 0; i < SUBJECT; i++)
                    {
                        printf("请输入科目%d成绩：", i + 1);
                        newS.subjectScores[i] = readInt("");
                        newS.totalScore += newS.subjectScores[i];
                    }
                    Node* tar = searchStudent(stuHead, newS.id);
                    if (tar != NULL) {
                        tar->data = newS;
                    }
                }
                else if (newChoice == 3)
                {
                    char tar[20];
                    readString(tar, sizeof(tar), "请输入要删除学生的学号：");
                    deleteNode(stuHead, tar);
                }
                else if (newChoice == 4)
                {
                    char tar[20];
                    readString(tar, sizeof(tar), "请输入要查找学生的学号：");
                    Node* p = searchStudent(stuHead, tar);

                    if (p == NULL) {
                        printf("查无此人！\n");
                        break;
                    }

                    printf("%-10s %-10s %-10s ", "学号", "姓名", "班级");
                    for (int i = 0; i < SUBJECT; i++)
                    {
                        printf("科目%d  ", i + 1);
                    }
                    printf("%-8s\n", "总分");
                    printf("------------------------------------------------------------------------\n");
                    printf("%-10s %-10s %-10s ", p->data.id, p->data.name, p->data.classId);
                    for (int i = 0; i < SUBJECT; i++)
                    {
                        printf("%-6d ", p->data.subjectScores[i]);
                    }
                    printf("%-8d\n", p->data.totalScore);
                }
                else
                {
                    printf("输入错误！\n");
                }
            }
            break;
        case 2:
            {
                printf("\n===== 班内成绩 =====\n");
                Node* classList = filterByClass(stuHead, loginAcc->classId);
                sortStudents(classList, 0, 1);
                printList(classList);
                destroyList(classList);
                break;
            }
        case 3:
            {
                printf("\n===== 班级成绩分析 =====\n");
                Node* classList = filterByClass(stuHead, loginAcc->classId);
                Node *p = classList->next;
                if (p == NULL) {
                    printf("暂无数据！\n");
                    destroyList(classList);
                    break;
                }
                int sum = 0;
                int max = p->data.totalScore;
                int min = p->data.totalScore;
                int count = 0;
                while (p != NULL) {
                    sum += p->data.totalScore;
                    if (p->data.totalScore > max)
                    {
                        max = p->data.totalScore;
                    }
                    if (p->data.totalScore < min)
                    {
                        min = p->data.totalScore;
                    }
                    count++;
                    p = p->next;
                }
                printf("班级总人数：%d人\n", count);
                printf("班级平均分：%.2f分\n", (float)sum / count);
                printf("班级最高分：%d分\n", max);
                printf("班级最低分：%d分\n", min);
                destroyList(classList);
                break;
            }
        case 4:
            printf("正在返回登录界面...\n");
            return;
        default:
            printf("无效选项\n");
            break;
        }
    }
}