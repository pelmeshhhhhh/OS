#include "Number.h"

const Number Number::ZERO(0.0);
const Number Number::ONE(1.0);

Number::Number() : value(0.0) {}

Number::Number(double value) : value(value) {}

Number::Number(const Number& other) : value(other.value) {}

Number& Number::operator=(const Number& other) {
    if (this != &other) {
        value = other.value;
    }
    return *this;
}

Number& Number::operator=(double value) {
    this->value = value;
    return *this;
}

Number Number::operator+(const Number& other) const {
    return Number(value + other.value);
}

Number Number::operator-(const Number& other) const {
    return Number(value - other.value);
}

Number Number::operator*(const Number& other) const {
    return Number(value * other.value);
}

Number Number::operator/(const Number& other) const {
    if (other.value == 0.0) {
        throw std::runtime_error("Division by zero");
    }
    return Number(value / other.value);
}

Number& Number::operator+=(const Number& other) {
    value += other.value;
    return *this;
}

Number& Number::operator-=(const Number& other) {
    value -= other.value;
    return *this;
}

Number& Number::operator*=(const Number& other) {
    value *= other.value;
    return *this;
}

Number& Number::operator/=(const Number& other) {
    if (other.value == 0.0) {
        throw std::runtime_error("Division by zero");
    }
    value /= other.value;
    return *this;
}

Number Number::sqrt() const {
    if (value < 0.0) {
        throw std::domain_error("Square root of negative number");
    }
    return Number(std::sqrt(value));
}

Number Number::atan2(const Number& y, const Number& x) {
    return Number(std::atan2(y.value, x.value));
}

double Number::toDouble() const {
    return value;
}

std::string Number::toString() const {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

void Number::print() const {
    std::cout << value << std::endl;
}

bool Number::operator==(const Number& other) const {
    return value == other.value;
}

bool Number::operator!=(const Number& other) const {
    return value != other.value;
}

bool Number::operator<(const Number& other) const {
    return value < other.value;
}

bool Number::operator>(const Number& other) const {
    return value > other.value;
}

bool Number::operator<=(const Number& other) const {
    return value <= other.value;
}

bool Number::operator>=(const Number& other) const {
    return value >= other.value;
}