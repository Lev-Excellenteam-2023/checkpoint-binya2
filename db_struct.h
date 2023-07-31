#ifndef CHECKPOINT_BINYA2_DB_STRUCT_H
#define CHECKPOINT_BINYA2_DB_STRUCT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 11
#define SCORE_COUNT 10

typedef struct {
    char _firstName[MAX_NAME_LENGTH], _lastName[MAX_NAME_LENGTH], _phoneNumber[MAX_PHONE_LENGTH];
    int _grade, _class, _scores[SCORE_COUNT];
    struct Student* _next;
} Student;

typedef struct {
    Student *studentHead;
} Class;

typedef struct {
    Class classes[10];
} Grade;

typedef struct {
    Grade grade[12];
} School;

void initGrade(Grade* grade);
void initSchool(School* school);
Student* initStudent(char* line);
void add_student(Class* class, Student* new_student);
void print_student(School* school);
void free_student(School* school);

#endif //CHECKPOINT_BINYA2_DB_STRUCT_H
