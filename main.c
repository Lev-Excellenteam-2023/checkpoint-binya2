#include <stdio.h>

int main() {
    FILE *file;
    char buffer[100];

    file = fopen("C:\\exselentim\\bootcamp\\checkpoint-binya2\\students_with_class.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);

    return 0;
}
