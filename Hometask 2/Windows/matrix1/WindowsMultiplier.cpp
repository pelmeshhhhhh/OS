#include "WindowsMultiplier.h"
#include <algorithm>
#include <iostream>

Matrix WindowsMultiplier::multiply(const Matrix& A, const Matrix& B, int blockSize) {
    int n = A.size();
    if (n == 0) return Matrix(0);

    Matrix result(n);
    std::vector<HANDLE> threads;
    threads.reserve((n / blockSize + (n % blockSize != 0)) * (n / blockSize + (n % blockSize != 0)));

    std::vector<ThreadData*> threadDataPtrs;

    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            ThreadData* data = new ThreadData{ &A, &B, &result, i, j, blockSize };
            threadDataPtrs.push_back(data);

            HANDLE thread = CreateThread(
                NULL,
                0,
                threadFunction,
                data,
                0,
                NULL
            );

            if (thread == NULL) {
                std::cerr << "Error: Failed to create thread. Error code: " << GetLastError() << std::endl;
                delete data;
            }
            else {
                threads.push_back(thread);
            }
        }
    }

    if (!threads.empty()) {
        DWORD numThreads = static_cast<DWORD>(threads.size());
        DWORD offset = 0;

        while (offset < numThreads) {
            DWORD count = std::min(numThreads - offset, static_cast<DWORD>(MAXIMUM_WAIT_OBJECTS));

            if (count > 0) {
                DWORD waitResult = WaitForMultipleObjects(count, threads.data() + offset, TRUE, INFINITE);
                if (waitResult == WAIT_FAILED) {
                    std::cerr << "Error: WaitForMultipleObjects failed. Error code: " << GetLastError() << std::endl;
                }
            }

            offset += count;
        }
    }

    for (HANDLE thread : threads) {
        CloseHandle(thread);
    }

    for (ThreadData* data : threadDataPtrs) {
        delete data;
    }

    return result;
}

DWORD WINAPI WindowsMultiplier::threadFunction(LPVOID lpParam) {
    ThreadData* data = static_cast<ThreadData*>(lpParam);
    multiplyBlock(*data->A, *data->B, *data->result,
        data->startRow, data->startCol, data->blockSize);
    return 0;
}

void WindowsMultiplier::multiplyBlock(const Matrix& A, const Matrix& B, Matrix& result,
    int startRow, int startCol, int blockSize) {
    int n = A.size();
    if (n == 0) return;

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