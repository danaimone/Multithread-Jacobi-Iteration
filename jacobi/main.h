//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#ifndef JACOBI_MAIN_H
#define JACOBI_MAIN_H

#include <pthread.h>

int main(int argc, char *argv[]);

/* Compute the values for the new matrix from the previous matrix.
 * Input: previous matrix, new matrix, and start index
 * Output: void
 */
void compute(double (*P)[], double (*N)[], int increment, int startIndex);

/* create the given number of threads
 * Input: number of threads
 * Output: void
 */
void threadCreate(pthread_t threads[], int noth);

#endif //JACOBI_MAIN_H
