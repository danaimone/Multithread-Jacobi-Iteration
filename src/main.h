//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#ifndef JACOBI_MAIN_H
#define JACOBI_MAIN_H

#include <pthread.h>
#include "src/cthread.h"
#include "src/barrier.h"

int main(int argc, char *argv[]);

/*
 * Transforms a space separated .mtx file into a 1024x1024 2D double array.
 * Input:
 *  FILE *file: the file pointer provided by fopen(file.mtx)
 *  double (*matrix)[]: the malloc'd 2d array to be filled
 *  char *argv[]: command line arguments, used for printing
 * Output: void
 */
void fileToMatrix(FILE *file, double (*matrix)[], char *programArgs[]);

void writeMatrixToFile(FILE *file, double (*matrix)[]);

void swapMatrix(double (*source)[], double (*dest)[]);

char *processArgs(int argc, char *argv[]);

/*
 * Prints the usage of the program
 * Input:
 *  char *argv: used for grabbing program name instead of hard coding in
 * Output: void
 */
void printUsage(char *argv[]);

/* Compute the values for the new matrix from the previous matrix.
 * Input:
 *  double (*P)[]: previous matrix
 *  double (*N)[]: new matrix
 *  tArg *thread: given thread
 * Output: void
 */
void computeCell(double (*P)[], double (*N)[], tArg *thread);

/* Checks that the program should continue to iterate
 * Input: shared barrier object
 * Output: void
 */
void continueIterationCheck(barrier *bar);

/* Create the thread argument that is passed into computeJacobi which
 * is the threads main function
 * Input: thread id, pointer to the shared barrier object
 * Output: Populated thread argument
 */
tArg *makeThreadArg(int id, barrier *bar);

/* Function that each thread runs independently to compute the new matrix
 * Input: thread argument with respect to the thread that called this function
 * Output: thread argument to be freed
 */
tArg *computeJacobi(void *threadArg);

/* create the given number of threads
 * Input: number of threads
 * Output: void
 */
void createThread(pthread_t *threads, int noth, barrier *bar);

#endif //JACOBI_MAIN_H
