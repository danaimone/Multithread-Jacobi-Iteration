/* Corben Roszak & Dan Aimone
 * CSCI 347
 * Jacobi Matrix Multi Threaded Project
 * Version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "cthread.h"
#include "barrier.h"

#define MATRIX_SIZE 1024
#define NOTH 1

const double (*previous)[MATRIX_SIZE];

int main(int argc, char *argv[]) {
    previous = malloc(sizeof(double) * MATRIX_SIZE * MATRIX_SIZE);
    //TODO: initialize threads
    pthread_t threads[NOTH];
    threadCreate(threads, NOTH);


    return 0;
}

void threadCreate(pthread_t threads[], int noth){
    //init semaphore

    for(int i = 0; i < noth, i++) {
        //will be the thread id (e.g. thread 0 will start at 0, thread 1 at 1)
        int startIndex = 0;
        int increment = NOTH;

        //TODO: start threads - &start_func (compute?) and block (barrier?)
        //pthread_create(&threads[i, NULL, &start_func, block);
    }

    for(int i = 0; i < noth; i++){
        //TODO: join threads
        //new stuct
        //pthread_join(threads[i], &struct);
        //free(struct)
    }

    //destroy semaphore

}

void compute(double (*P)[], double (*N)[], int increment, int startIndex){
    for(int i = startIndex; i < MATRIX_SIZE, i+=increment;){
        for(int j = 0; j < MATRIX_SIZE; j++){
            (*N)[j] = ( (*P+i)[j] + (*P-i)[j] +
                        (*P)[j-1] + (*P)[j+1]   ) / 4.0;
        }
    }
}