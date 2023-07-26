#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000

typedef struct {
    char line[MAX_LINE_LENGTH];
} LineNode;

void tailN(FILE* file, int n) {
    LineNode* buffer = (LineNode*)malloc(n * sizeof(LineNode));
    if (buffer == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    int currentIndex = 0;
    int lineCount = 0;

    // Read lines from the file and store them in the circular buffer
    char currentLine[MAX_LINE_LENGTH];
    while (fgets(currentLine, MAX_LINE_LENGTH, file) != NULL) {
        if (lineCount > n)
            currentIndex = (currentIndex + 1) % n;
        else
            lineCount++;

        // Copy the current line into the circular buffer
        strcpy(buffer[currentIndex].line, currentLine);
    }

    // Print the last n lines stored in the circular buffer
    int i;
    for (i = 0; i < lineCount; i++) {
        printf("%s", buffer[currentIndex].line);
        currentIndex = (currentIndex + 1) % n;
    }

    // Free allocated memory
    free(buffer);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s -n <number_of_lines>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[2]);

    if (n <= 0) {
        printf("Please enter a positive value for the number of lines.\n");
        return EXIT_FAILURE;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening the file");
        return EXIT_FAILURE;
    }

    tailN(file, n);

    fclose(file);

    return EXIT_SUCCESS;
}
