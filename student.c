//
// Created by li on 25-7-3.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "student.h"

const char* genders[] = {
    "male", "female"
};

const char* gender_to_string(const int gender) {
    if (gender >= MALE && gender <= FEMALE) {
        return genders[gender];
    }
    return "invalid gender";
}

int read_students_from_file(const char* filename, Student students[]) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("Could not open file %s\n", filename);
        return -1;
    }

    char line[LINE_BUFFER_SIZE];
    int student_count = 0;
    Student current_student = {0};
    int parsing_id = 1;

    while (fgets(line, LINE_BUFFER_SIZE, f) != NULL) {
        line[strcspn(line, "\n")] = 0;

        if (line[0] == '\0') {
            continue;
        }

        if (parsing_id && line[0] == '#') {
            current_student.id = atoi(&line[1]);
            parsing_id = 0;
            continue;
        }

        const char* token = strtok(line, ":");
        if (token != NULL) {
            const char* field_name = token;
            while (isspace(*field_name)) field_name++;

            token = strtok(NULL, "");
            if (token != NULL) {
                const char* field_value = token;
                while (isspace(*field_value)) field_value++;

                if (strcmp(field_name, "name") == 0) {
                    strncpy(current_student.name, field_value, sizeof(current_student.name) - 1);
                    current_student.name[sizeof(current_student.name) - 1] = '\0';
                } else if (strcmp(field_name, "age") == 0) {
                    current_student.age = atoi(token);
                } else if (strcmp(field_name, "gender") == 0) {
                    if (strcmp(field_value, "male") == 0) {
                        current_student.gender = MALE;
                    } else if (strcmp(field_value, "female") == 0) {
                        current_student.gender = FEMALE;
                    }
                }
            }

            if (strcmp(field_name, "gender") == 0 && student_count < MAX_STUDENTS) {
                students[student_count++] = current_student;
                current_student = (Student) {0};
                parsing_id = 1;
            }
        }
    }

    fclose(f);
    return student_count;
}

void write_students_to_file(const char* filename, Student students[], const int n) {
    FILE* writer = fopen(filename, "w");
    if (writer == NULL) {
        fprintf(stderr, "Failed to open file %s\n", "student.txt");
    }
    for (int i = 0; i < n; i++) {
        Student *s = &students[i];
        fprintf(writer, "#%d\n"
                    "name: %s\n"
                    "age: %d\n"
                    "gender: %s\n", s->id, s->name, s->age, gender_to_string(s->gender));
    }
    fclose(writer);
}
