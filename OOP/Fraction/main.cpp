#include <iostream>
#include "Fraction.h";

void main() {
	Fraction F1, F2, Summ, Diff;

	F1.numerator = 1;
	F1.denominator = 2;


	F2.numerator = 3;
	F2.denominator = 4;

	Summ = F1.summ_fractions(F2);
	
	Summ.print();

	/*
	1/2 + 3/4 = (1*4+3*2)/8 = 10/8
	output: 10/8
	
	*/

	std::cout << "\n";
	Diff = F1.difference_fractions(F2);

	Diff.print();

	/*
	1/2-3/4 = (1*4-3*2)/2*4 = -2/8
	*/

}