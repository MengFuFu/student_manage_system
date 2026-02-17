//
// Created by Megumin on 2026/2/18.
//
#include "student_port.h"

//成绩柱状图
void printScoreBar(int score)
{
    printf("成绩柱状图：");
    int count = score / 10;
    for (int i = 0; i < count; i++)
    {
        printf("■");
    }
    printf(" %d分\n", score);
}

//学生端菜单
void studentMainMenu(Account* loginACC, Node* stuHead)
{
    Node* classList = filterByClass(stuHead, loginACC->classId);

    printf("\n===== 学生端 =====\n");
    printf("1. 成绩查询\n");
    printf("2. 查询本班成绩\n");
    printf("3. 成绩分析\n");
    printf("4. 返回上一级\n");

    while (1)
    {
        int choice = readInt("请输入选项：");

        switch (choice)
        {
        case 1:
            {
                printf("\n===== 个人成绩查询 =====\n");
                Node* me = searchStudent(stuHead, loginACC->username);
                if (me == NULL)
                {
                    printf("未找到你的成绩信息！\n");
                    break;
                }
                printf("姓名：%s  班级：%s\n", me->data.name, me->data.classId);
                for (int i = 0; i < SUBJECT; i++)
                {
                    printf("科目%d：%d分  班级排名：第%d名\n",
                           i + 1, me->data.subjectScores[i],
                           getStudentRank(classList, me->data.id, i + 1));
                }
                printf("总分：%d分  班级总排名：第%d名\n",
                       me->data.totalScore, getStudentRank(classList, me->data.id, 0));
                printScoreBar(me->data.totalScore);

                break;
            }
        case 2:
            printf("\n===== 本班成绩表 =====\n");
            sortStudents(classList, 0, 1);
            printList(classList);
            break;
        case 3:
            {
                printf("\n===== 班级成绩分析 =====\n");
                Node* p = classList->next;
                if (p == NULL) {
                    printf("暂无数据！\n");
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

                break;
            }
        case 4:
            printf("返回登录界面中...\n");
            destroyList(classList);
            return;
        default:
            printf("无效选项！\n");
        }
    }
}