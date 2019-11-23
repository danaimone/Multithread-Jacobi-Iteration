//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#ifndef JACOBI_MAIN_H
#define JACOBI_MAIN_H

#include <pthread.h>
#include "cthread.h"
#include "barrier.h"

int main(int argc, char *argv[]);

char* processArgs(int argc, char *argv[]);

void printUsage(char *argv[]);

void printMatrix(double (*matrix)[], int matrixSize);

/* Compute the values for the new matrix from the previous matrix.
 * Input: previous matrix, new matrix, and start index
 * Output: void
 */
double computeCell(double (*P)[], double (*N)[], int threadNo);

tArg* makeThreadArg(double(*prev)[], double(*next)[], sem_t *lock, int i, barrier *bar);
void computeJacobi(void *threadArg);

/* create the given number of threads
 * Input: number of threads
 * Output: void
 */
void threadCreate(pthread_t threads[], int noth, barrier *bar);

#endif //JACOBI_MAIN_H
