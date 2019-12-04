//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#include <semaphore.h>
#include <stdlib.h>
#include <printf.h>
#include <zconf.h>
#include "barrier.h"
#include "cthread.h"
#include "main.h"

void initBarrier(barrier *bar, int noth) {
    bar->currentThreads = 0;
    bar->continueIteration = 1;
    bar->maxThreads = noth;
    bar->lock = (sem_t) malloc(sizeof(sem_t));
    sem_post(&bar->lock);
    bar->done[noth] = (sem_t) malloc(sizeof(sem_t) * noth);
    for (int i = 0; i < noth; i++) {
        sem_post(&bar->done[i]);
    }
}

void freeBarrier(barrier *bar) {
    free(&bar->lock);
    free(bar->done);
}

void arrive(barrier *bar, tArg *thread) {
    sem_wait(&bar->lock);
    bar->currentThreads++;
    sem_post(&bar->lock);

    if (bar->currentThreads < bar->maxThreads) {
        sem_wait(thread->lock);
    } else {
        bar->currentThreads = 0;
        for (int i = 0; i < bar->maxThreads; i++) {
            sem_post(&bar->done[i]);
        }
        sem_wait(thread->lock);
    }
}