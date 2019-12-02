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
    bar->done[noth] = (sem_t) malloc(sizeof(sem_t) * noth);
    for (int i = 0; i < noth; i++) {
        sem_init(&bar->done[i], 0, 1);
    }
    sem_init(&bar->lock, 0, 1);
}

void freeBarrier(barrier *bar) {
    free(bar->done);
    free(&bar->lock);
}

void arrive(barrier *bar, tArg *thread, double epsilon) {
    sem_wait(&bar->lock);
    bar->currentThreads++;
    //TODO: maybe do this differently?
    if (thread->delta > epsilon) {
        bar->continueIteration = 2;
    }
    sem_post(&bar->lock);

    if (bar->currentThreads < bar->maxThreads) {
        sem_wait(&bar->done[thread->customThreadId]);
    } else {
        if (bar->continueIteration == 1) {
            bar->continueIteration = 0;
        } else {
            //TODO: make this a rendezvous for the threads.
            swapMatrix(*thread->next, *thread->prev);

            for (int i = 0; i < bar->maxThreads; i++) {
                sem_post(&bar->done[i]);
            }
            sem_wait(&bar->done[thread->customThreadId]);
            bar->currentThreads = 0;
            bar->continueIteration = 1;
        }
    }
}