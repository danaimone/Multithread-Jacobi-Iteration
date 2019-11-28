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
void fileToMatrix(FILE *file, double (*matrix)[], char* programArgs[]);
void writeMatrixToFile(FILE *file, double (*matrix)[]);
void copyMatrix(double (*matrix)[]);
void swapMatrix();
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

tArg* makeThreadArg(int i, barrier *bar);
tArg* computeJacobi(void *threadArg);

/* create the given number of threads
 * Input: number of threads
 * Output: void
 */
void threadCreate(pthread_t threads[], int noth, barrier *bar);

#endif //JACOBI_MAIN_H
