#ifndef CHECKPOINT_BINYA2_DB_STRUCT_H
#define CHECKPOINT_BINYA2_DB_STRUCT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0
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
Student* initStudent_buffer(char* buffer);
Student* initStudent(char* firstName, char* lastName, char* phoneNumber, const int* scores);
void add_student(Class* class, Student* new_student);
Student* find_student(School* school, char* firstName, char* lastName);
void print_students(School* school);
void print_student(Student* student);
void free_student(School* school);
bool delete_student(School* school, char* firstName, char* lastName,int grade, int class);
bool update_student(School* school, char* firstName, char* lastName, const int* grade,const int* class, const int* scores);

#endif //CHECKPOINT_BINYA2_DB_STRUCT_H
