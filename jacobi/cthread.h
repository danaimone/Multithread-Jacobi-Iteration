//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#ifndef JACOBI_CTHREAD_H
#define JACOBI_CTHREAD_H
#include <pthread.h>
#include <bits/semaphore.h>

typedef struct threadArg{
    sem_t *lock;
    int customThreadId;
    double delta;
    double (*prev)[];
    double (*next)[];
}tArg;

#endif //JACOBI_CTHREAD_H
