#include "db_struct.h"


Student* initStudent(char* line) {
    Student* student = (Student*) malloc(sizeof(Student));
    char firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH], phoneNumber[MAX_PHONE_LENGTH];
    int grade, class, scores[SCORE_COUNT];

    sscanf(line, "%s %s %s %i %i %i %i %i %i %i %i %i %i %i %i",
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

void print_student(School* school){
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            Student* current_student = school->grade[i].classes[j].studentHead;
            while (current_student != NULL) {
                printf("\n\nfirat name: %s, last Name: %s, phone Number: %s\nscores: ",
                       current_student->_firstName, current_student->_lastName, current_student->_phoneNumber);
                for (int k = 0; k < 10; ++k) {
                    printf( "%i, ", current_student->_scores[k]);
                }
                current_student = (Student *) current_student->_next;
            }
        }
    }
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