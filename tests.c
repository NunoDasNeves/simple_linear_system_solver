#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sl_solver.h"
#include "sl_mat.h"

// basic whitebox testing for matrix library and solvers

static void mat_1() {
    printf("Simple matrix mul\n");
    double a[] = {2.0,0,0,2.0};
    double b[] = {3.0,34.2323,21.23,42.019923};
    sl_mat A, B, C;
    A.dat = a;
    B.dat = b;
    A.m = A.n = B.m = B.n = 2;
    C = sl_mat_mul(A, B);
    for (int i = 0; i < 4; ++i)
        assert(SL_D_EQ(2.0*B.dat[i], C.dat[i]));
    sl_mat_free(C);
}

static void mat_2() {
    printf("Matrix factors mul\n");
    // TODO
}

static void mat_3() {
    printf("Matrix vector mul\n");
    // TODO
}

static void mat_4() {
    printf("Multi matrix mul\n");
    // TODO
}

static void test_mat() {
    printf("**** Testing matrix library\n");
    mat_1();
    mat_2();
    mat_3();
    printf("sl_matrix library: ALL PASSED\n\n");
}

static void test_i_solver() {
    // TODO
}

static void test_d_solver() {
    // TODO
}

void sl_run_tests() {
    test_mat();
    test_i_solver();
    test_d_solver();
}
