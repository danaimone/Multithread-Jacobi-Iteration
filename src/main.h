//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#ifndef JACOBI_MAIN_H
#define JACOBI_MAIN_H

#include <pthread.h>
#include "src/cthread.h"
#include "src/barrier.h"

int main(int argc, char *argv[]);

void writeMatrixToFile(FILE *file, double (*matrix)[]);

void copyMatrix(double (*matrix)[]);

char* processArgs(int argc, char *argv[]);

/*
 * Prints the usage of the program
 * Input:
 *  char *argv: used for grabbing program name instead of hard coding in
 * Output: void
 */
void printUsage(char *argv[]);

/*
 * Helper function: prints the contents of a matrix of doubles
 * Input:
 *  double matrix: matrix to be printed
 * Output: void
 */
void printMatrix(double (*matrix)[]);

/* Compute the values for the new matrix from the previous matrix.
 * Input:
 *  double (*P)[]: previous matrix
 *  double (*N)[]: new matrix
 *  tArg *thread: given thread
 * Output: void
 */
void computeCell(double (*P)[], double (*N)[], tArg *thread);

tArg* makeThreadArg(double(*prev)[], double(*next)[], int i, barrier *bar);
void computeJacobi(void *threadArg);

/* create the given number of threads
 * Input: number of threads
 * Output: void
 */
void threadCreate(pthread_t threads[], int noth, barrier *bar);

#endif //JACOBI_MAIN_H
