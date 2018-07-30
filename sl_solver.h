#ifndef SL_SOLVER_H
#define SL_SOLVER_H

#include "sl_mat.h"

extern void sl_run_tests();

// enum to denote the number of solutions of a system of linear equations
enum sl_result {ZERO, ONE, INF};

/*
 * Gaussian elimination solver
 * A: m*n matrix of equation coefficients
 * b: m*1 matrix (vector) of equation constants
 * r: (single solution, infinite solutions, no solution) is returned
 * returns: the reduced row-echelon form augmented matrix if infinite or single solution is found
 * returns: a 0*0 vector if no solution is found
 */
// gaussian elimination solver
extern sl_mat sl_g_solve(sl_mat A, sl_mat b, enum sl_result * r);

#endif
