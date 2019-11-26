#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Usage: ./main output_matrix final_matrix
 *
 * output_matrix is the one from our program
 * final_matrix is the expected output matrix
 *
 * output should be +/- 1 of the target epsilon
 */

#define MATRIX_SIZE 1024

int main(int argc, char *argv[]);
void compare(double(*out)[], double(*fin)[]);

double (*output)[MATRIX_SIZE];
double (*final)[MATRIX_SIZE];

int main(int argc, char *argv[]) {
    char *outputName = strdup(argv[1]);
    char *finalName = strdup(argv[2]);
    FILE *fpOut;
    FILE *fpFin;
    output = malloc(sizeof(double) * MATRIX_SIZE * MATRIX_SIZE);
    final = malloc(sizeof(double) * MATRIX_SIZE * MATRIX_SIZE);
    fpOut = fopen(outputName, "r");
    fpFin = fopen(finalName, "r");

    if (fpOut != NULL) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                fscanf(fpOut, "%lf ", &(*output + 1024 * i)[j]);
            }
        }
    } else {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fclose(fpOut);
    if (fpFin != NULL) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                fscanf(fpFin, "%lf ", &(*final + 1024 * i)[j]);
            }
        }
    } else {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fclose(fpFin);

    compare(output, final);

    return 0;
}

void compare(double(*out)[], double(*fin)[]){
    double maxDelta = 0.0;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            double curDelta = (*fin + 1024 * i)[j] - (*out + 1024 * i)[j];
            if (curDelta > maxDelta) {
                maxDelta = curDelta;
            }
        }
    }
    printf("Max delta is: %lf \n", maxDelta);
}