//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#include <semaphore.h>
#include <stdlib.h>
#include <printf.h>
#include "barrier.h"
#include "cthread.h"

#define EPSILON 0.001

void barrierInit(barrier *bar, int noth){
    bar->maxThreads = noth;
    bar->currentThreads = 0;
    bar->cont = 1;
    for (int i = 0; i < noth; i++) {
        sem_init(&bar->done[i], 0, 1);
    }
    sem_init(&bar->lock, 0, 1);

}

void arrive(barrier *bar, tArg *thread){
    sem_wait(&bar->lock);
    bar->currentThreads++;
    if(thread->delta > EPSILON){
        bar->cont++;
    }
    bar->maxThreads = 1;
    sem_post(&bar->lock);


    if(bar->currentThreads < bar->maxThreads){
        sem_wait(&bar->done[thread->customThreadId]);
    } else {
        if(bar->cont == 1){
            bar->cont = 0;
        }else {
            for (int i = 0; i < bar->maxThreads; i++) {
                sem_post(&bar->done[i]);
            }
            sem_wait(&bar->done[thread->customThreadId]);
            bar->currentThreads = 0;
            bar->cont = 1;
        }
    }
}