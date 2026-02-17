//
// Created by Megumin on 2026/2/16.
//

#ifndef STUDENT_MANAGE_SYSTEM_LINK_LIST_H
#define STUDENT_MANAGE_SYSTEM_LINK_LIST_H
#define SUBJECT 3
#include <stdbool.h>
#include "safe_stdin.h"

//枚举类型定义三端，比直接使用数字会更有辨识度
typedef enum
{
    ROLE_STUDENT = 0,
    ROLE_TEACHER = 1,
    ROLE_ADMIN = 2
}UserRole;

typedef struct Student{
    char id[20];
    char name[50];
    char classId[20];
    int subjectScores[SUBJECT];
    int totalScore;
} Student;

typedef struct Node {
    Student data;
    struct Node* next;
} Node;

Node* createList();
void printStudent(Node* p);
bool insertNode(Node* head, Student s);
bool deleteNode(Node* head, char* id);
void destroyList(Node* head);
Node* searchStudent(Node* head, char* id);
void printList(Node* head);
int countStudents(Node* head);
Node* filterByClass(Node* head, char* classId);
void sortStudents(Node* head, int sortBy, int order);
int getStudentRank(Node* head, char* studentId, int sortBy);

#endif //STUDENT_MANAGE_SYSTEM_LINK_LIST_H