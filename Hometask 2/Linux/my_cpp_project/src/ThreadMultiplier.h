#ifndef THREAD_MULTIPLIER_H
#define THREAD_MULTIPLIER_H

#include "Matrix.h"
#include <thread>
#include <vector>
#include <algorithm>

class ThreadMultiplier {
public:
    static Matrix multiply(const Matrix& A, const Matrix& B, int blockSize);

private:
    static void multiplyBlock(const Matrix& A, const Matrix& B, Matrix& result,
        int startRow, int startCol, int blockSize);
};

#endif