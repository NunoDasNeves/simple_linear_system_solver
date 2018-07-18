#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "sl_solver.h"
#include "sl_mat.h"


int main(int argc, char** argv) {

    int err = 0;
    enum {ITERATIVE, DIRECT} which = ITERATIVE;

    for(int i = 1; i < argc; ++i) {
        if (strlen(argv[i]) < 2 || argv[i][0] != '-') {
            err = 1;
            break;
        }
        // check all options TODO
        switch(argv[i][1]) {
            case 't':
                sl_run_tests();
                exit(0);
            case 'i':
                which = ITERATIVE;
                break;
            case 'd':
                which = DIRECT;
                break;
            default:
                err = 1;
        }
        if (err) break;
    }

    if (err) {
        // TODO print usage
        printf("USAGE: \n");//TODO
    }
    (void)which;
    // TODO

    return EXIT_SUCCESS;
}
