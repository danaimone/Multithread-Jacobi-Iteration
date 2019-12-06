/* Corben Roszak & Dan Aimone
 * CSCI 347
 * Jacobi Matrix Multi Threaded Project
 * Version 1.0
 * Usage: --time : display elapsed time
 *        -e n : set epsilon
 *        -t n : set number of threads
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <zconf.h>
#include <time.h>
#include <getopt.h>
#include "main.h"
#include "cthread.h"
#include "barrier.h"


#define MATRIX_SIZE 1024
double EPSILON = 0.00001;

static int printTimeFlag = 0;
int NOTH = 1;
double (*previous)[MATRIX_SIZE];
double (*next)[MATRIX_SIZE];

int main(int argc, char *argv[]) {
    time_t start, end;
    time(&start);
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
    time(&end);
    if (printTimeFlag) {
        double timeTaken = (double) end - start;
        int hours = (timeTaken / 3600);
        int minutes = (timeTaken - (3600 * hours)) / 60;
        int seconds = (timeTaken - (3600 * hours) - (minutes * 60));
        printf("Execution time: %d hrs %d minutes %d seconds", hours, minutes, seconds);
    }
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

/*
 * Note: copies all values from source to destination
 */
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

char *processArgs(int argc, char *argv[]) {
    int opt;
    while (optind < argc) {
        static struct option longOptions[] =
                {
                        {"time",    no_argument,       &printTimeFlag, 1},
                        {"threads", required_argument, 0,              't'},
                        {"epsilon", required_argument, 0,              'e'},
                        {0, 0,                         0,              0}
                };

        int optionIndex = 0;
        opt = getopt_long(argc, argv, "t:e:", longOptions, &optionIndex);
        if (opt == -1)
            break;

        switch (opt) {
            case 0:
                if (longOptions[optionIndex].flag != 0)
                    break;
                printf("option %s", longOptions[optionIndex].name);
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");
                break;

            case 't':
                NOTH = atoi(optarg);
                break;

            case 'e':
                EPSILON = strtod(optarg, NULL);
                break;

            case '?':
                break;

            default:
                abort();
        }
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
        void *retArg;
        pthread_join(threads[i], &retArg);
        free(retArg);
    }
}

/*
 * Note: thread '0' is the 'main' thread that swaps the matrices and checks if the program
 *       should continue.
 */
tArg *computeJacobi(void *arg) {
    tArg *threadArg = arg;
    while (threadArg->bar->continueIteration != 0) {
       arrive(threadArg->bar, threadArg);

        computeCell(*threadArg->prev, *threadArg->next, threadArg);

        if(threadArg->delta > EPSILON){
            threadArg->bar->continueIteration = 2;
        }

        arrive(threadArg->bar, threadArg);

        if(threadArg->customThreadId == 0){
            swapMatrix(*threadArg->next, *threadArg->prev);
            continueIterationCheck(threadArg->bar);
        }
        threadArg->delta = 0.0;
        arrive(threadArg->bar, threadArg);
    }
    return threadArg;
}

/*
 * Note: continueIteration = 1 : exit
 *                           2 : continue program
 */
void continueIterationCheck(barrier *bar){
    if(bar->continueIteration == 1){
        bar->continueIteration = 0;
    } else {
        bar->continueIteration = 1;
    }
}

tArg *makeThreadArg(int id, barrier *bar) {
    tArg *threadArg = malloc(sizeof(struct ThreadArg));
    threadArg->customThreadId = id;
    threadArg->delta = 0.0;
    threadArg->lock = &bar->done[id];
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