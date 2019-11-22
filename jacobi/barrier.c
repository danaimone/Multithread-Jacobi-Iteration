//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#include "barrier.h"

void barrierInit(barrier *bar, unsigned noth){
    bar->maxThreads = noth;
    bar->currentthreads = 0;
    for (int i = 0; i < noth; i++) {
        sem_init(bar->done[i], 0, 0);
    }
    sem_init(bar->sem, 0, 0);

}

void arrive(barrier *bar, cthread thread){


}