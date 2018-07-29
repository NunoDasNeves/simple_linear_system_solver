#include "sl_solver.h"



sl_mat g_solver(sl_mat A, sl_mat b, enum sl_result * r) {
    // construct an augmented matrix from A and b

    sl_mat aug = sl_mat_alloc(A.rows, A.cols+1);
    // copy A's cols
    for (size_t i = 0; i < A.cols; ++i) {
        sl_mat_copy_col(A, aug, i, i);
    }
    // copy b into last col
    sl_mat_copy_col(b, aug, 0, A.cols);

    sl_mat_print(aug);

    sl_mat x = {0,0,NULL};
    *r = ZERO; // ONE INF

    return x;
}

