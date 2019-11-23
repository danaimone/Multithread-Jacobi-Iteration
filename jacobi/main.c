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

const double (*previous)[MATRIX_SIZE];
const double (*next)[MATRIX_SIZE];

int main(int argc, char *argv[]) {
    FILE *fp;
    previous = malloc(sizeof(double) * MATRIX_SIZE * MATRIX_SIZE);
    next = malloc(sizeof(double) * MATRIX_SIZE * MATRIX_SIZE);
    char *fileName = processArgs(argc, argv);
    fp = fopen(fileName, "r");
    if (fp != NULL) {
        // TODO: populate matrix, potentially do this another function
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; i < MATRIX_SIZE; j++) {
                fscanf(fp, "%f", (*previous+i)[j]);
            }
        }
    } else {
        perror("fopen");
        printUsage(argv);
        exit(EXIT_FAILURE);
    }
    printMatrix(previous, MATRIX_SIZE);
    //TODO: initialize threads
//    pthread_t threads[NOTH];
//    threadCreate(threads, NOTH);

    return 0;
}

void printMatrix(const double (*matrix)[], int matrixSize) {
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; i < matrixSize; ++j) {
            printf("%f", (*matrix+i)[j]);
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

void threadCreate(pthread_t threads[], int noth){
    //init semaphore
    sem_t lock;
    sem_init(&lock, 0, 1);

    for(int i = 0; i < noth; i++) {
        //make block struct

        //will be the thread id (e.g. thread 0 will start at 0, thread 1 at 1)
        int startIndex = i;
        int increment = NOTH;
        //TODO: start threads - &start_func (?) and tArg
        //pthread_create(&threads[i, NULL, &start_func, block);
    }

    for(int i = 0; i < noth; i++){
        //TODO: join threads
        //new stuct
        //pthread_join(threads[i], &struct);
        //free(struct)
    }

    //destroy semaphore
    sem_destroy(&lock);
}

tArg makeThreadArg(){


}

void compute(double (*P)[], double (*N)[], int increment, int startIndex){
    for(int i = startIndex; i < MATRIX_SIZE, i+=increment;){
        for(int j = 0; j < MATRIX_SIZE; j++){
            (*N)[j] = ( (*P+i)[j] + (*P-i)[j] +
                        (*P)[j-1] + (*P)[j+1]   ) / 4.0;
        }
    }
}