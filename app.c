//
// Created by li on 25-7-3.
//

#include <stdio.h>

#include "config.h"
#include "student.h"
#include "system.h"


int main() {
    Student students[MAX_STUDENTS];
    int n = read_students_from_file(DATA_FILE, students);

    printf("Welcome to the StudentSystem!\n");
    int system_status = 1;
    while (system_status) {
        print_menu();
        int choice;
        scanf("%d", &choice);
        system_operator(students, &n, &system_status, choice);
    }
}
