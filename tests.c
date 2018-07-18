#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sl_solver.h"
#include "sl_mat.h"

// basic whitebox testing for matrix library and solvers

static void mat_1() {
    printf("  Simple matrix mul\n");
    double a[] = {2.0,0,0,2.0};
    double b[] = {3.0,34.2323,21.23,42.019923};
    sl_mat A, B, C;
    A.dat = a;
    B.dat = b;
    A.m = A.n = B.m = B.n = 2;
    C = sl_mat_mul(A, B);

    assert(C.m == 2 && C.n == 2);
    for (int i = 0; i < 4; ++i)
        assert(SL_D_EQ(2.0*B.dat[i], C.dat[i]));
    sl_mat_free(C);
}

static void mat_2() {
    printf("  Matrix factors mul\n");
    double a[] = {3.0,34.2323,21.23,42.019923};
    double f = 42.2342;
    sl_mat A = sl_mat_alloc(2,2);
    memcpy(A.dat, a, 4*sizeof(double));
    sl_mat_mul_factor(A, f);

    for (int i = 0; i < 4; ++i)
        assert(SL_D_EQ(f*a[i], A.dat[i]));
}

static void mat_3() {
    printf("  Matrix vector mul\n");
    double a[] = {3.0,34.2323,21.23,42.019923}; // matrix
    double b[] = {62.345,5322.234};             // vector
    sl_mat A, B, C;
    A.dat = a;
    B.dat = b;
    A.m = A.n = 2;
    B.m = 2; B.n = 1;
    C = sl_mat_mul(A, B);

    assert(C.m == 2 && C.n == 1);
    assert(SL_D_EQ(a[0]*b[0]+a[1]*b[1], C.dat[0]));
    assert(SL_D_EQ(a[2]*b[0]+a[3]*b[1], C.dat[1]));
    sl_mat_free(C);
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
