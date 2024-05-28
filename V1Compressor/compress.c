#include <stdio.h>
#include <stdlib.h>

void compressFile(const char *inputFilename, const char *outputFilename) {
    FILE *inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char currentChar, previousChar = '\0';

    if ((previousChar = fgetc(inputFile)) != EOF) {
        count = 1;
        while ((currentChar = fgetc(inputFile)) != EOF) {
            if (currentChar == previousChar) {
                count++;
            } else {
                if (count > 1) {
                    fprintf(outputFile, "%d%c", count, previousChar);
                } else {
                    fprintf(outputFile, "%c", previousChar);
                }
                previousChar = currentChar;
                count = 1;
            }
        }
        // Output the last run
        if (count > 1) {
            fprintf(outputFile, "%d%c", count, previousChar);
        } else {
            fprintf(outputFile, "%c", previousChar);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    compressFile(argv[1], argv[2]);
    printf("File compressed successfully.\n");

    return EXIT_SUCCESS;
}
