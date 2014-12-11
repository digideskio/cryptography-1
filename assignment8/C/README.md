# Übung 8 - Chinese Remainder Theorem in practice

## Build Instructions
This exercise was implemented in C++ using the GMP library (version 6.0.0a). After adjusting the variable `CC` in the `Makefile` to your C++ compiler, a simple `make` should build and run the implementation.

## Implementation Details
### EEA.cc
Contains the simple and extended euclidean algorithm. The simple version is implemented iteratively, the extended recursively.

### CRT.cc
Contains the algorithms for the Chinese Remainder Theorem and the exponentiation based upon it.

## Results
Run on my computer, the implementation produces the following results:

    Running 100 tests for N = 1024
    Time spent using own algorithm: 0.748686
    Time spent using GMP algorithm: 1.153354
    Speed-up: 1.540504
    Running 50 tests for N = 2048
    Time spent using own algorithm: 2.317670
    Time spent using GMP algorithm: 4.039326
    Speed-up: 1.742839
    Running 20 tests for N = 4096
    Time spent using own algorithm: 6.468639
    Time spent using GMP algorithm: 9.608183
    Speed-up: 1.485348
