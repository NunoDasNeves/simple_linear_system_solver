## Simple Linear System Solver (slsolve)
Simple (and naive) implementations of basic linear equation solvers in C.  
WARNING: Primarily for self-education - don't actually use this!

# Build
`make` to build `slsolve` binaries  
`make test` to run build and run tests  
`make clean` to remove binaries

# Input
A system of linear equations, in the form of a matrix A and vector b.

Element i,j of A is the coefficient of the jth unknown variable in the ith row of A, and  
element i of b is the constant in equation i.

i.e. each equation i takes the form:  
    Ai1 + Ai2 + ... + Aij = bi

Input is read from std input and should take the following form:
```
m n
A11 A12 ... A1n
A21 A22 ... A2n
... ... ... ...
Am1 Am2 ... Amn
b1
b2
...
bm
```
where:  
m = number of equations  
n = number of unknown variables  

It's best to write the system of equations to a file and pipe it to stdin of the solver.

# Output
(Assuming no fatal error occurs...)  
One line with the result of the solver - `success` or `failure`. If the result is `failure`, an error message is printed.  
Otherwise, the number of solutions of the system is printed - `single`, `infinite` or `none`.  
If there is a single solution, it is printed as a space-separated list of doubles.

Errors that cause `failure` to be printed:  
TODO

# Usage and Examples
See tests directory for example inputs
```
-i          specify the iterative solver (default)
-d          specify the direct solver
-e BOUND    select error bound (default = TODO)
-t          run whitebox tests (nothing else happens)
```
TODO more options!

Solve a system of linear equations specified in 'input.txt' using the direct solver:
```./slsolve -d < input.txt```

... TODO

# Precision and Performance
This implementation is not performant or particularly precise.

