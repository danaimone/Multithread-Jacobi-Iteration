/* Corben Roszak & Dan Aimone
 * CSCI 347
 * Jacobi Matrix Multi Threaded Project
 * Version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <zconf.h>
#include "main.h"
#include "cthread.h"
#include "barrier.h"


#define MATRIX_SIZE 1024
#define NOTH 4
#define EPSILON 0.0001

double (*previous)[MATRIX_SIZE];
double (*next)[MATRIX_SIZE];

int main(int argc, char *argv[]) {
    FILE *fp;
    previous = malloc(sizeof(double) * MATRIX_SIZE * MATRIX_SIZE);
    next = malloc(sizeof(double) * MATRIX_SIZE * MATRIX_SIZE);


    char *fName = processArgs(argc, argv);
    fp = fopen(fName, "r");
    fileToMatrix(fp, next, argv);
    fclose(fp);

    swapMatrix(next, previous);

    pthread_t threads[NOTH];
    barrier *bar = malloc(sizeof(barrier));
    initBarrier(bar, NOTH);
    createThread(threads, NOTH, bar);

    fp = fopen("jacobiOutput.mtx", "w");
    writeMatrixToFile(fp, next);

    fclose(fp);
    free(previous);
    free(next);
    freeBarrier(bar);
    return 0;
}

void fileToMatrix(FILE *file, double (*matrix)[], char *programArgs[]) {
    if (file != NULL) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                fscanf(file, "%lf ", &(*matrix + 1024 * i)[j]);
            }
        }
    } else {
        perror("fopen");
        printUsage(programArgs);
        exit(EXIT_FAILURE);
    }
}

void swapMatrix(double (*source)[], double (*dest)[]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            double val = (*source + 1024 * i)[j];
            (*dest + 1024 * i)[j] = val;
        }
    }
}

void writeMatrixToFile(FILE *fp, double (*matrix)[MATRIX_SIZE]) {
    if (fp != NULL) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                fprintf(fp, "%.10lf ", (*matrix + 1024 * i)[j]);
            }
            fprintf(fp, "\n");
        }
    } else {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fclose(fp);
}

void printMatrix(double (*matrix)[MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%lf ", (*matrix + 1024 * i)[j]);
        }
        printf("\n");
    }
}

char *processArgs(int argc, char *argv[]) {
    if (argc > 2) {
        printf("%s: expected 1 argument [file], but was given %d.\n", argv[0], argc - 1);
        printUsage(argv);
        exit(EXIT_FAILURE);
    }
    return argv[1];
}

void printUsage(char *argv[]) {
    printf("usage: %s [input-file]\n", argv[0]);
}


void createThread(pthread_t *threads, int noth, barrier *bar) {
    for (int i = 0; i < noth; i++) {
        tArg *threadArg = makeThreadArg(i, bar);
        pthread_create(&threads[i], NULL, computeJacobi, threadArg);
    }

    for (int i = 0; i < noth; i++) {
        tArg *retArg;
        pthread_join(threads[i], &retArg);
        free(retArg);
    }
}

tArg *computeJacobi(void *arg) {
    tArg *threadArg = arg;
    while (threadArg->bar->cont) {
        computeCell(*threadArg->prev, *threadArg->next, threadArg);
        arrive(threadArg->bar, threadArg, EPSILON);
        threadArg->delta = 0.0;
    }
    return threadArg;
}

tArg *makeThreadArg(int i, barrier *bar) {
    tArg *threadArg = malloc(sizeof(struct ThreadArg));
    threadArg->customThreadId = i;
    threadArg->delta = 0.0;
    threadArg->lock = &bar->done[i];
    threadArg->next = &next;
    threadArg->prev = &previous;
    threadArg->bar = bar;

    return threadArg;
}

void computeCell(double (*P)[MATRIX_SIZE], double (*N)[MATRIX_SIZE], tArg *thread) {
    int i = thread->customThreadId + 1;
    while (i < MATRIX_SIZE - 1) {
        for (int j = 1; j < MATRIX_SIZE - 1; j++) {
            (*N + 1024 * i)[j] = ((*P + 1024 * (i + 1))[j] + (*P + 1024 * (i - 1))[j] +
                                  (*P + 1024 * i)[j - 1] + (*P + 1024 * i)[j + 1]) / 4.0;
            double curDelta = (*N + 1024 * i)[j] - (*P + 1024 * i)[j];
            if (curDelta > thread->delta) {
                thread->delta = curDelta;
            }
        }
        i += NOTH;
    }
}