//
// Created by Megumin on 2026/2/16.
//

#ifndef STUDENT_MANAGE_SYSTEM_LINK_LIST_H
#define STUDENT_MANAGE_SYSTEM_LINK_LIST_H
#define SUBJECT 3
#include <stdbool.h>

#endif //STUDENT_MANAGE_SYSTEM_LINK_LIST_H
//枚举类型定义三端，比直接使用数字会更有辨识度
typedef enum
{
    ROLE_STUDENT = 0,
    ROLE_TEACHER = 1,
    ROLE_ADMIN = 1
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
Node* searchStudent(Node* head, char* id);
void searchTargetStudent(Node* head, char* id);
void printList(Node* head);
int countStudents(Node* head);
void filterByClass(Node* head, char* classId);
void sortStudents(Node* head, int sortBy, int order);
int getClassRank(Node* head, char* studentId, int sortBy);