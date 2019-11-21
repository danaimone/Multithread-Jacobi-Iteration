//
// Created by Dan Aimone & Corben Roszak on 11/20/19.
//

#ifndef JACOBI_MAIN_H
#define JACOBI_MAIN_H

int main(int argc, char *argv[]);

/* Compute the values for the new matrix from the previous matrix.
 * Input: previous matrix, new matrix
 * Output: void
 */
void compute(double (*P)[], double (*N)[]);

/* create the given number of threads
 * Input: number of threads
 * Output: void
 */
void threadCreate(int noth);

#endif //JACOBI_MAIN_H
