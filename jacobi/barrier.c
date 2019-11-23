//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#include <semaphore.h>
#include "barrier.h"

void barrierInit(barrier *bar, unsigned noth){
    bar->maxThreads = noth;
    bar->currentthreads = 0;
    for (int i = 0; i < noth; i++) {
        sem_init(&bar->done[i], 0, 0);
    }
    sem_init(&bar->lock, 0, 1);

}

void arrive(barrier *bar, tArg thread){
    sem_wait(&bar->lock);
    bar->currentthreads++;
    sem_post(&bar->lock);

    if(bar->currentthreads < bar->maxThreads){
        sem_wait(&bar->done[thread.customThreadId]);
    } else {
        for(int i = 0; i < bar->maxThreads; i++){
            sem_post(&bar->done[i]);
        }
        sem_wait(&bar->done[thread.customThreadId]);
        bar->currentthreads = 0;
    }

}