//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#ifndef JACOBI_CTHREAD_H
#define JACOBI_CTHREAD_H
#include <pthread.h>

typedef struct CustomThread {
    pthread_t thread;
    int customThreadId;
    double delta;
} cthread;


int getThreadId();

double getDelta();

int setThreadId(int newId);

double setDelta(double newDelta);

#endif //JACOBI_CTHREAD_H
