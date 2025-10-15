#include "Vector.h"
#include <sstream>
#include <iostream>

// using namespace std;

#ifdef VECTORLIB_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif

Vector::Vector() : x(Number::ZERO), y(Number::ZERO) {}

Vector::Vector(const Number& x, const Number& y) : x(x), y(y) {}

Vector::Vector(double x, double y) : x(x), y(y) {}

Number Vector::getX() const {
    return x;
}

Number Vector::getY() const {
    return y;
}

void Vector::setX(const Number& x) {
    this->x = x;
}

void Vector::setY(const Number& y) {
    this->y = y;
}

Number Vector::PolarR() const {
    Number x_squared = x * x;
    Number y_squared = y * y;
    Number sum = x_squared + y_squared;
    return sum.sqrt();
}

Number Vector::PolarA() const {
    return Number::atan2(y, x);
}

Vector Vector::Add(const Vector& other) const {
    Number newX = x + other.x;
    Number newY = y + other.y;
    return Vector(newX, newY);
}

Vector Vector::operator+(const Vector& other) const {
    return Add(other);
}

Vector Vector::operator-(const Vector& other) const {
    Number newX = x - other.x;
    Number newY = y - other.y;
    return Vector(newX, newY);
}

void Vector::Print() const {
    std::cout << "(" << x.toString() << ", " << y.toString() << ")" << '\n';
}

std::string Vector::ToString() const {
    std::stringstream ss;
    ss << "(" << x.toString() << ", " << y.toString() << ")";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "Vector(" << vec.x.toString() << ", " << vec.y.toString() << ")";
    return os;
}

const Vector Vector::ZERO_VEC(Number(0.0), Number(0.0));
const Vector Vector::ONE_VEC(Number(1.0), Number(1.0));