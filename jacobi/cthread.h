//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#ifndef JACOBI_CTHREAD_H
#define JACOBI_CTHREAD_H
#include <pthread.h>
#include <semaphore.h>
#include "barrier.h"

typedef struct ThreadArg{
    sem_t *lock;
    barrier *bar;
    int customThreadId;
    double delta;
    double (*prev)[];
    double (*next)[];
}tArg;

#endif //JACOBI_CTHREAD_H
