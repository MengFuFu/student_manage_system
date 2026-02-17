//
// Created by Megumin on 2026/2/16.
//

/*实现链表的基本功能-增删改查-*/

#include "link_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//链表初始化---带头节点
Node* createList()
{
    Node* head = (Node*)malloc(sizeof(Node));
    head->next = NULL;

    return head;
}

//打印单个学生信息
void printStudent(Node* p)
{
    if (p == NULL)
    {
        return;;
    }
    printf("%s %s %s %d %d %d %d\n", p->data.id, p->data.name, p->data.classId, p->data.subjectScores[0],
    p->data.subjectScores[1], p->data.subjectScores[2], p->data.totalScore);
}

//添加学生节点---插入节点
bool insertNode(Node* head, Student s)
{
    if (head == NULL)
    {
        printf("程序出错，请传入正确的头节点!");
        return false;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        perror("内存分配失败！");
        return false;
    }

    newNode->next = head->next;
    newNode->data = s;
    head->next = newNode;

    return true;
}

//删除学生节点
bool deleteNode(Node* head, char* id)
{
    Node* p = head;
    while (p->next!= NULL)
    {
        if (strcmp(p->next->data.id, id) == 0)
        {
            p->next = p->next->next;
            printf("删除成功！");
            return true;
        }
        p = p->next;
    }

    printf("查无此人，删除失败！");
    return false;
}

//查找学生节点
Node* searchStudent(Node* head, char* id)
{
    Node* p = head;
    while (p->next!= NULL)
    {
        if (strcmp(p->next->data.id, id) == 0)
        {
            return p->next;
        }
        p = p->next;
    }

    printf("查无此人！");
    return NULL;
}

//查找并打印指定学生信息
void searchTargetStudent(Node* head, char* id)
{
    Node* tar = searchStudent(head, id);
    if (tar == NULL)
    {
        return;;
    }
    printf("学号 姓名 班级 科目一 科目二 科目三 总分\n");
    printStudent(tar);
}

//新增计数功能，实时记录学生数量
int countStudents(Node *head) {
    int count = 0;
    Node *p = head->next;
    while (p != NULL) {
        count++;
        p = p->next;
    }

    return count;
}

//打印所有学生信息
void printList(Node* head)
{
    Node* p = head->next;
    if (p == NULL)
    {
        printf("列表为空！请先加入学生后再试！");
        return;
    }
    printf("学号 姓名 班级 科目一 科目二 科目三 总分\n");
    while (p != NULL)
    {
        printStudent(p);
        p = p->next;
    }

}

//按照班级序号查找目标学生群体
void filterByClass(Node *head, char *classId)
{
    Node* p = head->next;
    if (p == NULL)
    {
        printf("列表为空！请先加入学生后再试！");
        return;
    }
    printf("学号 姓名 班级 科目一 科目二 科目三 总分\n");
    while (p != NULL)
    {
        if (strcmp(p->data.classId, classId) == 0)
        {
            printStudent(p);
        }
        p = p->next;
    }
}

//升级了排序功能，可对所有学生按照总成绩 单科成绩等排序（升序 / 降序）
void sortStudents(Node* head, int sortBy, int order)
{
    if (head->next == NULL || head->next->next == NULL)
    {
        return;
    }

    int swapped;
    Node* p;
    Node* q = NULL;
    do {
        swapped = 0;
        p = head;
        while (p->next != q) {
            int valA, valB;
            // 取值：总分/单科
            if (sortBy == 0) {
                valA = p->next->data.totalScore;
                valB = p->next->next->data.totalScore;
            } else {
                valA = p->next->data.subjectScores[sortBy-1];
                valB = p->next->next->data.subjectScores[sortBy-1];
            }
            // 比较：升序/降序
            int needSwap = 0;
            if (order == 0 && valA > valB)
            {
                needSwap = 1;
            }
            if (order == 1 && valA < valB)
            {
                needSwap = 1;
            }
            if (needSwap) {
                Student temp = p->next->data;
                p->next->data = p->next->next->data;
                p->next->next->data = temp;
                swapped = 1;
            }
            p = p->next;
        }
        q = p->next;
    } while (swapped);
}

//班内排名
int get_student_rank(Node* head, char* studentId, int sortBy)
{
    //找到目标学生
    Node* targetStudent = searchStudent(head, studentId);
    if (targetStudent == NULL)
    {
        return -1;
    }
    char targetClassId[20];
    strcpy(targetClassId, targetStudent->data.classId);

    //确定要比较的分数（总分 / 单科分）
    int targetScore;
    if (sortBy == 0)
    {
        targetScore = targetStudent->data.totalScore; // 总分比较
    }
    else
    {
        targetScore = targetStudent->data.subjectScores[sortBy - 1]; // 单科比较
    }

    //计算排名
    int rank = 1;
    Node* cur = head->next;

    while (cur != NULL)
    {
        if (strcmp(cur->data.classId, targetClassId) == 0)
        {
            int currentScore;
            if (sortBy == 0)
            {
                currentScore = cur->data.totalScore;
            }
            else
            {
                currentScore = cur->data.subjectScores[sortBy - 1];
            }

            if (currentScore > targetScore)
            {
                rank++;
            }
        }
        cur = cur->next;
    }

    return rank;
}