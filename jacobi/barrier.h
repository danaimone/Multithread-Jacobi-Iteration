//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#ifndef JACOBI_BARRIER_H

#define JACOBI_BARRIER_H

#include <semaphore.h>
#include "cthread.h"

typedef struct Barrier {
    sem_t lock;
    int maxThreads;
    int currentThreads;
    int cont;
    sem_t done[];
} barrier;

/* Initialize barrier
 * Input: barrier object and number of threads
 * Output: void
 */
void barrierInit(barrier *bar, int noth);

/* Blocks all threads from continuing Jacobi iteration
 * Input: barrier and current thread
 * Output: void
 */
void arrive(barrier *bar, struct ThreadArg *thread);

#endif //JACOBI_BARRIER_H
