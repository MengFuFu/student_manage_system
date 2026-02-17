//
// Created by Megumin on 2026/2/16.
//

#ifndef STUDENT_MANAGE_SYSTEM_FILE_UTIL_H
#define STUDENT_MANAGE_SYSTEM_FILE_UTIL_H

#include "account.h"

void saveStudentsToFile(const Node* head, const char* filename);
void loadStudentsFromFile(Node* head, const char* filename);
void saveAccountsToFile(AccountNode *head, const char *filename);
void loadAccountsFromFile(AccountNode *head, const char *filename);
void batchImportAccounts(AccountNode* head, const char* filename);
void batchExportAccounts(AccountNode* head, const char* filename);

#endif //STUDENT_MANAGE_SYSTEM_FILE_UTIL_H