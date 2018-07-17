#include <stdio.h>
#include <stdlib.h>

#include "sl_solver.h"
#include "sl_mat.h"

// basic whitebox testing for matrix library and solvers

#define DOTEST(f)           \
    if (f()) {              \
        printf("FAILED\n"); \
        return 1;           \
    else printf("PASSED\n")

#define PRINTTEST(s) printf("Running Test "s": ");

static int mat_1() {
    PRINTTEST("Simple matrix mul")
    // TODO
    return 1;
}

static int mat_2() {
    PRINTTEST("Matrix factors mul")
    // TODO
    return 1;
}

static int mat_3() {
    PRINTTEST("Multi matrix mul")
    // TODO
    return 1;
}

static int test_mat() {
    printf("**** Testing sl_matrix library");
    DOTEST(mat_1);
    DOTEST(mat_2);
    DOTEST(mat_3);
    printf("sl_matrix library: ALL PASSED");
    return 0;
}

static int test_i_solver() {
    // TODO
    return 1;
}

static int test_d_solver() {
    // TODO
    return 1;
}

int sl_run_tests() {
    if (test_mat() || test_i_solver() || test_d_solver()) return 1;
    return 0;
}
