//
// Created by Megumin on 2026/2/16.
//

#ifndef STUDENT_MANAGE_SYSTEM_LINK_LIST_H
#define STUDENT_MANAGE_SYSTEM_LINK_LIST_H
#include <stdbool.h>

#endif //STUDENT_MANAGE_SYSTEM_LINK_LIST_H

typedef struct {
    char id[20];
    char name[50];
    int score;
} Student;

typedef struct Node {
    Student data;
    struct Node* next;
} Node;

Node* link_init();
bool insert_node(Node* head, Student s);
bool delete_node(Node* head, char* id);
Node* search_student(Node* head, char* id);