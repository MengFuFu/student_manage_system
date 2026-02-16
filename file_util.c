//
// Created by Megumin on 2026/2/16.
//

#include "file_util.h"
#include <stdio.h>

//把链表中的数据用二进制保存在文件中
void save_to_file(Node* head, const char* filename)
{
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("文件打开失败！");
        return;
    }

    Node* p = head->next;
    while (p != NULL)
    {
        fwrite(&p->data, sizeof(Student), 1, fp);
        p = p->next;
    }

    fclose(fp);
    printf("数据已保存到 %s\n", filename);
}

//数据重载，从文件加载到链表
void load_from_file(Node* head, const char* filename)
{
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("文件打开失败！");
        return;
    }

    int count = 0;
    Student s;
    while (fread(&s, sizeof(Student), 1, fp) == 1)
    {
        insert_node(head, s);
        count++;
    }

    fclose(fp);

    printf("加载到%d个数据", count);
}