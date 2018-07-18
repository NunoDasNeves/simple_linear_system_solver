#include <stdlib.h>
#include <stdio.h>

#include "sl_mat.h"

// allocate a new matrix of size rows*cols
sl_mat sl_mat_alloc(size_t rows, size_t cols) {
    sl_mat m = {m:rows, n:cols};
    m.dat = (double *)calloc(rows*cols, sizeof(double));
    if (m.dat == NULL) {
        perror("Couldn't allocate matrix");
        exit(EXIT_FAILURE);
    }
    return m;
}

// free a matrix's data
void sl_mat_free(sl_mat m) {
    free(m.dat);
}

// multiply two existing, allocated matrices A and B, returning the result in a newly allocated matrix
sl_mat sl_mat_mul(sl_mat A, sl_mat B) {
    if (A.n != B.m) {
        fprintf(stderr, "Can't multiply two matrices with %lu columns and %lu rows respectively\n", A.n, B.m);
        exit(EXIT_FAILURE);
    }
    // new matrix with A's no of rows, B's no of cols
    sl_mat C = sl_mat_alloc(A.m, B.n);  // uses calloc so filled with 0s

    // naive cubic matmul
    size_t c = 0;
    for (size_t i = 0; i < A.m; ++i) {          // row in A
        for (size_t j = 0; j < B.n; ++j) {      // col in B
            for (size_t k = 0; k < A.n; ++k) {  // col in A, row in B
                C.dat[c] += A.dat[i*A.n+k]*B.dat[k*B.n+j];
            }
            // next entry in c, to save multiplications
            ++c;
        }
    }

    return C;
}

// multiply an allocated matrix A by a constant factor
void sl_mat_mul_factor(sl_mat A, double factor) {
    size_t len = A.n*A.m;
    for (size_t i = 0; i < len; ++i) {
        A.dat[i] *= factor;
    }
}

// multiply a row of a matrix by a constant factor
void sl_mat_mul_row(sl_mat A, size_t row, double factor) {
    if (row > A.m) {
        fprintf(stderr, "Out of bounds sl_mat_mul_row\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = row*A.n; i < A.n; ++i) {
        A.dat[i] *= factor;
    }
}
