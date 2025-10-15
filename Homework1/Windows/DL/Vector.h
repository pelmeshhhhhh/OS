#ifndef VECTOR_H
#define VECTOR_H

#ifdef VECTORLIB_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif

#include "../Libraries/Number.h"
#include <string>
#include <iostream>

class VECTOR_API Vector {
private:
    Number x;
    Number y;

public:
    Vector();
    Vector(const Number& x, const Number& y);
    Vector(double x, double y);

    static const Vector ZERO_VEC;
    static const Vector ONE_VEC;

    Number getX() const;
    Number getY() const;
    void setX(const Number& x);
    void setY(const Number& y);

    Number PolarR() const;
    Number PolarA() const;

    Vector Add(const Vector& other) const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);

    void Print() const;
    std::string ToString() const;
};


#endif