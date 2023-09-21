#include <iostream>
#include "Fraction.h";

void main() {
	std::cout << "Constructors: ";
	Fraction def = Fraction() , par = Fraction(3, 4);
	
	std::cout << "def: ";
	def.print();
	std::cout << std::endl;

	std::cout << "par: ";
	par.print();
	std::cout << std::endl;

	Fraction a = Fraction(), b = Fraction();
	std::cout << "Input 2 fractions (without '/') for summ, multipication, division and difference" << std::endl;
	a.set();
	b.set();

	std::cout << "A: "; 
	a.print();
	std::cout << std::endl;

	std::cout << "B: ";
	b.print();
	std::cout << std::endl;

	Fraction summ=a, mult=a, divis=a, diff=a;
	summ += b;
	diff -= b;
	mult *= b;
	divis /= b;


	std::cout << "a+b= "; summ.print(); summ = a + b;  std::cout << " "; summ.print(); std::cout << std::endl;

	std::cout << "a-b= "; diff.print(); diff = a - b;  std::cout << " "; diff.print(); std::cout << std::endl;
	
	std::cout << "a*b= "; mult.print(); mult = a * b; std::cout << " "; mult.print(); std::cout << std::endl;

	std::cout << "a/b= "; divis.print(); divis = a / b;  std::cout << " "; divis.print(); std::cout << std::endl;

	summ.reduce();
	diff.reduce();
	mult.reduce();
	divis.reduce();

	std::cout << std::endl << "Reduced: " << std::endl; 

	std::cout << "a+b= "; summ.print(); std::cout << std::endl;

	std::cout << "a-b= "; diff.print(); std::cout << std::endl;

	std::cout << "a*b= "; mult.print(); std::cout << std::endl;

	std::cout << "a/b= "; divis.print(); std::cout << std::endl;

	Fraction num1, num2;

	std::cout << "Input 2 fractions for comparison " << std::endl;
	num1.set();
	num2.set();

	std::cout << num1.compare(num2) << std::endl;

	std::cout << "Input 1 fraction for convertion to double and backward" << std::endl;
	Fraction foo;
	foo.set();

	float fooDouble = foo.convertToFloat(); 
	foo = foo.convertFromFloat(fooDouble, 3);
	std::cout.precision(4);
	std::cout << fooDouble << std::endl;
	foo.print();

}