#ifndef SL_SOLVER_H
#define SL_SOLVER_H

#include "sl_mat.h"

extern void sl_run_tests();

// enum to denote the number of solutions of a system of linear equations
enum sl_result {ZERO, ONE, INF};

/*
 * Functions for invoking the solvers
 * A: m*n matrix of equation coefficients
 * b: m*1 matrix (vector) of equation constants
 * r: (single solution, infinite solutions, no solution) is returned
 * returns an n*1 matrix (vector) of variables if there is a single solution
 * The returned vector has 0 size if no solution was found, or there are infinite solutions
 */
// gaussian elimination solver
extern sl_mat g_solver(sl_mat A, sl_mat b, enum sl_result * r);

#endif
