#include "PthreadMultiplier.h"
#include <algorithm>
#include <iostream>
#include <memory> 

Matrix PthreadMultiplier::multiply(const Matrix& A, const Matrix& B, int blockSize) {
    int n = A.size();

    if (n == 0 || B.size() != n || blockSize <= 0) {
        std::cerr << "Error: Invalid parameters in PthreadMultiplier" << std::endl;
        return Matrix(0);
    }

    Matrix result(n);
    std::vector<pthread_t> threads;

    std::vector<std::unique_ptr<ThreadData>> threadData;

    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            auto data = std::make_unique<ThreadData>();
            data->A = &A;
            data->B = &B;
            data->result = &result;
            data->startRow = i;
            data->startCol = j;
            data->blockSize = blockSize;

            pthread_t thread;
            int createResult = pthread_create(&thread, NULL, threadFunction, data.get());

            if (createResult == 0) {
                threads.push_back(thread);
                threadData.push_back(std::move(data));
            }
            else {
                std::cerr << "Error: Failed to create pthread, error code: " << createResult << std::endl;
            }
        }
    }

    for (pthread_t thread : threads) {
        pthread_join(thread, NULL);
    }

    return result;
}

void* PthreadMultiplier::threadFunction(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);

    if (data == nullptr) {
        std::cerr << "Error: Null pointer in thread function" << std::endl;
        return NULL;
    }

    if (data->A == nullptr || data->B == nullptr || data->result == nullptr) {
        std::cerr << "Error: Null matrix pointer in thread function" << std::endl;
        return NULL;
    }

    multiplyBlock(*data->A, *data->B, *data->result,
        data->startRow, data->startCol, data->blockSize);
    return NULL;
}

void PthreadMultiplier::multiplyBlock(const Matrix& A, const Matrix& B, Matrix& result,
    int startRow, int startCol, int blockSize) {
    int n = A.size();

    if (n != B.size() || n != result.size()) {
        std::cerr << "Error: Matrix size mismatch in multiplyBlock" << std::endl;
        return;
    }

    int endRow = std::min(startRow + blockSize, n);
    int endCol = std::min(startCol + blockSize, n);

    for (int i = startRow; i < endRow; i++) {
        for (int j = startCol; j < endCol; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A.get(i, k) * B.get(k, j);
            }
            result.set(i, j, sum);
        }
    }
}