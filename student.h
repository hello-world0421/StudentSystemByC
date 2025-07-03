//
// Created by li on 25-7-3.
//

#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100
#define LINE_BUFFER_SIZE 1024

typedef enum {
    MALE = 0,
    FEMALE = 1,
} gender;

typedef struct {
    int id;
    char name[50];
    int age;
    gender gender;
} Student;

int read_students_from_file(const char* filename, Student students[]);

void write_students_to_file(const char* filename, Student students[], int n);

const char* gender_to_string(int gender);

#endif //STUDENT_H
