#include "../Libraries/Number.h"
#include <Windows.h>
#include "../DL/Vector.h"
#include <iostream>

int main() {
	HINSTANCE load;
	load = LoadLibrary(L"DL.dll");
	Number a(10.0);
	Number b(5.0);
	Number n = Number::ONE;
	std::cout << "Test Number" << std::endl;
	a.print();
	n.print();
	(a + n).print();
	(a - n).print();
	(a * b).print();
	(a / b).print();
	a += b;
	a.print();
	Vector d(10, 10);
	Vector c(5, 2);
	
	std::cout << "Test Vector" << std::endl;
	c.Print();
	(c + d).Print();
	(c - d).Print();
	d.PolarA().print();
	d.PolarR().print();

	return 0;
}