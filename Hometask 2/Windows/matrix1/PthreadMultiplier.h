#ifndef PTHREAD_MULTIPLIER_H
#define PTHREAD_MULTIPLIER_H

// #pragma comment(lib, "pthreadVSE3.lib")

#include "Matrix.h"
#include <pthread.h>
#include <vector>
#include <algorithm>

class PthreadMultiplier {
private:
    struct ThreadData {
        const Matrix* A;
        const Matrix* B;
        Matrix* result;
        int startRow;
        int startCol;
        int blockSize;
    };

public:
    static Matrix multiply(const Matrix& A, const Matrix& B, int blockSize);

private:
    static void* threadFunction(void* arg);
    static void multiplyBlock(const Matrix& A, const Matrix& B, Matrix& result,
        int startRow, int startCol, int blockSize);
};

#endif