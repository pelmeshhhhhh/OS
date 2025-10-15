#include <iostream>
#include "Number.h" 
#include "Vector.h"

int main() {
    std::cout << "--- Тестирование статической библиотеки Number ---" << std::endl;
    Number num1(10.5);
    Number num2(3.2);

    num1.print();
    num2.print();

    Number sum = num1 + num2;
    sum.print();

    Number diff = num1 - num2;
    diff.print();

    Number prod = num1 * num2;
    prod.print();

    Number quot = num1 / num2;
    quot.print();

    std::cout << "\nТестирование констант Number" << std::endl;
    Number::ZERO.print();
    Number::ONE.print();

    std::cout << "\n--- Тестирование динамической библиотеки Vector ---" << std::endl;
    Vector vec1(Number(1.0), Number(2.0));
    Vector vec2(Number(4.0), Number(5.0));

    std::cout << vec1 << std::endl;
    std::cout << vec2 << std::endl;

    Vector vec_sum = vec1 + vec2;
    std::cout << vec_sum << std::endl;

    Vector vec_diff = vec1 - vec2;
    std::cout << vec_diff << std::endl;

    std::cout << "\nТестирование констант Vector" << std::endl;
    std::cout << Vector::ZERO_VEC << std::endl;
    std::cout << Vector::ONE_VEC << std::endl;

    return 0;
}