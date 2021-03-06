#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sl_solver.h"
#include "sl_mat.h"

// basic whitebox testing for matrix library and solvers

static void mat_1() {
    printf("* Simple matrix mul\n");
    double a[] = {2.0,0,0,2.0};
    double b[] = {3.0,-34.2323,21.23,42.019923};
    sl_mat A, B, C;
    A.dat = a;
    B.dat = b;
    A.rows = A.cols = B.rows = B.cols = 2;
    C = sl_mat_mul(A, B);

    assert(C.rows == 2 && C.cols == 2);
    for (int i = 0; i < 4; ++i)
        assert(SL_D_EQ(2.0*B.dat[i], C.dat[i]));
    sl_mat_free(C);
    printf("\n");
}

static void mat_2() {
    printf("* Matrix factor mul\n");
    double a[] = {3.0,34.2323,21.23,-42.019923};
    double f = 42.2342;
    sl_mat A = sl_mat_alloc(2,2);
    memcpy(A.dat, a, 4*sizeof(double));
    sl_mat_mul_factor(A, f);

    for (int i = 0; i < 4; ++i)
        assert(SL_D_EQ(f*a[i], A.dat[i]));

    sl_mat_free(A);
    printf("\n");
}

static void mat_3() {
    printf("* Matrix vector mul\n");
    double a[] = {3.0,34.2323,21.23,42.019923}; // matrix
    double b[] = {62.345,-5322.234};            // vector
    sl_mat A, B, C;
    A.dat = a;
    B.dat = b;
    A.rows = A.cols = 2;
    B.rows = 2; B.cols = 1;
    C = sl_mat_mul(A, B);

    assert(C.rows == 2 && C.cols == 1);
    assert(SL_D_EQ(a[0]*b[0]+a[1]*b[1], C.dat[0]));
    assert(SL_D_EQ(a[2]*b[0]+a[3]*b[1], C.dat[1]));
    sl_mat_free(C);
    printf("\n");
}

static void mat_4() {
    printf("* Matrix row mul\n");
    double a[] = {3.0,34.2323,-21.23,42.019923,334.232,2882.2324};
    double f = -42.9807;
    sl_mat A = sl_mat_alloc(2,3);
    memcpy(A.dat, a, 6*sizeof(double));
    sl_mat_mul_row(A, 0, f);    // multiply row 0 by f

    for (int i = 0; i < 3; ++i)
        assert(SL_D_EQ(f*a[i], A.dat[i]));
    for (int i = 3; i < 6; ++i)
        assert(SL_D_EQ(a[i], A.dat[i]));

    sl_mat_free(A);
    printf("\n");
}

static void mat_5() {
    printf("* Matrix col copy\n");
    double a[] = {3.0,34.2323,-21.23,42.019923,334.232,2882.2324};
    sl_mat A = {rows:2, cols:3, dat:a};
    sl_mat B = sl_mat_alloc(2,3);
    sl_mat_copy_col(A, B, 0, 1);
    sl_mat_copy_col(A, B, 1, 2);
    sl_mat_copy_col(A, B, 2, 0);

    for (int i = 0; i < 3; ++i) {
        assert(SL_D_EQ(A.dat[i], B.dat[(i+1)%3]));
        assert(SL_D_EQ(A.dat[i+3], B.dat[(i+1)%3+3]));
    }

    sl_mat_free(B);
    printf("\n");
}

static void test_mat() {
    printf("**** Testing matrix library\n");
    mat_1();
    mat_2();
    mat_3();
    mat_4();
    mat_5();
    printf("Matrix library: ALL PASSED\n\n");
}


static void g_1() {
    printf("* Single solution 2 equation system 1\n");
    double _a[] = {1,-1,1,1};
    double _b[] = {0,2};
    sl_mat A = {rows:2, cols:2, dat:_a};
    sl_mat b = {rows:2, cols:1, dat:_b};

    enum sl_result r = ZERO;
    sl_mat x = sl_g_solve(A, b, &r);

    // single solution (1,1)
    assert(r == ONE);
    double sol[] = {1, 0, 1, 0, 1, 1};
    for (int i = 0; i < 6; ++i) {
        assert(SL_D_EQ(x.dat[i], sol[i]));
    }
    printf("\n");
}

static void g_2() {
    printf("* Single solution 2 equation system 2\n");
    double _a[] = {1.2, -1.2, 13.3, 81.2};
    double _b[] = {83.23, 21.34};
    sl_mat A = {rows:2, cols:2, dat:_a};
    sl_mat b = {rows:2, cols:1, dat:_b};

    enum sl_result r = ZERO;
    sl_mat x = sl_g_solve(A, b, &r);

    // single solution (1,1)
    assert(r == ONE);
    double sol[] = {1, 0, 59.8226102292761, 0, 1, -9.535723104056437};
    for (int i = 0; i < 6; ++i) {
        assert(SL_D_EQ(x.dat[i], sol[i]));
    }
    printf("\n");
}

static void g_3() {
    printf("* No solution 3 equation system\n");
    double _a[] = { 1,  3, -1,
                    2, -7,  4,
                    4, -1,  2};
    double _b[] = {4, -3, 8};
    sl_mat A = {rows:3, cols:3, dat:_a};
    sl_mat b = {rows:3, cols:1, dat:_b};

    enum sl_result r = ONE;
    sl_mat x = sl_g_solve(A, b, &r);

    // no solution (1,1)
    assert(r == ZERO);
    assert(x.dat == NULL);
    assert(x.rows == 0);
    assert(x.cols == 0);
    printf("\n");
}

static void g_4() {
    printf("* Inf solutions 2 equation system\n");
    double _a[] = {1, 1, 2, 2};
    double _b[] = {3, 6};
    sl_mat A = {rows:2, cols:2, dat:_a};
    sl_mat b = {rows:2, cols:1, dat:_b};

    enum sl_result r = ZERO;
    sl_mat x = sl_g_solve(A, b, &r);

    // single solution (1,1)
    assert(r == INF);
    double sol[] = {1, 1, 3, 0, 0, 0};
    for (int i = 0; i < 6; ++i) {
        assert(SL_D_EQ(x.dat[i], sol[i]));
    }
    printf("\n");
}

static void g_5() {
    printf("* Solution 3 equation system\n");
    printf("\n");
    assert(0);
}

static void G_test() {
    double _a[] = {
        -63.0f/64.0f, 15.0f/64.0f,  15.0f/64.0f,  15.0f/64.0f,  1.0f/64.0f,   1.0f/64.0f,   1.0f/64.0f,   15.0f/64.0f,
        15.0f/64.0f,  -63.0f/64.0f, 15.0f/64.0f,  1.0f/64.0f,   15.0f/64.0f,  1.0f/64.0f,   15.0f/64.0f,  1.0f/64.0f,
        1.0f/64.0f,   59.0f/192.0f, -63.0f/64.0f, 59.0f/192.0f, 1.0f/64.0f,   1.0f/64.0f,   59.0f/192.0f, 1.0f/64.0f,
        1.0f/64.0f,   1.0f/64.0f,   1.0f/64.0f,   -63.0f/64.0f, 29.0f/64.0f,  29.0f/64.0f,  1.0f/64.0f,   1.0f/64.0f,
        1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    -7.0f/8.0f,   1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,
        59.0f/192.0f, 1.0f/64.0f,   59.0f/192.0f, 1.0f/64.0f,   1.0f/64.0f,   -63.0f/64.0f, 59.0f/192.0f, 1.0f/64.0f,
        1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    -7.0f/8.0f,   1.0f/8.0f,
        59.0f/192.0f, 1.0f/64.0f,   59.0f/192.0f, 1.0f/64.0f,   59.0f/192.0f, 1.0f/64.0f,   1.0f/64.0f,   -63.0f/64.0f
    };
    double _b[] = {0, 0, 0, 0, 0, 0, 0, 0};
    sl_mat A = {rows:8, cols:8, dat:_a};
    sl_mat b = {rows:8, cols:1, dat:_b};
    sl_mat A_T = sl_mat_transpose(A);

    enum sl_result r = ZERO;
    sl_mat x = sl_g_solve(A_T, b, &r);

    sl_mat_free(x);
    sl_mat_free(A_T);
}


static void pagerank_test() {
    double _a[] = {
        1.0f/64.0f,   15.0f/64.0f,  15.0f/64.0f,  15.0f/64.0f,  1.0f/64.0f,   1.0f/64.0f,   1.0f/64.0f,   15.0f/64.0f,
        15.0f/64.0f,  1.0f/64.0f,   15.0f/64.0f,  1.0f/64.0f,   15.0f/64.0f,  1.0f/64.0f,   15.0f/64.0f,  1.0f/64.0f,
        1.0f/64.0f,   59.0f/192.0f, 1.0f/64.0f,   59.0f/192.0f, 1.0f/64.0f,   1.0f/64.0f,   59.0f/192.0f, 1.0f/64.0f,
        1.0f/64.0f,   1.0f/64.0f,   1.0f/64.0f,   1.0f/64.0f,   29.0f/64.0f,  29.0f/64.0f,  1.0f/64.0f,   1.0f/64.0f,
        1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,
        59.0f/192.0f, 1.0f/64.0f,   59.0f/192.0f, 1.0f/64.0f,   1.0f/64.0f,   1.0f/64.0f,   59.0f/192.0f, 1.0f/64.0f,
        1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,
        59.0f/192.0f, 1.0f/64.0f,   59.0f/192.0f, 1.0f/64.0f,   59.0f/192.0f, 1.0f/64.0f,   1.0f/64.0f,   1.0f/64.0f
    };
    // init to 1/N
    double _p[] = {1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,    1.0f/8.0f,   1.0f/8.0f};
    sl_mat G = {rows:8, cols:8, dat:_a};
    sl_mat p = sl_mat_alloc(1, 8);
    memcpy(p.dat, _p, 8*sizeof(double));

    sl_mat x; // not allocated

    for (int i = 0; i < 7; ++i) {
        x = sl_mat_mul(p, G);
        sl_mat_free(p);
        p.dat = x.dat;
        sl_mat_print(x);
    }
    //for (int i = 0; i < 8; ++i) {
    //    
    //}

    sl_mat_free(x);
}


static void test_g_solver() {
    printf("**** Testing gaussian solver\n");
    g_1();
    g_2();
    g_3();
    g_4();
    G_test();
    pagerank_test();
    g_5();
    printf("Gaussian solver: ALL PASSED\n\n");
}

void sl_run_tests() {
    test_mat();
    test_g_solver();
}
