# Übung 8 - Chinese Remainder Theorem in practice

## Build Instructions
This exercise was implemented in C++ using the GMP library (version 6.0.0a). After adjusting the variable `CC` in the `Makefile` to your C++ compiler, a simple `make` should build and run the implementation.

## Implementation Details
Some of the algorithms are recursive. A conversion to iterative algorithms could possible result in even greater speed-ups.
### EEA.cc
Contains the simple and extended euclidean algorithm. The simple version is implemented iteratively, the extended recursively.

### CRT.cc
Contains the algorithms for the Chinese Remainder Theorem (recursive) and the exponentiation based upon it.

## Results
Run on my computer, the implementation produces the following results:

    Running 100 tests for N = 1024
    Time spent using own algorithm: 0.783164 seconds
    Time spent using GMP algorithm: 1.229521 seconds
    Speed-up: 1.569941
    Running 50 tests for N = 2048
    Time spent using own algorithm: 2.494518 seconds
    Time spent using GMP algorithm: 4.306443 seconds
    Speed-up: 1.726363
    Running 20 tests for N = 4096
    Time spent using own algorithm: 6.791347 seconds
    Time spent using GMP algorithm: 10.071012 seconds
    Speed-up: 1.482918
