#ifndef WINDOWS_MULTIPLIER_H
#define WINDOWS_MULTIPLIER_H

#include "Matrix.h"
#define NOMINMAX
#include <windows.h>
#include <vector>
#include <utility>
#include <algorithm>

class WindowsMultiplier {
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
    static DWORD WINAPI threadFunction(LPVOID lpParam);
    static void multiplyBlock(const Matrix& A, const Matrix& B, Matrix& result,
        int startRow, int startCol, int blockSize);
};

#endif