//
// Created by li on 25-7-3.
//

#ifndef SYSTEM_H
#define SYSTEM_H
#include "student.h"

void print_menu(void);

void system_operator(Student students[100], int *n, int *system_status, int choice);

void add_student_info(Student students[100], int *n);

void del_student_info(Student* students, int* n);

void update_student_info(Student* students, int size);

int query_student_info_by_id(const Student* students, int n, int id);

void list_student_info(Student students[100], int n);

void save_student_info(Student students[100], int n);

#endif //SYSTEM_H
