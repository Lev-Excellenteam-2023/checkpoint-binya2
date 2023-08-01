#include <stdio.h>
#include "db_struct.h"
#include "db_struct.c"

char *student_to_buffer(Student *current_student, int grade, int class);

bool save_data_from_file(School *school, char *file_path);

void enter_to_file(School *school);

size_t get_input(char *dst, size_t max_size);

int main() {
    School school;
    initSchool(&school);
    Student *student = NULL;
    char firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH], phoneNumber[MAX_PHONE_LENGTH];
    int grade, class, scores[SCORE_COUNT], choice, score;
    if (save_data_from_file(&school, "/home/benny/exelenteam/checkpoint-binya2/students_with_class.txt")) {
        printf("Data loaded successfully\n");
    } else {
        printf("Failed to load data\n");
        return 1;
    }
    while (true) {
        printf("\ninsert\n"
               "1 To admit a new student,\n"
               "2 To delete a student,\n"
               "3 To change information,\n"
               "4 To search for a student by name,\n"
               "5 To receive the 10 outstanding students in each grade in a particular subject,\n"
               "6 to receive a list of students who are candidates for departure,\n"
               "7 Get an average by class/course,\n"
               "8 Export the DB to a file\n"
               "0 to exit\n");
        scanf("%i", &choice);

        switch (choice) {
            case 0:
                free_school(&school);
                return 0;
            case 1:
                printf("Enter first name : ");
                scanf("%s", firstName);
                printf("Enter last name : ");
                scanf("%s", lastName);
                printf("Enter phone number : ");
                scanf("%s", phoneNumber);
                printf("Enter grade number: ");
                scanf("%i", &grade);
                printf("Enter class number: ");
                scanf("%i", &class);
                for (int i = 0; i < 10; ++i) {
                    printf("Enter score number %i: ", i + 1);
                    scanf("%i", &scores[i]);
                }
                student = initStudent(firstName, lastName, phoneNumber, scores);
                add_student(&school.grade[grade - 1].classes[class - 1], student);
                break;
            case 2:
                printf("Enter first name : ");
                scanf("%s", firstName);
                printf("Enter last name : ");
                scanf("%s", lastName);
                printf("Enter grade number: ");
                scanf("%i", &grade);
                printf("Enter class number: ");
                scanf("%i", &class);
                if (delete_student(&school, firstName, lastName, grade, class)) {
                    printf("Student deleted successfully\n");
                } else {
                    printf("Student not found\n");
                }
                break;
            case 3:
                printf("Enter first name : ");
                scanf("%s", firstName);
                printf("Enter last name : ");
                scanf("%s", lastName);
                for (int i = 0; i < 10; ++i) {
                    printf("Enter new score number %i: ", i + 1);
                    scanf("%i", &scores[i]);
                }
                if (update_student(&school, firstName, lastName, scores)) {
                    printf("Student updated successfully\n");
                } else {
                    printf("Student not found\n");
                }
                break;
            case 4:
                printf("Enter first name : ");
                scanf("%s", firstName);
                printf("Enter last name : ");
                scanf("%s", lastName);
                student = find_student(&school, firstName, lastName);
                if (student != NULL) {
                    Student* student_copy = malloc(sizeof(Student));
                    deep_copy_student(student_copy, (Student *)student);
                    printf("Student found\n");
                    print_student(student_copy);
                    free_student(student_copy);
                } else {
                    printf("Student not found\n");
                }
                break;
            case 5:
                printf("Enter score number: ");
                scanf("%i", &score);
                Student **exel_student = (Student **) receive_10_outstanding_students_in_school(&school, score);
                print_exellent_students(exel_student);
                free_exellent_students(exel_student);
                break;
            case 6:
                student = (Student *) recevie_students_to_departure(&school);
                print_student(student);
                free_student(student);
                break;
            case 7:
                printf("Enter grade number: ");
                scanf("%i", &grade);
                printf("Enter score number: ");
                scanf("%i", &score);
                printf("Average is: %i\n", receive_average_by_class(&school, grade - 1, score - 1));
                break;
            case 8:
                enter_to_file(&school);
                break;
            default:
                printf("invalid choice\n");
        }
    }
}

bool save_data_from_file(School *school, char *file_path) {
    FILE *file;
    char buffer[100];
    file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return false;
    }
    Student *new_student = NULL;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        new_student = initStudent_buffer(buffer);
        add_student(&school->grade[new_student->_grade - 1].classes[new_student->_class - 1], new_student);
    }
    fclose(file);
    return true;
}

void enter_to_file(School *school) {
    char *buffer;
    FILE *file;
    file = fopen("/home/benny/exelenteam/checkpoint-binya2/students_with_class_output.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            Student *current_student = school->grade[i].classes[j].studentHead;
            while (current_student != NULL) {
                buffer = student_to_buffer(current_student, i + 1, j + 1);
                fputs(buffer, file);
                fputc('\n', file);
                current_student = (Student *) current_student->_next;
                free(buffer);
            }
        }
    }
    fclose(file);
}

char *student_to_buffer(Student *current_student, int grade, int class) {
    char *buffer = (char *) malloc(100 * sizeof(char));
    sprintf(buffer, "%s %s %s %i %i %i %i %i %i %i %i %i %i %i %i",
            current_student->_firstName, current_student->_lastName, current_student->_phoneNumber,
            grade, class, current_student->_scores[0], current_student->_scores[1], current_student->_scores[2],
            current_student->_scores[3], current_student->_scores[4], current_student->_scores[5],
            current_student->_scores[6], current_student->_scores[7], current_student->_scores[8],
            current_student->_scores[9]);
    return buffer;
}


/*
 * The function gets input from the user and ensures the input
 * doesn't exceed max_size. if yes - it will shrink it and will add \0.
 */

size_t get_input(char *dst, size_t max_size) {
    fflush(stdin);
    char *input = NULL;
    size_t len = 0;
    size_t len_size = 0;
    len_size = getline(&input, &len, stdin);
    if (len_size == -1)
        return -1;
    if (len_size < max_size) {
        input[len_size - 1] = '\0';
        strncpy(dst, input, len_size);
    } else {
        input[max_size - 1] = '\0';
        strncpy(dst, input, max_size);
        len_size = max_size;
    }
    free(input);
    return len_size;
}

