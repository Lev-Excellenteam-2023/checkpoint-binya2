#include <stdio.h>
#include "db_struct.h"



bool save_data_from_file(School* school, char* file_path){
    FILE *file;
    char buffer[100];
    file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return false;
    }
    Student* new_student = NULL;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        new_student = initStudent_buffer(buffer);
        add_student(&school->grade[new_student->_grade - 1].classes[new_student->_class - 1], new_student);
    }
    fclose(file);
    return true;
}

int main() {
    School school;
    initSchool(&school);
    Student* student = NULL;
    char firstName[MAX_NAME_LENGTH], lastName[MAX_NAME_LENGTH], phoneNumber[MAX_PHONE_LENGTH];
    int grade, class, scores[SCORE_COUNT], choice,  score;
//    if (save_data_from_file(&school, "/home/benny/exelenteam/checkpoint-binya2/students_with_class.txt")){
//        printf("Data loaded successfully\n");
//    } else {
//        printf("Failed to load data\n");
//        return 1;
//    }
    while (true){
        printf("insert\n"
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
                if (delete_student(&school, firstName, lastName, grade, class)){
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
                printf("Enter grade number: ");
                scanf("%i", &grade);
                printf("Enter class number: ");
                scanf("%i", &class);
                for (int i = 0; i < 10; ++i) {
                    printf("Enter new score number %i: ", i + 1);
                    scanf("%i", &scores[i]);
                }
                if (update_student(&school, firstName, lastName, &grade, &class, scores)){
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
                if (student != NULL){
                    printf("Student found\n");
                    print_student(student);
                } else {
                    printf("Student not found\n");
                }
                break;
                break;
            case 5:
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
                printf("Average is: %i\n", receive_average_by_class(&school, grade-1, score-1));
                break;
            case 8:
                print_students(&school);
                break;
            default:
                printf("invalid choice\n");
        }
    }

    print_students(&school);
    free_school(&school);
    return 0;
}
