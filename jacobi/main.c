/* Corben Roszak & Dan Aimone
 * CSCI 347
 * Jacobi Matrix Multi Threaded Project
 * Version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "cthread.h"
#include "barrier.h"

const double (*previous)[1024];

int main(int argc, char *argv[]) {
    previous = malloc(sizeof(double) * 1024 * 1024);

    return 0;
}