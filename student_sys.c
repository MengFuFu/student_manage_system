//
// Created by Megumin on 2026/2/16.
//
#include "student_sys.h"
#include <stdio.h>
#include <stdlib.h>
//显示操作菜单
void show_menu()
{
    printf("\n===== 学生成绩管理系统 =====\n");
    printf("1. 录入学生信息\n");
    printf("2. 显示所有学生\n");
    printf("3. 查找学生\n");
    printf("4. 删除学生\n");
    printf("5. 修改学生信息\n");
    printf("6. 按成绩排序\n");
    printf("7. 统计成绩\n");
    printf("0. 退出系统\n");
    printf("============================\n");
    printf("请输入选项: ");
}
//录入学生
void add_student(Node* head)
{
    Student s;
    printf("请输入学生的信息：\n");
    printf("学号（id）：");
    scanf("%s", s.id);
    printf("\n姓名（name）：");
    scanf("%s", s.name);
    printf("\n成绩（score）：");
    scanf("%d", &s.score);

    if (insert_node(head, s))
    {
        printf("添加成功！当前共有%d名学生信息", count_students(head));
    }

    printf("添加失败！！");
}
//修改学生信息
void modify_student(Node* head)
{
    printf("请输入您要修改的学生id：");
    char id[20];
    scanf("%s", id);
    Node* curNode = search_student(head, id);
    if (curNode != NULL)
    {
        Student newData;
        printf("请输入新的信息：\n");
        printf("学号（id）：");
        scanf("%s", newData.id);
        printf("\n姓名（name）：");
        scanf("%s", newData.name);
        printf("\n成绩（score）：");
        scanf("%d", &newData.score);

        curNode->data = newData;

        printf("修改成功！");
        return ;
    }

    printf("修改失败！");
}

//对学生按照成绩排序
void sort_students(Node* head, int choice)
{
    if (head->next == NULL || head->next->next == NULL)
    {
        return;
    }
    Node* dummy = (Node*)malloc(sizeof(Node));
    dummy->next = head->next;
    Node* sortedNode = head->next;

    switch (choice)
    {
    case 0:
        {
            while (sortedNode->next != NULL)
            {
                if (sortedNode->next->data.score < sortedNode->data.score)
                {
                    Node* prev = dummy;
                    while (prev->next != sortedNode->next && prev->next->data.score < sortedNode->next->data.score)
                    {
                        prev = prev->next;
                    }
                    Node* nextList = sortedNode->next;
                    sortedNode->next = sortedNode->next->next;
                    nextList->next = prev->next;
                    prev->next = nextList;
                }
                else
                {
                    sortedNode = sortedNode->next;
                }
            }
            head->next = dummy->next;
            break;
        }
    case 1:
        {
            while (sortedNode->next != NULL)
            {
                if (sortedNode->next->data.score > sortedNode->data.score)
                {
                    Node* prev = dummy;
                    while (prev->next != sortedNode->next && prev->next->data.score > sortedNode->next->data.score)
                    {
                        prev = prev->next;
                    }
                    Node* nextList = sortedNode->next;
                    sortedNode->next = sortedNode->next->next;
                    nextList->next = prev->next;
                    prev->next = nextList;
                }
                else
                {
                    sortedNode = sortedNode->next;
                }
            }
            head->next = dummy->next;
            break;
        }

    default:
        printf("输入错误！请重新输入！\n");
        break;
    }
    free(dummy);
}

//统计学生平均分
void calculate_students(Node* head)
{

}

