#include "Matrix.h"

Matrix::Matrix(int size) {
    if (size <= 0) {
        n = 0;
        if (size < 0) {
            std::cerr << "Error: Matrix size must be positive, got: " << size << std::endl;
        }
    }
    else {
        n = size;
        data.resize(n, std::vector<int>(n, 0));
    }
}

void Matrix::randomFill(int minVal, int maxVal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minVal, maxVal);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            data[i][j] = dis(gen);
        }
    }
}

void Matrix::print() const {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << data[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

int Matrix::get(int i, int j) const { return data[i][j]; }
void Matrix::set(int i, int j, int value) { data[i][j] = value; }
int Matrix::size() const {
    if (n < 0 || data.size() != static_cast<size_t>(n)) {
        std::cerr << "Error: Inconsistent matrix state. n=" << n << ", data.size()=" << data.size() << std::endl;
        return 0;
    }
    return n;
}

Matrix Matrix::multiplySimple(const Matrix& A, const Matrix& B) {
    int n = A.size();

    if (n == 0 || B.size() != n) {
        std::cerr << "Error: Invalid matrices for multiplication" << std::endl;
        return Matrix(0);
    }

    Matrix result(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A.get(i, k) * B.get(k, j);
            }
            result.set(i, j, sum);
        }
    }
    return result;
}

bool Matrix::equals(const Matrix& other) const {
    if (n != other.n) return false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (data[i][j] != other.get(i, j)) {
                return false;
            }
        }
    }
    return true;
}