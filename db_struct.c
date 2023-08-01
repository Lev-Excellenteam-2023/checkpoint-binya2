#include "db_struct.h"


Student* initStudent_buffer(char* buffer) {
    Student* student = (Student*) malloc(sizeof(Student));
    char firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH], phoneNumber[MAX_PHONE_LENGTH];
    int grade, class, scores[SCORE_COUNT];

    sscanf(buffer, "%s %s %s %i %i %i %i %i %i %i %i %i %i %i %i",
           firstName, lastName, phoneNumber, &grade, &class,
           &scores[0], &scores[1], &scores[2], &scores[3], &scores[4],
           &scores[5], &scores[6], &scores[7], &scores[8], &scores[9]);

    strcpy(student->_firstName, firstName);
    strcpy(student->_lastName, lastName);
    strcpy(student->_phoneNumber, phoneNumber);
    student->_grade = grade;
    student->_class = class;
    for (int i = 0; i < 10; i++) {
        student->_scores[i] = scores[i];
    }
    student->_next = NULL;
    return student;
}

Student* initStudent(char* firstName, char* lastName, char* phoneNumber, const int* scores) {
    Student* student = (Student*) malloc(sizeof(Student));
    strcpy(student->_firstName, firstName);
    strcpy(student->_lastName, lastName);
    strcpy(student->_phoneNumber, phoneNumber);
    for (int i = 0; i < 10; i++) {
        student->_scores[i] = scores[i];
    }
    student->_next = NULL;
    return student;
}

Student* find_student(School* school, char* firstName, char* lastName){
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            Student* current_student = school->grade[i].classes[j].studentHead;
            while (current_student != NULL) {
                if (strcmp(current_student->_firstName, firstName) == 0 &&
                    strcmp(current_student->_lastName, lastName) == 0) {
                    return current_student;
                }
                current_student = (Student *) current_student->_next;
            }
        }
    }
    return NULL;
}

void initGrade(Grade* grade){
    for (int i = 0; i < 10; i++) {
        grade->classes[i].studentHead = NULL;
    }
}

void initSchool(School* school){
    for (int i = 0; i < 12; i++) {
        initGrade(&school->grade[i]);
    }
}

void add_student(Class* class, Student* new_student) {
    Student* current_student = class->studentHead;
    if (current_student == NULL) {
        class->studentHead = new_student;
    } else  {
        new_student->_next = (struct Student *) current_student;
        class->studentHead = new_student;
    }
}

void print_students(School* school){
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            Student* current_student = school->grade[i].classes[j].studentHead;
            print_student(current_student);
        }
    }
}

void print_student(Student* student){
    while(student != NULL){
        printf("\nfirat name: %s, last Name: %s, phone Number: %s\nscores: ",
               student->_firstName, student->_lastName, student->_phoneNumber);
        for (int k = 0; k < 10; ++k) {
            printf( "%i, ", student->_scores[k]);
        }
        student = (Student *) student->_next;
    }
}

bool delete_student(School* school, char* firstName, char* lastName,int grade, int class){
    Student* current_student  = school->grade[grade-1].classes[class-1].studentHead;
    Student* prev_student = school->grade[grade-1].classes[class-1].studentHead;
    while (current_student != NULL) {
        if (strcmp(current_student->_firstName, firstName) == 0 &&
            strcmp(current_student->_lastName, lastName) == 0) {
            if (current_student == school->grade[grade-1].classes[class-1].studentHead) {
                school->grade[grade-1].classes[class-1].studentHead = (Student *) current_student->_next;
                current_student->_next = NULL;
                free(current_student);
                return true;
            }
            prev_student->_next = (struct Student *) (Student *) current_student->_next;
            current_student->_next = NULL;
            free(current_student);
            return true;
        }
        prev_student = current_student;
        current_student = (Student *) current_student->_next;
    }
    return false;
}

void free_student(School* school){
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            Student* current_student = school->grade[i].classes[j].studentHead;
            while (current_student != NULL) {
                Student* temp = current_student;
                current_student = (Student *) current_student->_next;
                free(temp);
            }
        }
    }
}

bool update_student(School* school, char* firstName, char* lastName, const int* grade,const int* class, const int* scores){
    Student* student = find_student(school, firstName, lastName);
    if (student != NULL) {
        strcpy(student->_firstName, firstName);
        strcpy(student->_lastName, lastName);
        student->_grade =  *grade;
        student->_class =  *class;
        for (int i = 0; i < 10; i++) {
            student->_scores[i] = scores[i];
        }
        return true;
    }
    return false;
}
