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
void free_student(Student* student);
void free_school(School* school);
void add_student(Class* class, Student* new_student);
Student* find_student(School* school, char* firstName, char* lastName);
void print_students(School* school);
void print_student(Student* student);
bool delete_student(School* school, char* firstName, char* lastName,int grade, int class);
bool update_student(School* school, char* firstName, char* lastName, const int* scores);
Student* recevie_students_to_departure(School* school);
int avg(Student* student);
void deep_copy_student(Student* target, Student* source);
int receive_average_by_class(School* school ,int grade, int score);
Student** receive_10_outstanding_students_in_school(School* school, int score);
Student* receive_10_outstanding_students_in_grade(Grade* grade, int score);
void insert_exellent_student(Student exellent[10], Student* student ,int score);
void print_exellent_students(Student** exellent);
void free_exellent_students(Student** exellent);
#endif //CHECKPOINT_BINYA2_DB_STRUCT_H
