//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#ifndef JACOBI_CTHREAD_H
#define JACOBI_CTHREAD_H
#include "src/barrier.h"
#include <pthread.h>
#include <semaphore.h>

typedef struct ThreadArg{
    sem_t *lock;
    struct Barrier *bar;
    int customThreadId;
    double delta;
    double (*prev)[];
    double (*next)[];
} tArg;

#endif //JACOBI_CTHREAD_H
