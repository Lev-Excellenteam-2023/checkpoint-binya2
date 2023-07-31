#include <stdio.h>
#include "db_struct.h"

int main() {
    FILE *file;
    char buffer[100];

    file = fopen("/home/benny/exelenteam/checkpoint-binya2/students_with_class.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    School school;
    initSchool(&school);
    Student* new_student = NULL;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        new_student = initStudent(buffer);
        add_student(&school.grade[new_student->_grade - 1].classes[new_student->_class - 1], new_student);
    }
    fclose(file);
    print_student(&school);
    free_student(&school);
    return 0;
}
