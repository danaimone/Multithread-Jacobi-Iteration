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

void barrierInit(barrier *bar, int noth){
    bar->currentThreads = 0;
    bar->cont = 1;
    bar->maxThreads = noth;
    for (int i = 0; i < noth; i++) {
        sem_init(&bar->done[i], 0, 0);
    }
    sem_init(&bar->lock, 0, 1);
}

void arrive(barrier *bar, tArg *thread, double epsilon){
    sem_wait(&bar->lock);
    bar->currentThreads++;
    if(thread->delta > epsilon){
        bar->cont++;
    }
    sem_post(&bar->lock);

    //TODO: threads are no blocking at all.
    if(bar->currentThreads < bar->maxThreads){
        printf("WAIT: %d \n", thread->customThreadId);
        sem_wait(&bar->done[thread->customThreadId]);
    } else {
        if(bar->cont == 1){
            bar->cont = 0;
        }else {
            sem_wait(&bar->done[thread->customThreadId]);
            printf("GO: %d \n", thread->customThreadId);
            //printf("%.10f \n", thread->delta);
            for (int i = 0; i < bar->maxThreads; i++) {
                sem_post(&bar->done[i]);
            }
            bar->currentThreads = 0;
            bar->cont = 1;
            //swap matricies here cause they should just be pointers so only one thread needs to swap them.
            sem_wait(&bar->lock);
            swapMatrix();
            sem_post(&bar->lock);
        }
    }
}