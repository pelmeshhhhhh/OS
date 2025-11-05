#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <random>

class Matrix {
private:
    std::vector<std::vector<int>> data;
    int n;

public:
    Matrix(int size);
    void randomFill(int minVal = 0, int maxVal = 10);
    void print() const;
    int get(int i, int j) const;
    void set(int i, int j, int value);
    int size() const;
    bool equals(const Matrix& other) const;

    static Matrix multiplySimple(const Matrix& A, const Matrix& B);
};

#endif