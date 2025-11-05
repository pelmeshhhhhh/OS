#include "ThreadMultiplier.h"

Matrix ThreadMultiplier::multiply(const Matrix& A, const Matrix& B, int blockSize) {
    int n = A.size();
    Matrix result(n);
    std::vector<std::thread> threads;

    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            threads.emplace_back([&, i, j]() {
                multiplyBlock(A, B, result, i, j, blockSize);
                });
        }
    }

    for (auto& t : threads) {
        t.join();
    }

    return result;
}

void ThreadMultiplier::multiplyBlock(const Matrix& A, const Matrix& B, Matrix& result,
    int startRow, int startCol, int blockSize) {
    int n = A.size();

    for (int i = startRow; i < std::min(startRow + blockSize, n); i++) {
        for (int j = startCol; j < std::min(startCol + blockSize, n); j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A.get(i, k) * B.get(k, j);
            }
            result.set(i, j, sum);
        }
    }
}