//
// Created by li on 25-7-3.
//

#include <stdio.h>
#include <string.h>

#include "system.h"
#include "config.h"

void print_menu(void) {
    printf("================Menu================\n");
    printf("1. Add student information.\n");
    printf("2. Del student information by id.\n");
    printf("3. Update student information.\n");
    printf("4. Query student information by id.\n");
    printf("5. List student information.\n");
    printf("6. Save.\n");
    printf("7. Exit(Not Save).\n");
}

void system_operator(Student students[MAX_STUDENTS], int *n, int *system_status, const int choice) {
    switch (choice) {
        case 1:
            add_student_info(students, n);
            break;
        case 2:
            del_student_info(students, n);
            break;
        case 3:
            update_student_info(students, *n);
            break;
        case 4:
            printf("Enter the student id: \n");
            int id;
            scanf("%d", &id);
            const int i = query_student_info_by_id(students, *n, id);
            if (i == -1) {
                printf("Student not found!\n");
                break;
            }
            printf("%-3d %-10s %-5d %-10s\n", students[i].id, students[i].name, students[i].age,
                   gender_to_string(students[i].gender));
            break;
        case 5:
            list_student_info(students, *n);
            break;
        case 6:
            save_student_info(students, *n);
            break;
        case 7:
            *system_status = 0;
            break;
        default:
            printf("Invalid choice.\n");
    }
}

void add_student_info(Student students[100], int* n) {
    printf("Enter the student information: \n");
    const int index = *n;
    char gender[10];
    scanf("%d %s %d %s", &students[index].id, &students[index].name, &students[index].age, &gender);
    const char* l_gender = strlwr(gender);
    if (strcmp(l_gender, "male") == 0) {
        students[index].gender = MALE;
    } else if (strcmp(l_gender, "female") == 0) {
        students[index].gender = FEMALE;
    }
    (*n)++;
}

void del_student_info(Student* students, int* n) {
    printf("Enter the student id of delete: \n");
    int id;
    scanf("%d", &id);
    const int index = query_student_info_by_id(students, *n, id);
    if (index == -1) {
        printf("Student not found!\n");
        return;
    }
    const int size = *n;
    for (int i = index; i < size - 1; i++) {
        students[i] = students[i + 1];
    }
    (*n)--;
}

void update_student_info(Student* students, int size) {
    printf("Enter the student id of update: \n");
    int id;
    scanf("%d", &id);
    const int index = query_student_info_by_id(students, size, id);
    if (index == -1) {
        printf("Student not found!\n");
        return;
    }
    printf("%-3d %-10s %-5d %-10s\n", students[index].id, students[index].name, students[index].age,
                   gender_to_string(students[index].gender));
    char gender[10];
    scanf("%d %s %d %s", &students[index].id, &students[index].name, &students[index].age, &gender);
    const char* l_gender = strlwr(gender);
    if (strcmp(l_gender, "male") == 0) {
        students[index].gender = MALE;
    } else if (strcmp(l_gender, "female") == 0) {
        students[index].gender = FEMALE;
    }
}

int query_student_info_by_id(const Student* students, const int n, const int id) {
    for (int i = 0; i < n; i++) {
        if (id == students[i].id) {
            return i;
        }
    }
    return -1;
}

void list_student_info(Student students[100], const int n) {
    printf("The list of student information:\n");
    for (int i = 0; i < n; i++) {
        printf("%-3d %-10s %-5d %-10s\n",
               students[i].id, students[i].name, students[i].age, gender_to_string(students[i].gender));
    }
}

void save_student_info(Student students[100], const int n) {
    write_students_to_file(DATA_FILE, students, n);
    printf("Successfully saved!\n");
}
