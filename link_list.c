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
Node* init_link()
{
    Node* head = (Node*)malloc(sizeof(Node));
    head->next = NULL;

    return head;
}

//添加学生节点---插入节点
bool insert_node(Node* head, Student s)
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
bool delete_node(Node* head, char* id)
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
        else
        {
            p = p->next;
        }
    }

    printf("查无此人，删除失败！");
    return false;
}

//查找学生节点
Node* search_student(Node* head, char* id)
{
    Node* p = head;
    while (p->next!= NULL)
    {
        if (strcmp(p->next->data.id, id) == 0)
        {
            p->next = p->next->next;
            return p->next;
        }
        else
        {
            p = p->next;
        }
    }

    printf("查无此人！");
    return NULL;
}

//新增计数功能，实时记录学生数量
int count_students(Node *head) {
    int count = 0;
    Node *p = head->next;
    while (p != NULL) {
        count++;
        p = p->next;
    }

    return count;
}
