#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sl_mat.h"

// allocate a new matrix of size rows*cols
sl_mat sl_mat_alloc(size_t r, size_t c) {
    sl_mat m = {rows:r, cols:c};
    m.dat = (double *)calloc(m.rows*m.cols, sizeof(double));
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
    if (A.cols != B.rows) {
        fprintf(stderr, "Can't multiply two matrices with %lu columns and %lu rows respectively\n", A.cols, B.rows);
        exit(EXIT_FAILURE);
    }
    // new matrix with A's no of rows, B's no of cols
    sl_mat C = sl_mat_alloc(A.rows, B.cols);  // uses calloc so filled with 0s

    // naive cubic matmul
    size_t c = 0;
    for (size_t i = 0; i < A.rows; ++i) {          // row in A
        for (size_t j = 0; j < B.cols; ++j) {      // col in B
            for (size_t k = 0; k < A.cols; ++k) {  // col in A, row in B
                C.dat[c] += A.dat[i*A.cols+k]*B.dat[k*B.cols+j];
            }
            // next entry in c, to save multiplications
            ++c;
        }
    }

    return C;
}

// multiply an allocated matrix A by a constant factor
void sl_mat_mul_factor(sl_mat A, double factor) {
    size_t len = A.cols*A.rows;
    for (size_t i = 0; i < len; ++i) {
        A.dat[i] *= factor;
    }
}

// multiply a row of a matrix by a constant factor
void sl_mat_mul_row(sl_mat A, size_t row, double factor) {
    if (row > A.rows) {
        fprintf(stderr, "Out of bounds sl_mat_mul_row\n");
        exit(EXIT_FAILURE);
    }
    size_t end = row * A.cols + A.cols;
    for (size_t i = row*A.cols; i < end; ++i) {
        A.dat[i] *= factor;
    }
}

sl_mat sl_mat_copy(sl_mat A) {
    sl_mat B = sl_mat_alloc(A.rows, A.cols);
    memcpy(B.dat, A.dat, B.rows*B.cols*(sizeof(double)));
    return B;
}

void sl_mat_copy_col(sl_mat A, sl_mat B, size_t from, size_t to) {
    if (A.rows != B.rows) {
        fprintf(stderr, "Matrices must have same number of rows sl_mat_copy_col\n");
        exit(EXIT_FAILURE);
    } else if (from > A.cols || to > B.cols) {
        fprintf(stderr, "Out of bounds sl_mat_copy_col\n");
        exit(EXIT_FAILURE);
    }
    size_t len = A.cols*A.rows;
    for(;from < len; from += A.cols, to += B.cols) {
        B.dat[to] = A.dat[from];
    }
}

void sl_mat_copy_row(sl_mat A, sl_mat B, size_t from, size_t to) {
    if (A.cols != B.cols) {
        fprintf(stderr, "Matrices must have same number of cols sl_mat_copy_row\n");
        exit(EXIT_FAILURE);
    } else if (from > A.rows || to > B.rows) {
        fprintf(stderr, "Out of bounds sl_mat_copy_row\n");
        exit(EXIT_FAILURE);
    }
    memcpy(&B.dat[to*B.cols], &A.dat[from*B.cols], B.cols*(sizeof(double)));
}

void sl_mat_print(sl_mat A) {
    printf("[ ");
    for (size_t i = 0; i < A.rows; ++i) {          // row in A
        printf("%s", i == 0 ? "" : "  ");
        for (size_t j = 0; j < A.cols; ++j) {      // col in A
            printf("%.3lf ", A.dat[i*A.cols+j]);
        }
        printf("%s\n", i == A.rows-1 ? "]" : "");
    }
}
