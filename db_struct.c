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

void free_student(Student* student){
    while(student != NULL){
        Student* temp = (Student*) student->_next;
        free(student);
        student = temp;
    }
    free(student);
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

void free_school(School* school){
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            Student* current_student = school->grade[i].classes[j].studentHead;
            free_student(current_student);
        }
    }
}

bool update_student(School* school, char* firstName, char* lastName, const int* scores){
    Student* student = find_student(school, firstName, lastName);
    if (student != NULL) {
        strcpy(student->_firstName, firstName);
        strcpy(student->_lastName, lastName);
        for (int i = 0; i < 10; i++) {
            student->_scores[i] = scores[i];
        }
        return true;
    }
    return false;
}

Student* recevie_students_to_departure(School* school){
    Student* departure = NULL;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            Student* current_student = school->grade[i].classes[j].studentHead;
            while (current_student != NULL) {
                if ( avg(current_student)< 60) {
                    if(departure == NULL){
                        Student* temp = (Student*) malloc(sizeof(Student));
                        deep_copy_student((Student *)temp, current_student);
                        departure = temp;
                    }else{
                        Student* temp;
                        temp = (Student*) malloc(sizeof(Student));
                        deep_copy_student((Student *)temp, current_student);
                        temp ->_next = (struct Student *) departure;
                        departure = temp;
                    }
                }
                current_student = (Student *) current_student->_next;
            }
        }
    }
    return departure;
}

int avg(Student* student){
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += student->_scores[i];
    }
    return sum/10;
}

void deep_copy_student( Student* target, Student* source){
    strcpy(target->_firstName, source->_firstName);
    strcpy(target->_lastName, source->_lastName);
    strcpy(target->_phoneNumber, source->_phoneNumber);
    target->_grade = source->_grade;
    target->_class = source->_class;
    for (int i = 0; i < 10; i++) {
        target->_scores[i] = source->_scores[i];
    }
    target->_next = NULL;
}

int receive_average_by_class(School* school ,int grade, int score){
    int sum = 0;
    int count = 0;
    for (int i = 0; i < 10; i++) {
        Student* current_student = school->grade[grade].classes[i].studentHead;
        while (current_student != NULL) {
            sum += current_student->_scores[score];
            count++;
            current_student = (Student *) current_student->_next;
        }
    }
    return sum/count;
}

Student** receive_10_outstanding_students_in_school(School* school , int score){
    Student** exellent = (Student**) malloc(sizeof(Student) * 12);
    for (int i = 0; i < 12; i++) {
        exellent[i] = receive_10_outstanding_students_in_grade(&school->grade[i], score);
    }
    return exellent;
}

Student* receive_10_outstanding_students_in_grade(Grade* grade, int score) {
    Student* exellent = (Student*) malloc(sizeof(Student)*10);
    int count = 0;
    for (int i = 0; i < 10; i++) {
        exellent[i]._scores[score] = count++;
    }
    for (int i = 0; i < 10; i++) {
        Student* current_student = grade->classes[i].studentHead;
        while (current_student != NULL) {
            insert_exellent_student(exellent, current_student, score);
            current_student = (Student *) current_student->_next;
        }
    }
    return exellent;
}

void insert_exellent_student(Student exellent[10], Student* student ,int score){
    Student* temp = (Student*) malloc(sizeof(Student));
    Student* temp1 = (Student*) malloc(sizeof(Student));
    for (int i = 9; i >= 0; i--) {
        if (student->_scores[score] > exellent[i]._scores[score]) {
            if (i == 0) {
                free(temp);
                free(temp1);
                return;
            }
            deep_copy_student((Student *) temp,&exellent[i]);
            deep_copy_student(&exellent[i], student);
            i--;
            for (int j = i ; j >= 0; j--) {
                deep_copy_student((Student *) temp1, &exellent[j]);
                deep_copy_student(&exellent[j], (Student *) temp);
                deep_copy_student((Student *) temp, (Student *) temp1);
                if (j == 0) {
                    free(temp);
                    free(temp1);
                    return;
                }
            }
        }
    }
    free(temp);
    free(temp1);
}

void print_exellent_students(Student** exellent){
    for (int i = 0; i < 12; i++) {
        printf("\ngrade %i", i+1);
        for (int j = 0; j < 10; j++) {
            print_student(&exellent[i][j]);
        }
    }
}

void free_exellent_students(Student** exellent){
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; ++j) {
            free(&exellent[i][j]);
        }
        free(exellent[i]);
    }
    free(exellent);
}