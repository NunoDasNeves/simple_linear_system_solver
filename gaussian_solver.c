#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "sl_solver.h"

#define DEBUG 1

sl_mat sl_g_solve(sl_mat A, sl_mat b, enum sl_result * num_solutions) {

    // assume one solution
    *num_solutions = ONE; // ONE INF

    // construct an augmented matrix from A and b
    sl_mat aug = sl_mat_alloc(A.rows, A.cols+1);
    // copy A's cols
    for (size_t i = 0; i < A.cols; ++i) {
        sl_mat_copy_col(A, aug, i, i);
    }
    // copy b into last col
    sl_mat_copy_col(b, aug, 0, A.cols);

#if DEBUG
    printf("Augmented matrix:\n");
    sl_mat_print(aug);
#endif

    // temporary row for swapping
    sl_mat temp = sl_mat_alloc(1, aug.cols);

    // perform operations on matrix until it is in reduced row echelon form
    size_t pivot_pos = 0;
    for (size_t e_row = 0; e_row < aug.rows; ++e_row, ++pivot_pos) { // row being used to eliminate
#if DEBUG
        printf ("Reducing row %lu\n", e_row);
#endif
        // find the first row with the leftmost pivot of all remaining rows
        // NOTE: not required to show infinite solutions?
        bool pivot_found = false;
        for (size_t p = pivot_pos; p < aug.cols-1; ++p) { // minus 1 because last col invalid
            // find first row with a pivot in the desired pivot position
            for (size_t r = e_row; r < aug.rows; ++r) {

                // if non-zero (i.e. we found a pivot), swap with e_row and break
                if (!SL_D_EQ(SL_MAT_GET(aug,r,pivot_pos), 0)) {
#if DEBUG
                    printf ("  Pivot at col %lu found at row %lu, swapping if necessary!\n", p, r);
#endif
                    if (e_row != r) { // don't do swap if they're already the same!
                        sl_mat_copy_row(aug, temp, e_row, 0);
                        sl_mat_copy_row(aug, aug, r, e_row);
                        sl_mat_copy_row(temp, aug, 0, r);
                    }
                    pivot_found = true;
                    break;
                }

            }
            // if the desired pivot was found, break
            if (pivot_found) {
                // update pivot position to the one we actually found
                pivot_pos = p;
                break;
            }
        }

        // check for inconsistencies
        // if no pivot was found, then the remaining rows (no including the last column) are zeroes
        if (!pivot_found) {
            // check each row from e_row to the end
            // since no pivot is found, they must all be rows of zeros, except for the last column
            // which we haven't checked.
            // if the last column contains any non-zero numbers, then the system is inconsistent!
            for (size_t r = e_row; r < aug.rows; ++r) {
                if (!SL_D_EQ(SL_MAT_GET(aug, r, aug.cols-1), 0)) {
#if DEBUG
                    printf("Inconsistency! Reduced row echelon-form matrix:\n");
                    sl_mat_print(aug);
#endif
                    // free aug and return that there are zero solutions
                    *num_solutions = ZERO;
                    sl_mat_free(aug);
                    sl_mat zero = {0,0,NULL};
                    return zero;
                }
            }
            // otherwise, there are just some rows of zeros at the end of the matrix, so we're done
            break;
        }

#if DEBUG
        printf ("  Multiplying row %lu by %lf\n", e_row, 1.0/SL_MAT_GET(aug, e_row, pivot_pos));
#endif
        // at this point, e_row is a row with pivot at pivot_pos
        // divide the row by the pivot number make the pivot element = 1
        sl_mat_mul_row(aug, e_row, 1.0/SL_MAT_GET(aug, e_row, pivot_pos));

        // go through every row (skipping e_row)
        // for each row which has a number at pivot_pos, 'reduce' that number to 0 by subtracting a multiple of e_row.
        // this reduces rows to their reduced echelon form
        for (size_t r = 0; r < aug.rows; ++r) {
        // and reduces rows underneath by reducing the element in the pivot position to 0
            if (r == e_row) continue;
            // check there's a non-zero value at the pivot position
            double factor = SL_MAT_GET(aug, r, pivot_pos);
            if (!SL_D_EQ(factor, 0)) {
                // subtract a factor * e_row from row r
                // we only need to do from pivot_pos onward:
                // - rows above e_row which have numbers before pivot_pos will be unaffected anyway
                // - rows below e_row are guaranteed to not have numbers before pivot_pos
                for (size_t c = pivot_pos; c < aug.cols; ++c) {
                    SL_MAT_GET(aug, r, c) -= factor*SL_MAT_GET(aug, e_row, c);
                }
            }
        }
    }
    // if the pivot pos didn't get to the end of the columns, it is a case of infinite solutions
    if (pivot_pos < aug.cols-1) {
        *num_solutions = INF;
    }

#if DEBUG
    printf("Reduced row echelon-form matrix:\n");
    sl_mat_print(aug);
#endif

    // return the reduced row echelon matrix
    return aug;
}

