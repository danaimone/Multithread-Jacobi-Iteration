//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#ifndef JACOBI_BARRIER_H

#define JACOBI_BARRIER_H

#include <semaphore.h>
#include "cthread.h"

typedef struct Barrier {
    sem_t lock;
    int currentThreads;
    int continueIteration;
    int maxThreads;
    sem_t done[];
} barrier;

/* Initialize barrier
 * Input: barrier object and number of threads
 * Output: void
 */
void initBarrier(barrier *bar, int noth);

void freeBarrier(barrier *bar);

/* Blocks all threads from continuing Jacobi iteration
 * Input: barrier and current thread
 * Output: void
 */
void arrive(barrier *bar, struct ThreadArg *thread);

#endif //JACOBI_BARRIER_H
