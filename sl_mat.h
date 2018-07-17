#ifndef SL_MAT_H
#define SL_MAT_H

// A sl_mat matrix
typedef struct {
    size_t m, n;       // # rows, # columns
    double dat*;    // the data in row-major order
} sl_mat;

// access element m[i][j] of a matrix m (ith row, jth column)
#define SL_MAT_GET(m,i,j) m.dat[i*m.n + j]

// macros for comparing doubles
#define SL_D_EQ() //TODO
#define SL_D_NEQ() // TODO

// allocate a new matrix of size rows*cols
extern sl_mat sl_mat_alloc(size_t rows, size_t cols);
// free a matrix's data
extern void sl_mat_free(sl_mat m);
// multiply two existing, allocated matrices A and B, returning the result in a newly allocated matrix
extern sl_mat sl_mat_mul(sl_mat A, sl_mat B);
// multiply an allocated matrix A by a constant factor
extern void sl_mat_mul_factor(sl_mat A, double factor);
// multiply a row of an allocated matrix A by a constant factor
extern void sl_mat_mul_row(sl_mat A, size_t row, double factor);

#endif
