#ifndef NUMBER_H
#define NUMBER_H

#include <cmath>
#include <sstream>
#include <iostream>
#include <stdexcept>

class Number {
private:
    double value;

public:
    Number();
    Number(double value);
    Number(const Number& other);

    Number& operator=(const Number& other);
    Number& operator=(double value);

    Number operator+(const Number& other) const;
    Number operator-(const Number& other) const;
    Number operator*(const Number& other) const;
    Number operator/(const Number& other) const;

    Number& operator+=(const Number& other);
    Number& operator-=(const Number& other);
    Number& operator*=(const Number& other);
    Number& operator/=(const Number& other);

    Number sqrt() const;
    static Number atan2(const Number& y, const Number& x);

    double toDouble() const;
    std::string toString() const;
    void print() const;

    bool operator==(const Number& other) const;
    bool operator!=(const Number& other) const;
    bool operator<(const Number& other) const;
    bool operator>(const Number& other) const;
    bool operator<=(const Number& other) const;
    bool operator>=(const Number& other) const;

    static const Number ZERO;
    static const Number ONE;
};

#endif