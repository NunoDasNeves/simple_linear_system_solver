#ifndef SL_MAT_H
#define SL_MAT_H

#include<math.h>
#include<stddef.h>

// A sl_mat matrix
typedef struct {
    size_t rows, cols;       // # rows, # columns
    double * dat;    // the data in row-major order
} sl_mat;

// access element m[i][j] of a matrix m (ith row, jth column)
#define SL_MAT_GET(m,i,j) m.dat[i*m.cols + j]

// macro for comparing doubles
#define SL_EPSILON 1e-6
#define SL_D_EQ(a, b) (fabs(a - b) < SL_EPSILON)

// allocate a new matrix of size rows*cols
extern sl_mat sl_mat_alloc(size_t rows, size_t cols);
// free a matrix's data
extern void sl_mat_free(sl_mat m);
// multiply two existing, allocated matrices A and B, returning the result in a newly allocated matrix
extern sl_mat sl_mat_mul(sl_mat A, sl_mat B);
// multiply an allocated matrix A by a constant factor
extern void sl_mat_mul_factor(sl_mat A, double factor);
// multiply a row of an allocated matrix A by a constant factor, row denotes 0-indexed row
extern void sl_mat_mul_row(sl_mat A, size_t row, double factor);
// copy an allocated matrix and return the copied matrix
extern sl_mat sl_mat_copy(sl_mat A);
// copy an entire column from one matrix to another, from and to denote 0-indexed columns
extern void sl_mat_copy_col(sl_mat A, sl_mat B, size_t from, size_t to);
// copy an entire row from one matrix to another, from and to denote 0-indexed rows
extern void sl_mat_copy_row(sl_mat A, sl_mat B, size_t from, size_t to);

// pretty print a matrix
extern void sl_mat_print(sl_mat A);

#endif
