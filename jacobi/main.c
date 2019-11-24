/* Corben Roszak & Dan Aimone
 * CSCI 347
 * Jacobi Matrix Multi Threaded Project
 * Version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <getopt.h>
#include <sys/stat.h>
#include "main.h"
#include "cthread.h"
#include "barrier.h"


#define MATRIX_SIZE 1024
#define NOTH 1

double (*previous)[MATRIX_SIZE];
double (*next)[MATRIX_SIZE];

int main(int argc, char *argv[]) {
    FILE *fp;
    previous = malloc(sizeof(double) * MATRIX_SIZE * MATRIX_SIZE);
    next = malloc(sizeof(double) * MATRIX_SIZE * MATRIX_SIZE);
    char *fileName = processArgs(argc, argv);
    fp = fopen(fileName, "r");
    if (fp != NULL) {
        //TODO: populate matrix, potentially do this another function
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                fscanf(fp, "%lf ", &(*previous+1024*i)[j]);
            }
        }
    } else {
        perror("fopen");
        printUsage(argv);
        exit(EXIT_FAILURE);
    }
    //printMatrix(previous, MATRIX_SIZE);

    //TODO: initialize threads
    pthread_t threads[NOTH];
    barrier *bar = malloc(sizeof(barrier));
    barrierInit(bar, NOTH, threads);
    threadCreate(threads, NOTH, bar);

    return 0;
}

void printMatrix(double (*matrix)[MATRIX_SIZE], int matrixSize) {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            printf("%lf ", (*matrix+1024*i)[j]);
        }
        printf("\n");
    }
}

char* processArgs(int argc, char *argv[]) {
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


void threadCreate(pthread_t threads[], int noth, barrier *bar){
    //init semaphore
    sem_t lock;
    sem_init(&lock, 0, 1);

    for(int i = 0; i < noth; i++) {
        //make block struct
        tArg *threadArg = makeThreadArg(previous, next, &lock, i, &bar);
        //TODO: start threads - &start_func (?) and tArg
        pthread_create(&threads[i], NULL, &computeJacobi, threadArg);
    }

    for(int i = 0; i < noth; i++){
        //TODO: join threads
        tArg *threadArg;
        pthread_join(threads[i], &threadArg);
        free(threadArg);
    }

    //destroy semaphore
    sem_destroy(&lock);
}

void computeJacobi(void *arg){
    struct ThreadArg *threadArg = arg;
    threadArg->delta = computeCell(threadArg->prev, threadArg->next, threadArg->customThreadId);
    arrive(threadArg->bar, threadArg);
}

tArg* makeThreadArg(double(*prev)[], double(*next)[], sem_t *lock, int i, barrier *bar){
    tArg *threadArg = malloc(sizeof(struct ThreadArg));
    threadArg->customThreadId = i;
    threadArg->delta = 0.0;
    threadArg->lock = lock;
    threadArg->next = next;
    threadArg->prev = prev;
    threadArg->bar = bar;

    return threadArg;
}

double computeCell(double (*P)[], double (*N)[], int threadNo){
    double maxDelta = 0.0;
    for(int i = threadNo; i < MATRIX_SIZE, i+=threadNo;){
        for(int j = 0; j < MATRIX_SIZE; j++){
            (*N)[j] = ( (*P+i)[j] + (*P-i)[j] +
                        (*P)[j-1] + (*P)[j+1]   ) / 4.0;
            double curDelta = (*P)[j] - (*N)[j];
            if(maxDelta > curDelta){
                maxDelta = curDelta;
            }
        }
    }
    return maxDelta;
}