#include "Matrix.h"
#include "ThreadMultiplier.h"
#include "WindowsMultiplier.h"
#include "PthreadMultiplier.h"
#include <iostream>
#include <chrono>
#include <vector>

using Clock = std::chrono::high_resolution_clock;
using Microseconds = std::chrono::microseconds;

void testAllMethods(int matrixSize) {

    Matrix A(matrixSize);
    Matrix B(matrixSize);
    A.randomFill();
    B.randomFill();

    auto start = Clock::now();
    Matrix simpleResult = Matrix::multiplySimple(A, B);
    auto end = Clock::now();
    auto simpleTime = std::chrono::duration_cast<Microseconds>(end - start).count();

    std::cout << "Simple multiplication: " << simpleTime << " mcrs" << std::endl;

    std::vector<int> blockSizes;
    for (int k = 1; k <= matrixSize; k++) {
        if (matrixSize % k == 0) {
            blockSizes.push_back(k);
        }
    }

    std::cout << "\nBlock sizes: ";
    for (int k : blockSizes) {
        std::cout << k << " ";
    }
    std::cout << std::endl << std::endl;

    for (int blockSize : blockSizes) {
        int numBlocks = (matrixSize / blockSize) * (matrixSize / blockSize);
        std::cout << "Block size: " << blockSize << " (threads: " << numBlocks << ")" << std::endl;

        start = Clock::now();
        Matrix threadResult = ThreadMultiplier::multiply(A, B, blockSize);
        end = Clock::now();
        auto threadTime = std::chrono::duration_cast<Microseconds>(end - start).count();
        std::cout << "  std::thread: " << threadTime << " mcrs, correct: "
            << (threadResult.equals(simpleResult) ? "YES" : "NO") << std::endl;

        start = Clock::now();
        Matrix windowsResult = WindowsMultiplier::multiply(A, B, blockSize);
        end = Clock::now();
        auto windowsTime = std::chrono::duration_cast<Microseconds>(end - start).count();
        std::cout << "  Windows API: " << windowsTime << " mcrs, correct: "
            << (windowsResult.equals(simpleResult) ? "YES" : "NO") << std::endl;

        start = Clock::now();
        Matrix pthreadResult = PthreadMultiplier::multiply(A, B, blockSize);
        end = Clock::now();
        auto pthreadTime = std::chrono::duration_cast<Microseconds>(end - start).count();
        std::cout << "  pthread: " << "\t" << pthreadTime << " mcrs, correct: "
            << (pthreadResult.equals(simpleResult) ? "YES" : "NO") << std::endl;

        std::cout << std::endl;
    }
}

int main() {
    /*
	std::vector<std::vector<int>> a = { {1,1,1}, {1,1,1}, {1,1,1} };
	std::vector<std::vector<int>> b = { {1,2,1}, {3,1,1}, {7,1,1} };
	Matrix A(3, a);
	Matrix B(3, b);
	Matrix C = ThreadMultiplier::multiply(A, B, 3);
	C.print();
    */
    std::vector<int> matrixSizes = { 8, 16, 32 };

    for (int size : matrixSizes) {
        testAllMethods(size);
    }


	return 0;
}

